//
// Plan.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Sat Apr 30 10:19:08 2011 loick michard
// Last update Sat Apr 30 20:45:39 2011 loick michard
//

#include <vector>
#include "Raytracer.hpp"
#include "Plan.hpp"

Plan::Plan(Object*object,
	       const Point& absolutePosition,
	       const Rotation& rotation,
	       const Material& material): 
  ObjectPrimitive(object, absolutePosition, rotation, material)
{

}

void		       Plan::addIntersectionWithRay(const Ray& ray, vector<struct s_intersected_object>& intersection) const
{
  Ray           newRay;

  newRay = getRayAtSimplePosition(ray);
  if (newRay._vector._z == 0)
    return ;
  double result(- newRay._point._z / newRay._vector._z);
  if (result < EPSILON)
    return ;
  vector<double> k;
  k.push_back(result);
  intersection.push_back((t_intersected_object){this, k});
}

void                  Plan::intersectWithRay(const Ray& ray, ObjectPrimitive*& primitive, double &res) const
{
  Ray           newRay;

  newRay = getRayAtSimplePosition(ray);
  if (newRay._vector._z == 0)
    return ;
  double result(- newRay._point._z / newRay._vector._z);
  if (result <= EPSILON)
    return ;
  if (result < res || res < 0)
    {
      primitive = (ObjectPrimitive*)this;
      res = result;
    }
}

Vector		Plan::getNormalVector(const Point& intersectPoint) const
{
  Vector	normal(0, 0, 100);

  normal.rotate(_rotation);
  return (normal);
}

Vector		Plan::getRefractedVector(const Point& intersectPoint,
					   Vector& vector) const
{

}

bool		Plan::isInBoundingBox(BoundingBox& box) const
{

}
