//
// Texture.hpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Wed Apr 27 17:29:38 2011 loick michard
// Last update Fri May 27 14:25:42 2011 samuel olivier
//

#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_

#include <string>
#include <QImage>

#include "Color.hpp"

using namespace std;

class Texture
{
public:
  Texture();
  Texture(const string& path, 
	  double repeatWidth = 1, double repeatHeight = 1);
  Texture(double repeatWidth, double repeatHeight);
  ~Texture();

  virtual Color getColor(double x, double y) const;
  virtual Color getPixel(double x, double y) const;
  virtual int	getWidth() const;
  virtual int	getHeight() const;

  const string& getName(void);
  void  setName(const string& name);

  double	_repeatWidth;
  double	_repeatHeight;
  int		_type;
  QImage*	_image;
  string	_name;
};

#endif
