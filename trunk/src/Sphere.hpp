//
// Sphere.hpp for ratracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Fri Apr 29 10:36:38 2011 loick michard
// Last update Mon May  2 22:26:32 2011 loick michard
//

#ifndef _SHPERE_HPP_
#define _SHPERE_HPP_

#include "ObjectPrimitive.hpp"

class Sphere : public ObjectPrimitive
{
public:
  Sphere(Object*object,
	 const Point& absolutePosition,
	 const Rotation& rotation,
	 const Material& material,
	 double	radius);

  void			setRadius(double r);

  const Color& getColor(const Point& intersectPoint) const;
  void        addIntersectionWithRay(const Ray& ray, vector<struct s_intersected_object>& intersection) const;
  void                  intersectWithRay(const Ray& ray, ObjectPrimitive*& primitive, double &res) const;
  Vector	getNormalVector(const Point& intersectPoint,
				const Vector& viewVector) const;
  Vector	getRefractedVector(const Point& intersectPoint,
				   const Ray& ray) const;
  bool		isInBoundingBox(BoundingBox& box) const;


private:
  double	_radius;
};

#endif
