//
// Torus.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Thu May  5 18:31:12 2011 loick michard
// Last update Sun May  8 13:38:44 2011 loick michard
//

#include "Torus.hpp"
#include "EquationSolver.hpp"
#include "Raytracer.hpp"

Torus::Torus(Object*object,
	     const Point& absolutePosition,
	     const Rotation& rotation,
	     const Material& material,
	     double R, double r) : ObjectPrimitive(object, 
						   absolutePosition,
						   rotation, material),
				   _R(R), _r(r)
{

}

void            Torus::setR(double R)
{
  _R = R;
}

void            Torus::setr(double r)
{
  _r = r;
}

void            Torus::getMappedCoords(const Point& intersectPoint,
				       double& x, double &y) const
{
  x = 0;
  y = 0;
}
#include <iostream>
void		
Torus::addIntersectionWithRay(const Ray& ray,
			      vector<struct s_intersected_object>& intersection) const
{
  Ray           newRay;

  newRay = getRayAtSimplePosition(ray);
  double sq1 = newRay._vector._x * newRay._vector._x +
    newRay._vector._y * newRay._vector._y +
    newRay._vector._z * newRay._vector._z;
  double sq2 = 2.0 * newRay._vector._x * newRay._point._x +
    2.0 * newRay._vector._y * newRay._point._y +
    2.0 * newRay._vector._z * newRay._point._z;
  double sq3 = newRay._point._x * newRay._point._x +
    newRay._point._y * newRay._point._y +
    newRay._point._z * newRay._point._z + _R * _R - _r * _r;
  double a = sq1 * sq1;
  double b = 2.0 * sq1 * sq2;
  double c = 2.0 * sq1 * sq3 + sq2 * sq2 - 4.0 * _R * _R *
    (newRay._vector._x * newRay._vector._x +
     newRay._vector._y * newRay._vector._y);
  double d = 2.0 * sq2 * sq3 - 4.0 * _R * _R *
    (2.0 * newRay._vector._x * newRay._point._x +
     2.0 * newRay._vector._y * newRay._point._y);
  double e = sq3 * sq3 - 4.0 * _R * _R * (newRay._point._x * newRay._point._x +
                                          newRay._point._y * newRay._point._y);
  //  std::cout<<a<<" "<<b<<" "<<c<<" "<<d<<" "<<e<<std::endl;
  vector<double> solutions =
    EquationSolver::solveQuarticEquation(a, b, c, d, e, true);
  vector<double> validSolutions;
  for (unsigned int i = 0 ; i < solutions.size(); i++)
    if (solutions[i] > EPSILON)
      validSolutions.push_back(solutions[i]);
  if (validSolutions.size() > 0)
    intersection.push_back((t_intersected_object){this, validSolutions});
}

void		Torus::intersectWithRay(const Ray& ray,
					ObjectPrimitive*& primitive, 
					double &res) const
{
  Ray           newRay;

  newRay = getRayAtSimplePosition(ray);
  double sq1 = newRay._vector._x * newRay._vector._x +
    newRay._vector._y * newRay._vector._y +
    newRay._vector._z * newRay._vector._z;
  double sq2 = 2.0 * newRay._vector._x * newRay._point._x +
    2.0 * newRay._vector._y * newRay._point._y +
    2.0 * newRay._vector._z * newRay._point._z;
  double sq3 = newRay._point._x * newRay._point._x +
    newRay._point._y * newRay._point._y +
    newRay._point._z * newRay._point._z + _R * _R - _r * _r;
  double a = sq1 * sq1;
  double b = 2.0 * sq1 * sq2;
  double c = 2.0 * sq1 * sq3 + sq2 * sq2 - 4.0 * _R * _R *
    (newRay._vector._x * newRay._vector._x +
     newRay._vector._y * newRay._vector._y);
  double d = 2.0 * sq2 * sq3 - 4.0 * _R * _R *
    (2.0 * newRay._vector._x * newRay._point._x +
     2.0 * newRay._vector._y * newRay._point._y);
  double e = sq3 * sq3 - 4.0 * _R * _R * (newRay._point._x * newRay._point._x +
					  newRay._point._y * newRay._point._y);
  vector<double> solutions =
    EquationSolver::solveQuarticEquation(a, b, c, d, e);
  for (unsigned int i = 0; i < solutions.size(); i++)
    {
      if (solutions[i] > EPSILON && (solutions[i] < res ||  res < 0))
        {
	  primitive = (ObjectPrimitive*)this;
	  res = solutions[i];
	}
    }
}

Vector		Torus::getNormalVector(const Point& intersectPoint,
				       const Vector& viewVector) const
{
  Point       intersection  = intersectPoint - _absolutePosition;

  intersection.rotate(_rotation, true);
  Vector normal;
  double k =
    4.0 * (intersection._x * intersection._x +
	   intersection._y * intersection._y +
	   intersection._z * intersection._z + _R * _R -
	   _r * _r);

  normal._x = intersection._x * k - 8.0 * _R * _R * intersection._x;
  normal._y = intersection._y * k - 8.0 * _R * _R * intersection._y;
  normal._z = intersection._z * k;
  double cosA = viewVector * normal;
  cosA = cosA / (viewVector.getNorm() * normal.getNorm());
  if (cosA < 0)
    return (normal.normalize() * -1);
  return (normal.normalize());
}

bool            Torus::isInBoundingBox(BoundingBox& box) const
{
  box = box;
  return (true);
}
