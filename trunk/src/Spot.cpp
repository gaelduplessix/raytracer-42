//
// Spot.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Fri Apr 29 16:51:44 2011 loick michard
// Last update Fri Apr 29 17:26:27 2011 loick michard
//

#include <cmath>
#include "Spot.hpp"

void	Spot::getLighting(const ObjectPrimitive& primitive,
			  const Point& intersectPoint,
			  const Raytracer &raytracer,
			  Color& directLighting,
			  Color& specularLighting) const
{
  Vector	lightVector = _position - intersectPoint;
  Vector	normal = primitive.getNormalVector(intersectPoint);
  double	scalar = lightVector * normal;
  double	cosa = scalar / 
    (lightVector.getNorm() *normal.getNorm());

  directLighting = _color * cosa;
}
