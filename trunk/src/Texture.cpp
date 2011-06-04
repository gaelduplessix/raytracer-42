//
// Texture.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Thu Apr 28 18:10:14 2011 loick michard
// Last update Sat Jun  4 18:52:40 2011 gael jochaud-du-plessix
//

#include <QString>
#include <QColor>
#include <fstream>

#include "Resources.hpp"
#include "Texture.hpp"

Texture::Texture(): _repeatWidth(1), _repeatHeight(1), _type(0), _image(NULL),
		    _name("")
{
}

Texture::Texture(const string& path, 
		 double repeatWidth, double repeatHeight):
  _repeatWidth(repeatWidth), _repeatHeight(repeatHeight), _type(0), _name(path)
{
  _image = new QImage(QString(Resources::getNewPathName(path).c_str()));
}

Texture::Texture(double repeatWidth, double repeatHeight):
  _repeatWidth(repeatWidth), _repeatHeight(repeatHeight), _type(0),
  _image(NULL), _name("")
{
}

Texture::~Texture()
{
  if (_image)
    delete _image;
}

Color Texture::getColor(double x, double y) const
{
  x /= _repeatWidth;
  y /= _repeatHeight;
  if (x >= 1)
    x = x - (int)x;
  if (y >= 1)
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

const string&	Texture::getName(void)
{
  return (_name);
}

void		Texture::setName(const string& name)
{
  _name = name;
}
