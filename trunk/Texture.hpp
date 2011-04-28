//
// Texture.hpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Wed Apr 27 17:29:38 2011 loick michard
// Last update Thu Apr 28 19:21:37 2011 loick michard
//

#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_

#include "Color.hpp"

class Texture
{
public:
  Texture();
  ~Texture();

  virtual const Color& getColor(double x, double y) const = 0;

private:

};

#endif
