//
// Plan.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Sat Apr 30 10:19:08 2011 loick michard
// Last update Sat Apr 30 13:48:21 2011 gael jochaud-du-plessix
//

#include <vector>
#include "Plan.hpp"

Plan::Plan(Object*object,
	       const Point& absolutePosition,
	       const Rotation& rotation,
	       const Material& material): 
  ObjectPrimitive(object, absolutePosition, rotation, material)
{

}

vector<double>	Plan::intersectWithRay(const Ray& ray) const
{
  Ray		newRay;
  vector<double> result;

  newRay = getRayAtSimplePosition(ray);
  if (newRay._vector._z == 0)
    return (result);
  result.push_back(- newRay._point._z / newRay._vector._z);
  return (result);
}

Vector		Plan::getNormalVector(const Point& intersectPoint) const
{
  Vector	normal(0, 0, 1);

  normal.rotate(_rotation);
  return (normal);
}

Vector		Plan::getReflectedVector(const Point& intersectPoint,
					   const Vector& vector) const
{

}

Vector		Plan::getRefractedVector(const Point& intersectPoint,
					   Vector& vector) const
{

}

bool		Plan::isInBoundingBox(BoundingBox& box) const
{

}
