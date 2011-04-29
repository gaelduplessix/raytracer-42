//
// Sphere.hpp for ratracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Fri Apr 29 10:36:38 2011 loick michard
// Last update Fri Apr 29 18:31:01 2011 samuel olivier
//

#ifndef _SHPERE_HPP_
#define _SHPERE_HPP_

#include "ObjectPrimitive.hpp"

class Sphere : public ObjectPrimitive
{
public:
  Sphere();
  Sphere(Object*object,
	 const Point& absolutePosition,
	 const Rotation& rotation,
	 const Material& material,
	 double	radius);

  ~Sphere();

  void			setRadius(double r);

  vector<double>	intersectWithRay(const Ray& ray) const;

  Vector	getNormalVector(const Point& intersectPoint) const;
  Vector	getReflectedVector(const Point& intersectPoint,
                                           const Vector& vector) const;
  Vector	getRefractedVector(const Point& intersectPoint,
                                           Vector& vector) const;
  bool		isInBoundingBox(BoundingBox& box) const;


private:
  double	_radius;
};

#endif
