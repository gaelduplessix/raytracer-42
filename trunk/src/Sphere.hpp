//
// Sphere.hpp for ratracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Fri Apr 29 10:36:38 2011 loick michard
// Last update Fri Apr 29 14:00:40 2011 loick michard
//

#ifndef _SHPERE_HPP_
#define _SHPERE_HPP_

#include "ObjectPrimitive.hpp"

class Sphere : public ObjectPrimitive
{
public:
  void		setRadius(double r);

  vector<double>	intersectWithRay(const Ray& ray) const;
  Vector		getNormalVector(const Point& intersectPoint) const;

private:
  double	_radius;
};

#endif
