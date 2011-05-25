//
// PerlinNoise.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Tue May  3 17:14:13 2011 loick michard
// Last update Wed May 25 18:31:55 2011 loick michard
//

#include <cmath>
#include "PerlinNoise.hpp"

PerlinNoise::PerlinNoise(double repeatWidth, double repeatHeight,
			 int width, int height):
  Texture(repeatWidth, repeatHeight), _width(width), _height(height),
  _octaves(5), _step(40), _persistance(0.6), _woodEffect(false),
  _marbleEffect(false), _color1(0, 0, 0), _color2(255, 255, 255)
{
  _type = 1;
  this->_initPerlinNoise();
}

PerlinNoise::~PerlinNoise()
{
  delete _perlinNoise;
}

void	PerlinNoise::setWoodProperties()
{
  _octaves = 5;
  _step = 40;
  _persistance = 0.6;
  _woodEffect = true;
  _color1 = Color(184, 133, 39);
  _color2 = Color(110, 54, 19);
  _type = 2;
}

void    PerlinNoise::setMarbleProperties()
{
  _octaves = 5;
  _step = 60;
  _persistance = 0.9;
  _marbleEffect = true;
  _color1 = Color(240, 233, 234);
  _color2 = Color(7, 94, 34);
  _type = 3;
}

void	PerlinNoise::setColor1(const Color& color1)
{
  _color1 = color1;
}

void	PerlinNoise::setColor2(const Color& color2)
{
  _color2 = color2;
}

void	PerlinNoise::setOctaves(double octaves)
{
  _octaves = octaves;
}

void    PerlinNoise::setStep(double step)
{
  _step = step;
}

void    PerlinNoise::setPersistance(double persistance)
{
  _persistance = persistance;
}

int	PerlinNoise::getWidth() const
{
  return (_width);
}

int	PerlinNoise::getHeight()const
{
  return (_height);
}

Color	PerlinNoise::getPixel(double x, double y) const
{
  x *= _width;
  y *= _height;

  double value = this->getPerlinNoise(x, y);
  if (_woodEffect)
    {
      value = 20 * value;
      value = value - (int)(value);
    }
  return Color((_color1._r * value + _color2._r * (1 - value)),
	       (_color1._g * value + _color2._g * (1 - value)),
	       (_color1._b * value + _color2._b * (1 - value)));
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
