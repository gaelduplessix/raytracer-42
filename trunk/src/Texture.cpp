//
// Texture.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Thu Apr 28 18:10:14 2011 loick michard
// Last update Tue May  3 12:01:54 2011 gael jochaud-du-plessix
//

#include <QString>
#include <QColor>
#include "Texture.hpp"

Texture::Texture(const string& path)
{
  _image = new QImage(QString(path.c_str()));
}

Texture::~Texture()
{

}
#include <iostream>
Color Texture::getColor(double x, double y) const
{
  int	xi;
  int	yi;

  if (x > 1)
    x = x - (int)x;
  if (y > 1)
    y = y - (int)y;
  if (x < 0)
    x = 1 + (x + (int)(-x));
  if (y < 0)
    y = 1 + (y + (int)(-y));
  xi = x * _image->width();
  yi = y * _image->height();
  if (_image)
    return (Color(_image->pixel(xi, yi)));
  else
    return (Color(255, 255, 255));
}
