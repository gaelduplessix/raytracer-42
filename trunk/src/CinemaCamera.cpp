//
// CinemaCamera.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Fri Apr 29 15:33:54 2011 loick michard
// Last update Fri Apr 29 16:21:14 2011 loick michard
//

#include "CinemaCamera.hpp"
#include "Rotation.hpp"
#include "Vector.hpp"

CinemaCamera::CinemaCamera()
{
  _width = 16;
  _height = 9;
  _focalLength = 16;
  _hasDepthOfField = false;
  _apertureSize = 0.9;
  _focus = 2;
}

Ray		CinemaCamera::getRay(double x, double y) const
{
  Vector	vector;
  Ray		ray;
  Rotation	rot = _rotation;

  vector.setX(_focalLength);
  vector.setY(_width * (x - 0.5));
  vector.setZ(_height * (y - 0.5));
  vector.rotate(rot);
  ray.setVector(vector);
  ray.setPoint(_position);
  ray.setRefractiveIndex(1);
  return (ray);
}

Ray		
CinemaCamera::getRayWithSampling(double x, double y,
				 double samplingPos) const
{
  return (this->getRay(x, y));
}
