//
// ParallelLight.cpp for Raytracer in /home/olivie_a//rendu/cpp/raytracer-42
//
// Made by samuel olivier
// Login   <olivie_a@epitech.net>
//
// Started on  Thu May  5 10:39:44 2011 samuel olivier
// Last update Wed May 18 11:25:10 2011 samuel olivier
//

#include "Raytracer.hpp"
#include "ParallelLight.hpp"

ParallelLight::ParallelLight(const Point &direction, const Color& color,
			     double intensity) :
  Light(direction * -1, color, intensity)
{

}

ParallelLight::ParallelLight(void)
{

}

Color   ParallelLight::getDirectLighting(const Raytracer& raytracer,
					 Ray& ray) const
{
  return (Color());
  (void)raytracer;
  (void)ray;
}

#include <stdio.h>

void    ParallelLight::getLighting(const ObjectPrimitive& primitive,
				    const Point& intersectPoint,
				    const Raytracer &raytracer,
				    const Vector& ray,
				    Color& directLighting,
				    Color& specularLighting) const
{
  Ray		newRay(intersectPoint, _position);
  vector<t_intersected_object>  intersections;
  raytracer.getIntersectingObjects(newRay, intersections);
  Color		lightColor = _color;
  double	absorptionCoeff = getAbsorptionCoeff(intersections, newRay,
						     lightColor, false);
  Vector	normal = primitive.getNormalVector(intersectPoint, ray);
  double	scalar = (normal * _position * -1)
    / (normal.getNorm() * _position.getNorm());

  if (scalar > 0)
    directLighting = lightColor * _intensity * (1 - absorptionCoeff)
      * scalar;
  return ;
  (void)specularLighting;
}

void    ParallelLight::getRandomRay(Ray& ray) const
{
  ray.setPoint(_position);
  ray._vector.setVector(2 * ((double)rand() / RAND_MAX) - 1,
                        2 * ((double)rand() / RAND_MAX) - 1,
                        2 * ((double)rand() / RAND_MAX) - 1);
}
