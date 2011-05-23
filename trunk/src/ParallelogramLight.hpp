//
// ParallelogramLight.hpp for raytracer in /home/jochau_g//Desktop/raytracer-42/src
//
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
//
// Started on  Sun May  8 22:43:24 2011 gael jochaud-du-plessix
// Last update Mon May 23 13:07:54 2011 samuel olivier
//

#ifndef _PARALLELOGRAM_LIGHT_HPP_
#define _PARALLELOGRAM_LIGHT_HPP_

#include "Light.hpp"

class	ParallelogramLight : public Light
{
public :
  ParallelogramLight(void);
  ParallelogramLight(const Point &position1,
		     const Point &position2,
		     const Point &position3,
		     const Color& color,
		     double intensity=1);

  void   setDirectLightPow(double value);
  double getDirectLightPow(void) const;

  void getLighting(const ObjectPrimitive& primitive,
		   const Point& intersectPoint,
		   const Raytracer &raytracer,
		   const Vector& ray,
		   Color& directLighting,
		   Color& specularLighting) const;

  Color getDirectLighting(const Raytracer& raytracer,
			  Ray& ray) const;
  void	getRandomRay(Ray& ray) const;
  void	setPoint2(const Point& point2);
  void	setPoint3(const Point& point3);

private:
  double	_directLightPow;
  Point		_point2;
  Point		_point3;
};

#endif
