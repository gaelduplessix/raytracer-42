//
// ParrallelLight.hpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Fri Apr 29 16:48:11 2011 loick michard
// Last update Thu May  5 14:39:22 2011 samuel olivier
//

#ifndef _PARRALLELLIGHT_HPP_
#define _PARRALLELLIGHT_HPP_

#include "Light.hpp"

class	ParrallelLight : public Light
{
public :
  ParrallelLight(const Vector &direction, const Color& color,
		 double intensity = 1);

  void getLighting(const ObjectPrimitive& primitive,
                   const Point& intersectPoint,
                   const Raytracer &raytracer,
                   const Vector& ray,
                   Color& directLighting,
                   Color& specularLighting) const;

  Color getDirectLighting(const Raytracer& raytracer,
                          const Ray& ray) const;
};

#endif
