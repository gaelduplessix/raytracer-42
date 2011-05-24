//
// CubeMap.cpp for raytracer in /home/jochau_g//Desktop/raytracer-42/src
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Tue May  3 16:29:38 2011 gael jochaud-du-plessix
// Last update Mon May 23 18:11:31 2011 samuel olivier
//

#include "CubeMap.hpp"

#include <cmath>
#include <iostream>

CubeMap::CubeMap(const string& path)
{
  _facesFiles.resize(6);
  _facesFiles[CubeMap::Top] = new QImage((path + "/posy.jpg").c_str());
  _facesFiles[CubeMap::Left] = new QImage((path + "/posx.jpg").c_str());
  _facesFiles[CubeMap::Front] = new QImage((path + "/posz.jpg").c_str());
  _facesFiles[CubeMap::Right] = new QImage((path + "/negx.jpg").c_str());
  _facesFiles[CubeMap::Bottom] = new QImage((path + "/negy.jpg").c_str());
  _facesFiles[CubeMap::Rear] = new QImage((path + "/negz.jpg").c_str());
  for (uint i = 0; i < _facesFiles.size(); i++)
    if (_facesFiles[i]->isNull())
      throw CubeMap::ERROR_INVALID_FILE;
  _facesWidth = _facesFiles[CubeMap::Top]->width();
  _name = path;
}

CubeMap::~CubeMap()
{
  for (uint i = 0; i < _facesFiles.size(); i++)
    delete _facesFiles[i];
}

Color		CubeMap::_readFace(int face, double x, double y)
{
  return (_facesFiles[face]->pixel(x * _facesWidth,
				   y * _facesWidth));
}

Color		CubeMap::getMapColor(Vector viewVector)
{
  double	x, y;
  static double	sqrt2 = sqrt(2);
  static double	sqrt2_2 = sqrt(2) / 2;
  
  viewVector.normalize();  
  if (abs(viewVector._x) >= abs(viewVector._y)
      && abs(viewVector._x) >= abs(viewVector._z))
    {
      if (viewVector._x > 0)
	{
	  x = (viewVector._y + sqrt2_2) / sqrt2;
	  y = (viewVector._z + sqrt2_2) / sqrt2;
	  return (_readFace(CubeMap::Front, 1 - x, 1 - y));
	}
      else if (viewVector._x < 0)
	{
	  x = (viewVector._y + sqrt2_2) / sqrt2;
	  y = (viewVector._z + sqrt2_2) / sqrt2;
	  return (_readFace(CubeMap::Rear, x, 1 - y));
	}
    }
  else if (abs(viewVector._y) >= abs(viewVector._x)
      && abs(viewVector._y) >= abs(viewVector._z))
    {
      if (viewVector._y > 0)
  	{
  	  x = (viewVector._x + sqrt2_2) / sqrt2;
  	  y = (viewVector._z + sqrt2_2) / sqrt2;
  	  return (_readFace(CubeMap::Right, x, 1 - y));
  	}
      else if (viewVector._y < 0)
  	{
  	  x = (viewVector._x + sqrt2_2) / sqrt2;
  	  y = (viewVector._z + sqrt2_2) / sqrt2;
  	  return (_readFace(CubeMap::Left, 1 - x, 1 - y));
  	}
    }
  else if (abs(viewVector._z) >= abs(viewVector._x)
      && abs(viewVector._z) >= abs(viewVector._y))
    {
      if (viewVector._z > 0)
	{
	  x = (viewVector._y + sqrt2_2) / sqrt2;
	  y = (viewVector._x + sqrt2_2) / sqrt2;
	  return (_readFace(CubeMap::Top, 1 - x, y));
	}
      else if (viewVector._z < 0)
      	{
      	  x = (viewVector._y + sqrt2_2) / sqrt2;
      	  y = (viewVector._x + sqrt2_2) / sqrt2;
      	  return (_readFace(CubeMap::Bottom, 1 - x, y));
      	}
    }
  return (Color(0, 0, 0));
}
