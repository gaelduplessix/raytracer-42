//
// CubeTroue.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42/src
//
// Made by loick michard
// Login   <michar_l@epitech.net>
//
// Started on  Fri May  6 15:54:06 2011 loick michard
// Last update Wed May 25 10:49:41 2011 loick michard
//

#include <cmath>
#include "CubeTroue.hpp"
#include "EquationSolver.hpp"
#include "Raytracer.hpp"

CubeTroue::CubeTroue(void) : _coeff(11.8)
{

}

CubeTroue::CubeTroue(Object*object,
		     const Point& absolutePosition,
		     const Rotation& rotation,
		     Material* material,
		     double coeff) : ObjectPrimitive(object,
						     absolutePosition,
						     rotation, material),
				     _coeff(coeff)
{

}

void	CubeTroue::setCoeff(double coeff)
{
  _coeff = coeff;
}

void            CubeTroue::getMappedCoords(const Point& intersectPoint,
					   double& x, double &y) const
{
  x = 0;
  y = 0;
  return ;
  (void)intersectPoint;
}

void
CubeTroue::addIntersectionWithRay(const Ray& ray,
				  vector<struct s_intersected_object>& intersection) const
{
  Ray           newRay;

  newRay = getRayAtSimplePosition(ray);
  double a = pow(newRay._vector._x, 4) + pow(newRay._vector._y, 4)
    + pow(newRay._vector._z, 4);
  double b = 4 * pow (newRay._vector._x, 3) * newRay._point._x +
    4 * pow (newRay._vector._y, 3) * newRay._point._y +
    4 * pow (newRay._vector._z, 3) * newRay._point._z;
  double c =
    6 * newRay._vector._x * newRay._vector._x * newRay._point._x *
    newRay._point._x - 5 * newRay._vector._x * newRay._vector._x +
    6 * newRay._vector._y * newRay._vector._y * newRay._point._y *
    newRay._point._y - 5 * newRay._vector._y * newRay._vector._y +
    6 * newRay._vector._z * newRay._vector._z * newRay._point._z *
    newRay._point._z - 5 * newRay._vector._z * newRay._vector._z;
  double d = 4 * newRay._vector._x * pow (newRay._point._x, 3)
    - 10 * newRay._vector._x * newRay._point._x +
    4 * newRay._vector._y * pow (newRay._point._y, 3)
    - 10 * newRay._vector._y * newRay._point._y +
    4 * newRay._vector._z * pow (newRay._point._z, 3)
    - 10 * newRay._vector._z * newRay._point._z;
  double e = pow (newRay._point._x, 4) - 5 * newRay._point._x *
    newRay._point._x + pow (newRay._point._y, 4) - 5 * newRay._point._y
    * newRay._point._y + pow (newRay._point._z, 4) - 5 * newRay._point._z
    * newRay._point._z + _coeff;
  vector<double> solutions =
    EquationSolver::solveQuarticEquation(a, b, c, d, e);
  vector<double> validSolutions;
  for (unsigned int i = 0 ; i < solutions.size(); i++)
    if (solutions[i] > EPSILON)
      {
        validSolutions.push_back(solutions[i]);
      }
  if (validSolutions.size() > 0)
    intersection.push_back((t_intersected_object){this, validSolutions});
}

void            CubeTroue::intersectWithRay(const Ray& ray,
					    ObjectPrimitive*& primitive,
					    double &res) const
{
  Ray           newRay;

  newRay = getRayAtSimplePosition(ray);
  double a = pow(newRay._vector._x, 4) + pow(newRay._vector._y, 4)
    + pow(newRay._vector._z, 4);
  double b = 4 * pow (newRay._vector._x, 3) * newRay._point._x +
    4 * pow (newRay._vector._y, 3) * newRay._point._y +
    4 * pow (newRay._vector._z, 3) * newRay._point._z;
  double c =
    6 * newRay._vector._x * newRay._vector._x * newRay._point._x *
    newRay._point._x - 5 * newRay._vector._x * newRay._vector._x +
    6 * newRay._vector._y * newRay._vector._y * newRay._point._y *
    newRay._point._y - 5 * newRay._vector._y * newRay._vector._y +
    6 * newRay._vector._z * newRay._vector._z * newRay._point._z *
    newRay._point._z - 5 * newRay._vector._z * newRay._vector._z;
  double d = 4 * newRay._vector._x * pow (newRay._point._x, 3)
    - 10 * newRay._vector._x * newRay._point._x +
    4 * newRay._vector._y * pow (newRay._point._y, 3)
    - 10 * newRay._vector._y * newRay._point._y +
    4 * newRay._vector._z * pow (newRay._point._z, 3)
    - 10 * newRay._vector._z * newRay._point._z;
  double e = pow (newRay._point._x, 4) - 5 * newRay._point._x *
    newRay._point._x + pow (newRay._point._y, 4) - 5 * newRay._point._y
    * newRay._point._y + pow (newRay._point._z, 4) - 5 * newRay._point._z
    * newRay._point._z + _coeff;
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

Vector          CubeTroue::getNormalVector(const Point& intersectPoint,
                                       const Vector& viewVector) const
{
  Point       intersection  = intersectPoint - _absolutePosition;

  intersection.rotate(_rotation, true);
  Vector normal;
  normal._x = 4.0 * pow(intersection._x, 3) - 10 * intersection._x;
  normal._y = 4.0 * pow(intersection._y, 3) - 10 * intersection._y;
  normal._z = 4.0 * pow(intersection._z, 3) - 10 * intersection._z;
  double cosA = viewVector * normal;
  cosA = cosA / (viewVector.getNorm() * normal.getNorm());
  if (cosA <= 0)
    return (normal.normalize() * -1);
  return (normal.normalize());
}

bool            CubeTroue::isInBoundingBox(BoundingBox& box) const
{
  return (true);
  (void)box;
}
