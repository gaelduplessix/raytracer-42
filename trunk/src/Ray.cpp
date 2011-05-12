//
// Ray.cpp for raytracer in /home/olivie_a//rendu/cpp/raytracer-42
// 
// Made by samuel olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  Thu Apr 28 18:50:52 2011 samuel olivier
// Last update Thu May 12 16:56:21 2011 gael jochaud-du-plessix
//

#include "Ray.hpp"

Ray::Ray():
  _point(Point(0, 0, 0)), _vector(0, 0, 0),
  _reflectionLevel(0), _reflectionIntensity(1),
  _refractionLevel(0), _refractionIntensity(1), _refractiveIndex(1)
{

}

Ray::Ray(const Point& point, const Vector& vector):
  _point(point), _vector(vector), _reflectionLevel(0), _reflectionIntensity(1),
  _refractionLevel(0), _refractionIntensity(1), _refractiveIndex(1)
{
}

const Point&	Ray::getPoint() const
{
  return (_point);
}

const Vector&	Ray::getVector() const
{
  return (_vector);
}

double	Ray::getRefractiveIndex() const
{
  return (_refractiveIndex);
}

void	Ray::setPoint(const Point& point)
{
  _point = point;
}

void	Ray::setVector(const Vector& vector)
{
  _vector = vector;
}

void	Ray::setRefractiveIndex(double refractiveIndex)
{
  _refractiveIndex = refractiveIndex;
}
