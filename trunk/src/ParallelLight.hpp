//
// ParallelLight.hpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Fri Apr 29 16:48:11 2011 loick michard
// Last update Mon May  9 00:08:16 2011 gael jochaud-du-plessix
//

#ifndef _PARALLELLIGHT_HPP_
#define _PARALLELLIGHT_HPP_

#include "Light.hpp"

class	ParallelLight : public Light
{
public :
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
};

#endif
