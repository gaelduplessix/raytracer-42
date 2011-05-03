//
// PerlinNoise.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Tue May  3 17:14:13 2011 loick michard
// Last update Tue May  3 19:14:12 2011 loick michard
//

#include <cmath>
#include "PerlinNoise.hpp"

PerlinNoise::PerlinNoise(int width, int height):
  Texture(1, 1), _width(width), _height(height),
  _octaves(5), _step(40), _persistance(0.6)
{
  this->_initPerlinNoise();
}

PerlinNoise::PerlinNoise(double repeatWidth, double repeatHeight,
			 int width, int height):
  Texture(repeatWidth, repeatHeight), _width(width), _height(height),
  _octaves(5), _step(40), _persistance(0.6)
{
  this->_initPerlinNoise();
}

PerlinNoise::~PerlinNoise()
{
  delete _perlinNoise;
}
#include <iostream>
Color	PerlinNoise::getPixel(double x, double y) const
{
  x *= _width;
  y *= _height;

  double value = this->getPerlinNoise(x, y);
  //value = cos(x /_width + value);
  value = 20 * value;
  value = value - (int)(value);
  Color r(184, 133, 39);
  Color b(110, 54, 19);
  return Color((r._r * value + b._r * (1 - value)),
	       (r._g * value + b._g * (1 - value)),
	       (r._b * value + b._b * (1 - value)));
  
  return (Color(value, value, value));
}

void	PerlinNoise::_initPerlinNoise()
{
  int	maxWidth = (int)ceil(_width * pow(2, _octaves - 1) / _step);
  int	maxHeight = (int)ceil(_height * pow(2, _octaves - 1) / _step);

  _maxLenght = maxWidth;
  _perlinNoise = new double[maxWidth * maxHeight];
  srand(time(NULL));
  for (int i = 0; i < maxWidth * maxHeight; i++)
    _perlinNoise[i] = ((double) rand()) / RAND_MAX;
}

double PerlinNoise::get1DInterpolation(double a, double b, double x) const
{
  double k = (1 - cos(x * M_PI)) / 2;
  return (a * (1 - k) + b * k);
}

double PerlinNoise::get2DInterpolation(double a, double b, 
				     double c, double d,
				     double x, double y) const
{
  double y1 = get1DInterpolation(a, b, x);
  double y2 = get1DInterpolation(c, d, x);

  return  (get1DInterpolation(y1, y2, y));
}

double	PerlinNoise::get2DPerlinNoise(int i, int j) const
{
  return (_perlinNoise[i * _maxLenght + j]);
}

double	PerlinNoise::getNoise(double x, double y) const
{
  int	i = (int)(x / _step);
  int	j = (int)(y / _step);

  return (get2DInterpolation(get2DPerlinNoise(i, j),
			     get2DPerlinNoise(i + 1, j),
			     get2DPerlinNoise(i, j + 1),
			     get2DPerlinNoise(i + 1, j + 1),
			     fmod(x / _step, 1),
			     fmod(y / _step, 1)));
}

double	PerlinNoise::getPerlinNoise(double x, double y) const
{
  double somme = 0;
  double persistance = 1;
  int	 pow = 1;

  for (int i = 0; i < _octaves; i++)
    {
      somme += persistance * getNoise(x * pow, y * pow);
      persistance *= _persistance;
      pow *= 2;
    }
  return (somme * ((1 - _persistance) / (1 - persistance)));
}
