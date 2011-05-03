//
// CinemaCamera.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Fri Apr 29 15:33:54 2011 loick michard
// Last update Tue May  3 21:57:18 2011 gael jochaud-du-plessix
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

CinemaCamera::CinemaCamera(Point position, Rotation rotation)
{
  _position = position;
  _rotation = rotation;
  _width = 16;
  _height = 9;
  _focalLength = 16;
  _hasDepthOfField = false;
  _apertureSize = 0.9;
  _focus = 2;
}

Ray		CinemaCamera::getRay(double x, double y) const
{
  Vector	vector(_focalLength,
  		       _width * (x - 0.5),
  		       _height * (0.5 - y));
  if (_rotation._x || _rotation._y || _rotation._z)
    vector.rotate(_rotation);
  return (Ray(_position, vector));
}

Ray		
CinemaCamera::getRayWithSampling(double x, double y,
				 double samplingPos) const
{
  return (this->getRay(x, y));
}
