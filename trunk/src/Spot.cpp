//
// Spot.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Fri Apr 29 16:51:44 2011 loick michard
// Last update Fri Apr 29 18:40:53 2011 samuel olivier
//

#include <cmath>
#include "Spot.hpp"

Spot::Spot()
{

}

Spot::Spot(const Point &position, const Color &color,
             double intensity):
  Light(position, color, intensity)
{

}

Spot::~Spot()
{

}

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
