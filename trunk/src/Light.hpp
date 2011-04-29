//
// Camera.hpp for raytracer in /home/jochau_g//data/dev/c/raytracer/raytracer-42
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Tue Apr 26 18:54:28 2011 gael jochaud-du-plessix
// Last update Fri Apr 29 17:46:10 2011 samuel olivier
//

#ifndef _LIGHT_HPP_
#define _LIGHT_HPP_

#include "Point.hpp"
#include "Color.hpp"
#include "Ray.hpp"
#include "RenderingConfiguration.hpp"
#include "Object.hpp"

class Raytracer;

class Light
{
public:
  Light();
  Light(const Point &position, const Color& color, double intensity=1);
  ~Light();

  const Point&	getPosition(void) const;
  const Color&	getColor(void) const;
  double	getIntensity(void) const;

  void		setPosition(const Point& position);
  void		setColor(const Color& color);
  void		setIntensity(double intensity);

  virtual void
  getLighting(const ObjectPrimitive& primitive,
	      const Point& intersectPoint,
	      const Raytracer &raytracer,
	      Color& directLighting,
	      Color& specularLighting) const = 0;

protected:
  Point		_position;
  Color		_color;
  double	_intensity;
};

#endif
