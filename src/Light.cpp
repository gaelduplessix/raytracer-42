//
// Light.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Wed Apr 27 19:02:25 2011 loick michard
// Last update Mon May  2 17:27:34 2011 gael jochaud-du-plessix
//

#include <cmath>

#include "Light.hpp"
#include "Raytracer.hpp"

Light::Light()
{

}

Light::Light(const Point &position, const Color &color,
	     double intensity):
  _position(position), _color(color), _intensity(intensity)
{
  
}

Light::~Light()
{
  
}

const Point&	Light::getPosition(void) const
{
  return (_position);
}

const Color&	Light::getColor(void) const
{
  return (_color);
}

double		Light::getIntensity(void) const
{
  return (_intensity);
}

void		Light::setPosition(const Point& position)
{
  _position = position;
}

void		Light::setColor(const Color& color)
{
  _color = color;
}

void		Light::setIntensity(double intensity)
{
  _intensity = intensity;
}

void		
Light::getLightingFromLightRay(const Vector& lightVector,
			       const Vector& normal,
			       const Vector& reflectedVector,
			       const Raytracer& raytracer,
			       const Point& intersectPoint,
			       const Vector& viewRay,
			       const ObjectPrimitive& primitive,
			       Color& directLighting,
			       Color& specularLighting) const
{
  Ray           ray(Color(), intersectPoint, lightVector, 1);
  double        k = -1;
  const ObjectPrimitive*    nearestObject =
    raytracer.getNearestObject(ray, k);

  if (!(nearestObject && k <= 1 && k > EPSILON))
    {
      double scalar;
      if (raytracer.getRenderingConfiguration()->isDirectLighting())
	{
	  scalar = lightVector * normal /
	    (lightVector.getNorm() * normal.getNorm());
	  directLighting = _color * scalar;
	}
      if (raytracer.getRenderingConfiguration()->isSpecularLighting())
	{
	  scalar = reflectedVector * viewRay /
	    (reflectedVector.getNorm() * viewRay.getNorm());
	  if (scalar > 0)
	    specularLighting =
	      _color * pow(scalar, primitive.getMaterial().getSpecularPow());
	}
    }
}
