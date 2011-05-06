//
// Spot.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Fri Apr 29 16:51:44 2011 loick michard
// Last update Thu May  5 19:35:35 2011 samuel olivier
//

#include <cmath>
#include "Spot.hpp"
#include "Raytracer.hpp"

Spot::Spot(const Point &position, const Color &color,
             double intensity):
  Light(position, color, intensity), _directLightPow(10000)
{

}

void	Spot::setDirectLightPow(double value)
{
  _directLightPow = value;
}

double	Spot::getDirectLightPow(void) const
{
  return (_directLightPow);
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
			  primitive.getNormal(intersectPoint,
					      lightVector),
			  primitive.getReflectedVector(intersectPoint,
						       lightVector),
			  raytracer,
			  intersectPoint, ray,
			  primitive,
			  directLighting,
			  specularLighting);
  directLighting *= _intensity;
  specularLighting *= _intensity;
}

Color	Spot::getDirectLighting(const Raytracer& raytracer,
				const Ray& ray) const
{
  Ray	lightRay = Ray(ray._point, _position - ray._point);
  vector<t_intersected_object>  intersections;
  raytracer.getIntersectingObjects(ray, intersections);
  Color         lightColor = _color;
  double        absorptionCoeff = getAbsorptionCoeff(intersections, lightRay,
                                                     lightColor);
  double	scalar = lightRay._vector * ray._vector /
    (lightRay._vector.getNorm() * ray._vector.getNorm());
  
  if (scalar > 0)
    return (lightColor * scalar * pow(scalar, _directLightPow)
	    * (1 - absorptionCoeff));
  return (Color());
}
