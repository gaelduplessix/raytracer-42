//
// Texture.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Thu Apr 28 18:10:14 2011 loick michard
// Last update Mon May  2 23:27:44 2011 loick michard
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
const Color& Texture::getColor(double x, double y) const
{
  int	xi;
  int	yi;

  xi = x * _image->width();
  yi = y * _image->height();
  while (xi <= 0)
    xi += _image->width();
  while (yi <= 0)
    yi += _image->height();
  xi %= _image->width();
  yi %= _image->height();
  if (_image)
    {
      QRgb rgb = _image->pixel(xi, yi);
      QColor color(rgb);
      return (Color(color.red(), color.green(), color.blue()));
    }
  else
    return (Color(255, 255, 255));
}
