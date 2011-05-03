//
// PerlinNoise.hpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Tue May  3 17:10:41 2011 loick michard
// Last update Tue May  3 18:11:20 2011 loick michard
//

#ifndef _PERLIN_NOISE_HPP_
#define _PERLIN_NOISE_HPP_

#include "Texture.hpp"
#include "Color.hpp"

class PerlinNoise : public Texture
{
public:
  PerlinNoise(int width = 100, int height = 100);
  PerlinNoise(double repeatWidth, double repeatHeight,
	      int width = 100, int height = 100);
  ~PerlinNoise();

  Color getPixel(double x, double y) const;

  double  getPerlinNoise(double x, double y) const;
  double  getNoise(double x, double y) const;
  double  get2DPerlinNoise(int i, int j) const;
  double  get2DInterpolation(double a, double b,
			     double c, double d,
			     double x, double y) const;
  double get1DInterpolation(double a,
			    double b, double x) const;

private:
  void		_initPerlinNoise();

  int		_width;
  int		_height;
  int		_maxLenght;
  double	_octaves;
  double	_step;
  double	_persistance;
  double*	_perlinNoise;
};

#endif
