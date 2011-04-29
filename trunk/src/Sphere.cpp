//
// Sphere.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Fri Apr 29 10:41:20 2011 loick michard
// Last update Fri Apr 29 23:17:03 2011 gael jochaud-du-plessix
//

#include <vector>
#include "Sphere.hpp"
#include "EquationSolver.hpp"

Sphere::Sphere()
{

}

Sphere::Sphere(Object*object,
	       const Point& absolutePosition,
	       const Rotation& rotation,
	       const Material& material,
	       double radius) : ObjectPrimitive(object, absolutePosition,
						rotation, material),
				_radius(radius)
{

}

Sphere::~Sphere()
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
  const Vector&	newRayVector = newRay.getVector();
  const Point&	newRayPoint = newRay.getPoint();
  a = newRayVector._x * newRayVector._x +
    newRayVector._y * newRayVector._y +
    newRayVector._z * newRayVector._z;
  b = 2 * (newRayPoint._x * newRayVector._x +
	   newRayPoint._y * newRayVector._y +
	   newRayPoint._z * newRayVector._z);
  c = newRayPoint._x * newRayPoint._x +
    newRayPoint._y * newRayPoint._y +
    newRayPoint._z * newRayPoint._z -
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
