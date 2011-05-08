//
// CinemaCamera.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Fri Apr 29 15:33:54 2011 loick michard
// Last update Sun May  8 19:19:58 2011 loick michard
//

#include <stdlib.h>
#include "CinemaCamera.hpp"
#include "Rotation.hpp"
#include "Vector.hpp"

CinemaCamera::CinemaCamera()
{
  _width = 1.6;
  _height = 0.9;
  _focalLength = 1.6;
  _hasDepthOfField = false;
  _apertureSize = 0.2;
  _focus = 2;
}

CinemaCamera::CinemaCamera(Point position, Rotation rotation)
{
  _position = position;
  _rotation = rotation;
  _width = 1.6;
  _height = 0.9;
  _focalLength = 1.6;
  _hasDepthOfField = false;
  _apertureSize = 0.2;
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
  if (_hasDepthOfField)
    {
      Vector        vector(_focalLength,
                           _width * (x - 0.5),
                           _height * (0.5 - y));
      if (_rotation._x || _rotation._y || _rotation._z)
	vector.rotate(_rotation);
      Point start = _position + vector;
      vector.normalize();
      Point end = start + vector * ((_focus - 1.0 - _focalLength)
				    / vector._x);
      Vector disturb;
      disturb._y = (_apertureSize / RAND_MAX) * (1.0f * rand());
      disturb._z = (_apertureSize / RAND_MAX) * (1.0f * rand());
      disturb._x = 0.0f;
      vector += disturb;
      Point rstart = start + vector * (1.0 / vector._x);
      return (Ray(rstart, end - rstart));
    }  
  else
    return (getRay(x, y));
}
