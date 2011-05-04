//
// Spot.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Fri Apr 29 16:51:44 2011 loick michard
// Last update Wed May  4 22:27:56 2011 gael jochaud-du-plessix
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
			  primitive.getNormal(intersectPoint,
					      lightVector),
			  primitive.getReflectedVector(intersectPoint,
						       lightVector),
			  raytracer,
			  intersectPoint, ray,
			  primitive,
			  directLighting,
			  specularLighting);
}

Color Spot::getDirectLighting(const Raytracer& raytracer,
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
    return (lightColor * scalar * pow(scalar, 10000) * (1 - absorptionCoeff));
  return (Color());
}
