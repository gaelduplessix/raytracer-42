//
// Light.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Wed Apr 27 19:02:25 2011 loick michard
// Last update Wed Jun  8 11:01:21 2011 samuel olivier
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


double
Light::getAbsorptionCoeff(vector<t_intersected_object>& intersections,
			  Ray& lightRay, Color& lightColor, bool limited) const
{
  double	coeff = 0;
  int		nbIntersect = intersections.size();
  int		nbK;

  for (int i = 0; i < nbIntersect && coeff < 1; i++)
    {
      nbK = intersections[i].k.size();
      for (int j = 0; j < nbK; j++)
	{
	  if (!limited || intersections[i].k[j] < 1)
	    {
	      Point intersectPoint = lightRay._point + lightRay._vector
		* intersections[i].k[j];
	      Color objectColor =
		intersections[i].primitive->getColor(intersectPoint);
	      lightColor &= objectColor;
	      coeff += 1 -
	      	intersections[i].primitive->getMaterial()
	      	->getTransmissionCoeff();
	    }
	}
    }
  if (coeff > 1)
    coeff = 1;
  return (coeff);
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
  Ray           ray(intersectPoint, lightVector);
  const RenderingConfiguration* renderConf = 
    raytracer.getRenderingConfiguration();

  Color		lightColor = _color;
  double	absorptionCoeff = 0;
  if (!renderConf->isTransparencyEnabled()
      || renderConf->isPhotonMappingEnabled())
    {
      double                k = -1;
      ObjectPrimitive*      nearestObject = NULL;
      nearestObject = raytracer.getNearestObject(ray, k);
      if (nearestObject && k < 1)
	return ;
    }
  else
    {
      vector<t_intersected_object>	intersections;
      raytracer.getIntersectingObjects(ray, intersections);
      absorptionCoeff = getAbsorptionCoeff(intersections, ray,
					   lightColor);
    }
  double	scalar;
  double	minAmbiant = renderConf->getMinimalAmbiantLighting();

  if (renderConf->isDiffuseLighting())
    {
      scalar = lightVector * normal /
	(lightVector.getNorm() * normal.getNorm());
      if (scalar < minAmbiant && renderConf->isMinimalAmbiantLighting())
	scalar = minAmbiant;
      if (scalar > 0)
	directLighting = lightColor * scalar * (1 - absorptionCoeff);
    }
  if (renderConf->isSpecularLighting())
    {
      scalar = reflectedVector * viewRay /
	(reflectedVector.getNorm() * viewRay.getNorm());
      if (scalar > 0)
	specularLighting =
	  lightColor * pow(scalar, primitive.getMaterial()->getSpecularPow())
	  * (1 - absorptionCoeff);
    }
}
