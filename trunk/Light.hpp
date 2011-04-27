//
// Camera.hpp for raytracer in /home/jochau_g//data/dev/c/raytracer/raytracer-42
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Tue Apr 26 18:54:28 2011 gael jochaud-du-plessix
// Last update Wed Apr 27 14:57:25 2011 gael jochaud-du-plessix
//

#ifndef _LIGHT_HPP_
#define _LIGHT_HPP_

#include "Point.hpp"
#include "Color.hpp"

class Light
{
public:
  Light();
  ~Light();

  Point&	getPosition() const;
  Color&	getColor() const;
  double	getIntensity() const;

  void		setPosition(const Point& position);
  void		setColor(Color& color);
  void		setIntensity(double intensity);

  double	getDirectLightning(Ray& ray, Point& intersectPoint,
				   RenderingConfiguration& config);

private:
  Point		_position;
  Color		_color;
  double	_intensity;
};

#endif
