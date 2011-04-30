//
// Ray.hpp for raytracer in /home/michar_l//Raytracer
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Wed Apr 27 15:11:51 2011 loick michard
// Last update Sat Apr 30 12:42:15 2011 gael jochaud-du-plessix
//

#ifndef _RAY_HPP_
#define _RAY_HPP_

#include "Color.hpp"
#include "Point.hpp"
#include "Vector.hpp"

class Ray
{
public:
  Ray();
  Ray(const Color& color, const Point& point,
      const Vector& vector, double refractiveIndex);
  ~Ray();

  void		setColor(const Color& color);
  void		setPoint(const Point& point);
  void		setVector(const Vector& vector);
  void		setRefractiveIndex(double refractiveIndex);

  const Color&	getColor() const;
  const Point&	getPoint() const;
  const Vector&	getVector() const;
  double	getRefractiveIndex() const;

public:
  Color		_color;
  Point		_point;
  Vector	_vector;
  double	_refractiveIndex;
};

#endif
