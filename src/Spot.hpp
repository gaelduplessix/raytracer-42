//
// Spot.hpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Fri Apr 29 16:48:11 2011 loick michard
// Last update Fri Apr 29 18:25:57 2011 samuel olivier
//

#ifndef _SPOT_HPP_
#define _SPOT_HPP_

#include "Light.hpp"

class	Spot : public Light
{
public :
  Spot();
  Spot(const Point &position, const Color& color, double intensity=1);
  ~Spot();

  void getLighting(const ObjectPrimitive& primitive,
		   const Point& intersectPoint,
		   const Raytracer &raytracer,
		   Color& directLighting,
		   Color& specularLighting) const;
};

#endif
