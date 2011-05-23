//
// ParallelogramLight.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
//
// Made by loick michard
// Login   <michar_l@epitech.net>
//
// Started on  Fri Apr 29 16:51:44 2011 loick michard
// Last update Mon May 23 13:07:39 2011 samuel olivier
//

#include <cmath>
#include "ParallelogramLight.hpp"
#include "Raytracer.hpp"
#include "Parallelogram.hpp"

ParallelogramLight::ParallelogramLight(void) : _directLightPow(10000)
{

}

ParallelogramLight::ParallelogramLight(const Point &position,
				       const Point &position2,
				       const Point &position3,
				       const Color &color,
				       double intensity):
  Light(position, color, intensity), _directLightPow(10000),
  _point2(position2), _point3(position3)
{

}

void	ParallelogramLight::setPoint2(const Point& point2)
{
  _point2 = point2;
}

void	ParallelogramLight::setPoint3(const Point& point3)
{
  _point3 = point3;
}

void	ParallelogramLight::setDirectLightPow(double value)
{
  _directLightPow = value;
}

double	ParallelogramLight::getDirectLightPow(void) const
{
  return (_directLightPow);
}

void	ParallelogramLight::getLighting(const ObjectPrimitive& primitive,
					const Point& intersectPoint,
					const Raytracer &raytracer,
					const Vector& ray,
					Color& directLighting,
					Color& specularLighting) const
{
  Color		directLightTmp;
  Color		specularLightTmp;
  Vector	vector1 = _point2 - _position;
  Vector	vector2 = _point3 - _position;
  int		sampling =
    raytracer.getRenderingConfiguration()->getDiffuseShadingSampling();

  if (!raytracer.getRenderingConfiguration()->isDiffuseShadingEnabled())
    sampling = 1;
  for (int i = 0; i < sampling; i++)
    {
      Point	lightPoint =
	_position + ((double)rand() / RAND_MAX) * vector1
	+ ((double)rand() / RAND_MAX) * vector2;
      if (!raytracer.getRenderingConfiguration()->isDiffuseShadingEnabled())
	lightPoint = _position;
      Vector	lightVector = lightPoint - intersectPoint;
      getLightingFromLightRay(lightVector,
			      primitive.getNormal(intersectPoint,
						  lightVector),
			      primitive.getReflectedVector(intersectPoint,
							   lightVector),
			      raytracer,
			      intersectPoint, ray,
			      primitive,
			      directLightTmp,
			      specularLightTmp);
      directLighting += directLightTmp;
      specularLighting += specularLightTmp;
    }
  directLighting /= sampling;
  specularLighting /= sampling;
  directLighting *= _intensity;
  specularLighting *= _intensity;
}

Color	ParallelogramLight::getDirectLighting(const Raytracer& raytracer,
					      Ray& ray) const
{
  Parallelogram		tmpPar(NULL, _position, _point2, _point3,
			       Rotation(0, 0, 0),
			       Material());
  ObjectPrimitive*	primitive = NULL;
  double		kLight = -1;

  tmpPar.intersectWithRay(ray, primitive, kLight);
  if (primitive)
    {
      Color lightColor = _color;
      double                k;
      ObjectPrimitive*      nearestObject;
      nearestObject = raytracer.getNearestObject(ray, k);
      if (nearestObject && k < kLight)
	return (Color());
      return (lightColor);
    }
  return (Color(0, 0, 0));
}

void    ParallelogramLight::getRandomRay(Ray& ray) const
{
  Vector	vector1 = _point2 - _position;
  Vector	vector2 = _point3 - _position;
  Point		lightPoint = _position + ((double)rand() / RAND_MAX) * vector1
    + ((double)rand() / RAND_MAX) * vector2;

  ray.setPoint(lightPoint);
  ray._vector.setVector(2 * ((double)rand() / RAND_MAX) - 1,
                        2 * ((double)rand() / RAND_MAX) - 1,
                        2 * ((double)rand() / RAND_MAX) - 1);
}
