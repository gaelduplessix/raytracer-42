//
// Plan.hpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Sat Apr 30 10:17:13 2011 loick michard
// Last update Sat Apr 30 17:40:48 2011 loick michard
//

#ifndef _PLAN_HPP_
#define _PLAN_HPP_

#include "ObjectPrimitive.hpp"

class Plan : public ObjectPrimitive
{
public:
  Plan(Object*object,
	 const Point& absolutePosition,
	 const Rotation& rotation,
	 const Material& material);

  void		        addIntersectionWithRay(const Ray& ray, vector<struct s_intersected_object>& intersection) const;
  void                  intersectWithRay(const Ray& ray, ObjectPrimitive*& primitive, double &res) const;
  Vector	getNormalVector(const Point& intersectPoint) const;
  Vector	getRefractedVector(const Point& intersectPoint,
                                           Vector& vector) const;
  bool		isInBoundingBox(BoundingBox& box) const;

};

#endif
