//
// Texture.hpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Wed Apr 27 17:29:38 2011 loick michard
// Last update Tue May  3 11:12:42 2011 gael jochaud-du-plessix
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
  Texture(const string& path);
  ~Texture();

  virtual Color getColor(double x, double y) const;

private:
  QImage	*_image;
};

#endif
