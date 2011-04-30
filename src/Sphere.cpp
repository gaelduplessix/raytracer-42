//
// Sphere.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Fri Apr 29 10:41:20 2011 loick michard
// Last update Sat Apr 30 13:50:41 2011 gael jochaud-du-plessix
//

#include <vector>
#include "Sphere.hpp"
#include "EquationSolver.hpp"

Sphere::Sphere(Object*object,
	       const Point& absolutePosition,
	       const Rotation& rotation,
	       const Material& material,
	       double radius) : ObjectPrimitive(object, absolutePosition,
						rotation, material),
				_radius(radius)
{

}

void		Sphere::setRadius(double r)
{
  _radius = r;
}

vector<double>	Sphere::intersectWithRay(const Ray& ray) const
{
  Ray		newRay;
  double	a;
  double	b;
  double	c;

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
  return (EquationSolver::solveQuadraticEquation(a, b, c));
}

Vector		Sphere::getNormalVector(const Point& intersectPoint) const
{
  Vector	normal = intersectPoint - _absolutePosition;

  return (normal);
}

Vector		Sphere::getReflectedVector(const Point& intersectPoint,
					   const Vector& vector) const
{

}

Vector		Sphere::getRefractedVector(const Point& intersectPoint,
					   Vector& vector) const
{

}

bool		Sphere::isInBoundingBox(BoundingBox& box) const
{

}
