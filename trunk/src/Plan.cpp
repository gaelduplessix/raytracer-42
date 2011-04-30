//
// Plan.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Sat Apr 30 10:19:08 2011 loick michard
// Last update Sat Apr 30 11:09:25 2011 loick michard
//

#include <vector>
#include "Plan.hpp"

Plan::Plan()
{

}

Plan::Plan(Object*object,
	       const Point& absolutePosition,
	       const Rotation& rotation,
	       const Material& material): 
  ObjectPrimitive(object, absolutePosition, rotation, material)
{

}

Plan::~Plan()
{

}
#include <iostream>
vector<double>	Plan::intersectWithRay(const Ray& ray) const
{
  Ray		newRay;
  vector<double> result;

  newRay = getRayAtSimplePosition(ray);
  if (newRay.getVector()._z == 0)
    return (result);
  result.push_back(- newRay.getPoint()._z / newRay.getVector()._z);
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
