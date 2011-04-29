//
// Sphere.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Fri Apr 29 10:41:20 2011 loick michard
// Last update Fri Apr 29 18:45:02 2011 samuel olivier
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
  a = ray.getVector().getX() * ray.getVector().getX() +
    ray.getVector().getY() * ray.getVector().getY() +
    ray.getVector().getZ() * ray.getVector().getZ();
  b = 2 * (ray.getPoint().getX() * ray.getVector().getX() +
	   ray.getPoint().getY() * ray.getVector().getY() +
	   ray.getPoint().getZ() * ray.getVector().getZ());
  c = ray.getPoint().getX() * ray.getPoint().getX() +
    ray.getPoint().getY() * ray.getPoint().getY() +
    ray.getPoint().getZ() * ray.getPoint().getZ() -
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
