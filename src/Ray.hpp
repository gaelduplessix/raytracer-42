//
// Ray.hpp for raytracer in /home/michar_l//Raytracer
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Wed Apr 27 15:11:51 2011 loick michard
// Last update Thu May 12 16:56:17 2011 gael jochaud-du-plessix
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
  Ray(const Point& point,
      const Vector& vector);

  void		setPoint(const Point& point);
  void		setVector(const Vector& vector);
  void		setRefractiveIndex(double refractiveIndex);

  const Point&	getPoint() const;
  const Vector&	getVector() const;
  double	getRefractiveIndex() const;

  Point				_point;
  Vector			_vector;
  int				_reflectionLevel;
  double			_reflectionIntensity;
  int				_refractionLevel;
  double			_refractionIntensity;
  double			_refractiveIndex;
};

#endif
