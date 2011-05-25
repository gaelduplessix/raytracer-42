//
// Texture.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Thu Apr 28 18:10:14 2011 loick michard
// Last update Wed May 25 09:53:19 2011 loick michard
//

#include <QString>
#include <QColor>
#include "Texture.hpp"

Texture::Texture()
{
  _type = 0;
}

Texture::Texture(const string& path, 
		 double repeatWidth, double repeatHeight)
{
  _type = 0;
  _name = path;
  _image = new QImage(QString(path.c_str()));
  _repeatWidth = repeatWidth;
  _repeatHeight = repeatHeight;
}

Texture::Texture(double repeatWidth, double repeatHeight):
  _repeatWidth(repeatWidth), _repeatHeight(repeatHeight)
{
  _image = NULL;
  _type = 0;
  _name = "";
}

Texture::~Texture()
{
  delete _image;
}

Color Texture::getColor(double x, double y) const
{
  x /= _repeatWidth;
  y /= _repeatHeight;
  if (x > 1)
    x = x - (int)x;
  if (y > 1)
    y = y - (int)y;
  if (x < 0)
    x = 1 + (x + (int)(-x));
  if (y < 0)
    y = 1 + (y + (int)(-y));
  return (this->getPixel(x, y));
}

Color Texture::getPixel(double x, double y) const
{
  if (_image)
    return (Color(_image->pixel(x * _image->width(),
                                y * _image->height())));
  else
    return (Color(255, 255, 255));
}

int    Texture::getWidth() const
{
  return (_image->width());
}

int    Texture::getHeight() const
{
  return (_image->height());
}
