//
// Spot.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Fri Apr 29 16:51:44 2011 loick michard
// Last update Sat Apr 30 18:43:39 2011 loick michard
//

#include <cmath>
#include "Spot.hpp"
#include "Raytracer.hpp"

Spot::Spot(const Point &position, const Color &color,
             double intensity):
  Light(position, color, intensity)
{

}

void	Spot::getLighting(const ObjectPrimitive& primitive,
			  const Point& intersectPoint,
			  const Raytracer &raytracer,
			  const Vector& ray,
			  Color& directLighting,
			  Color& specularLighting) const
{
  Vector	lightVector = _position - intersectPoint;

  getLightingFromLightRay(lightVector,
			  primitive.getNormalVector(intersectPoint),
			  primitive.getReflectedVector(intersectPoint,
						       lightVector),
			  raytracer,
			  intersectPoint, ray,
			  directLighting,
			  specularLighting);
}
