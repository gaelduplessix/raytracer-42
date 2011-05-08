//
// ParallelLight.hpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Fri Apr 29 16:48:11 2011 loick michard
// Last update Sun May  8 20:40:33 2011 gael jochaud-du-plessix
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
                          const Ray& ray) const;
};

#endif
