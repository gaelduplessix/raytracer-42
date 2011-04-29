//
// Camera.hpp for raytracer in /home/jochau_g//data/dev/c/raytracer/raytracer-42
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Tue Apr 26 18:54:28 2011 gael jochaud-du-plessix
// Last update Thu Apr 28 19:18:57 2011 loick michard
//

#ifndef _LIGHT_HPP_
#define _LIGHT_HPP_

#include "Point.hpp"
#include "Color.hpp"
#include "Ray.hpp"
#include "RenderingConfiguration.hpp"

class Light
{
public:
  Light();
  ~Light();

  Point&	getPosition() const;
  Color&	getColor() const;
  double	getIntensity() const;

  void		setPosition(const Point& position);
  void		setColor(const Color& color);
  void		setIntensity(double intensity);

  virtual double
  getDirectLightning(const Ray& ray,
		     const Point& intersectPoint,
		     const RenderingConfiguration& config) const = 0;

private:
  Point		_position;
  Color		_color;
  double	_intensity;
};

#endif
