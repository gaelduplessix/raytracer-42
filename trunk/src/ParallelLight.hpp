//
// ParallelLight.hpp for raytracer in /home/michar_l//Raytracer/raytracer-42
//
// Made by loick michard
// Login   <michar_l@epitech.net>
//
// Started on  Fri Apr 29 16:48:11 2011 loick michard
// Last update Wed May 18 11:24:06 2011 samuel olivier
//

#ifndef _PARALLELLIGHT_HPP_
#define _PARALLELLIGHT_HPP_

#include "Light.hpp"

class	ParallelLight : public Light
{
public :
  ParallelLight(void);
  ParallelLight(const Vector &direction, const Color& color,
		double intensity = 1);

  void getLighting(const ObjectPrimitive& primitive,
                   const Point& intersectPoint,
                   const Raytracer &raytracer,
                   const Vector& ray,
                   Color& directLighting,
                   Color& specularLighting) const;

  Color getDirectLighting(const Raytracer& raytracer,
                          Ray& ray) const;
  void	getRandomRay(Ray& ray) const;
};

#endif
