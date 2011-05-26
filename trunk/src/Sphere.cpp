//
// Sphere.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
//
// Made by loick michard
// Login   <michar_l@epitech.net>
//
// Started on  Fri Apr 29 10:41:20 2011 loick michard
// Last update Thu May 26 14:30:56 2011 samuel olivier
//

#include <cmath>
#include <vector>
#include "Raytracer.hpp"
#include "Sphere.hpp"
#include "EquationSolver.hpp"

Sphere::Sphere(Object*object,
	       const Point& absolutePosition,
	       const Rotation& rotation,
	       Material* material,
	       double radius) : ObjectPrimitive(object, absolutePosition,
						rotation, material),
				_radius(radius)
{
  
}

Sphere::Sphere(void) : ObjectPrimitive(NULL, Point(0, 0, 0),
				       Rotation(0, 0, 0), NULL),
		       _radius(1)
{

}

void		Sphere::setRadius(double r)
{
  _radius = r;
}

void		Sphere::getMappedCoords(const Point& intersectPoint,
				double& x, double &y) const
{
  Point newPoint = intersectPoint - _absolutePosition;
  Vector vn(0, 0, -1);
  Vector ve(1, 0, 0);

  newPoint.rotate(_rotation);
  newPoint.normalize();
  double phi = acos(- (vn * newPoint));
  double x2 = phi / M_PI;
  double angle = (newPoint * ve) / sin(phi);
  if (angle < -1)
    angle = -1;
  else if (angle > 1)
    angle = 1;
  double theta = (acos(angle)) / (2 * M_PI);
  vn *= ve;
  double y2;
  if (vn * newPoint > 0)
    y2 = theta;
  else
    y2 =  1 - theta;
  x = y2;
  y = x2;
}

void        Sphere::addIntersectionWithRay(const Ray& ray, vector<struct s_intersected_object>& intersection) const
{
  Ray           newRay;
  double        a;
  double        b;
  double        c;

  newRay = getRayAtSimplePosition(ray);
  a = newRay._vector._x * newRay._vector._x +
    newRay._vector._y * newRay._vector._y +
    newRay._vector._z * newRay._vector._z;
  b = 2 * (newRay._point._x * newRay._vector._x +
           newRay._point._y * newRay._vector._y +
           newRay._point._z * newRay._vector._z);
  c = newRay._point._x * newRay._point._x +
    newRay._point._y * newRay._point._y +
    newRay._point._z * newRay._point._z -
    _radius * _radius;
  vector<double> solutions =
    EquationSolver::solveQuadraticEquation(a, b, c);
  vector<double> validSolutions;
  for (unsigned int i = 0 ; i < solutions.size(); i++)
    if (solutions[i] > EPSILON)
      {
	Point	intersectPoint = ray._point + ray._vector * solutions[i];
	double x, y;
	getMappedCoords(intersectPoint, x, y);
	if (!_material->isLimitedAtPoint(x, y))
	  validSolutions.push_back(solutions[i]);
      }
  if (validSolutions.size() > 0)
    intersection.push_back((t_intersected_object){this, validSolutions});
}

void                  Sphere::intersectWithRay(const Ray& ray,
					       ObjectPrimitive*& primitive,
					       double &res) const
{
  Ray           newRay;
  double        a;
  double        b;
  double        c;

  newRay = getRayAtSimplePosition(ray);
  a = newRay._vector._x * newRay._vector._x +
    newRay._vector._y * newRay._vector._y +
    newRay._vector._z * newRay._vector._z;
  b = 2 * (newRay._point._x * newRay._vector._x +
           newRay._point._y * newRay._vector._y +
           newRay._point._z * newRay._vector._z);
  c = newRay._point._x * newRay._point._x +
    newRay._point._y * newRay._point._y +
    newRay._point._z * newRay._point._z -
    _radius * _radius;
  vector<double> solutions =
    EquationSolver::solveQuadraticEquation(a, b, c);
  for (unsigned int i = 0; i < solutions.size(); i++)
    {
      if (solutions[i] > EPSILON && (solutions[i] < res ||  res < 0))
        {
	  Point	intersectPoint = ray._point + ray._vector * solutions[i];
	  double x, y;
	  getMappedCoords(intersectPoint, x, y);
	  if (!_material->isLimitedAtPoint(x, y))
	    {
	      primitive = (ObjectPrimitive*)this;
	      res = solutions[i];
	    }
	}
    }
}

Vector		Sphere::getNormalVector(const Point& intersectPoint,
					const Vector& viewVector) const
{
  Point		intersect = intersectPoint - _absolutePosition;
  intersect.rotate(_rotation, true);
  intersect += _absolutePosition;
  Vector	normal = intersect - _absolutePosition;
  double	cosA = viewVector * normal;

  cosA = cosA / (viewVector.getNorm() * normal.getNorm());
  if (cosA <= 0)
    return (normal.normalize() * -1);
  return (normal.normalize());
}

bool		Sphere::isInBoundingBox(BoundingBox& box) const
{
  box = box;
  return (true);
}
