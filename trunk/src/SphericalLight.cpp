//
// SphericalLight.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
//
// Made by loick michard
// Login   <michar_l@epitech.net>
//
// Started on  Fri Apr 29 16:51:44 2011 loick michard
// Last update Wed May 18 11:26:21 2011 samuel olivier
//

#include <cmath>
#include "SphericalLight.hpp"
#include "Raytracer.hpp"
#include "Sphere.hpp"

SphericalLight::SphericalLight(const Point &position,
			       double size,
			       const Color &color,
			       double intensity):
  Light(position, color, intensity), _directLightPow(10000), _size(size)
{

}

SphericalLight::SphericalLight(void) : _directLightPow(10000)
{

}

void	SphericalLight::setDirectLightPow(double value)
{
  _directLightPow = value;
}

void	SphericalLight::setSize(double value)
{
  _size = value;
}


double	SphericalLight::getDirectLightPow(void) const
{
  return (_directLightPow);
}

void	SphericalLight::getLighting(const ObjectPrimitive& primitive,
				    const Point& intersectPoint,
				    const Raytracer &raytracer,
				    const Vector& ray,
				    Color& directLighting,
				    Color& specularLighting) const
{
  Color		directLightTmp;
  Color		specularLightTmp;
  int		sampling =
    raytracer.getRenderingConfiguration()->getDiffuseShadingSampling();

  if (!raytracer.getRenderingConfiguration()->isDiffuseShadingEnabled())
    sampling = 1;
  for (int i = 0; i < sampling; i++)
    {
      Point	lightPoint =
	_position + Point(((double)rand() / RAND_MAX) * _size,
			  ((double)rand() / RAND_MAX) * _size,
			  ((double)rand() / RAND_MAX) * _size);
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

Color	SphericalLight::getDirectLighting(const Raytracer& raytracer,
					  Ray& ray) const
{
  Ray   lightRay = Ray(ray._point, _position - ray._point);
  Color lightColor = _color;
  double                k;
  ObjectPrimitive*      nearestObject;

  nearestObject = raytracer.getNearestObject(lightRay, k);
  if (nearestObject && k < 1)
    return (Color());
  double        scalar = lightRay._vector * ray._vector /
    (lightRay._vector.getNorm() * ray._vector.getNorm());

  if (scalar > 0)
    return (lightColor * scalar * pow(scalar, _directLightPow));
  return (Color());
}

void    SphericalLight::getRandomRay(Ray& ray) const
{
  ray.setPoint(_position);
  ray._vector.setVector(2 * ((double)rand() / RAND_MAX) - 1,
                        2 * ((double)rand() / RAND_MAX) - 1,
                        2 * ((double)rand() / RAND_MAX) - 1);
}
