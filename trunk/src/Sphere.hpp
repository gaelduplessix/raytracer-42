//
// Sphere.hpp for ratracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Fri Apr 29 10:36:38 2011 loick michard
// Last update Sat Apr 30 13:50:53 2011 gael jochaud-du-plessix
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
