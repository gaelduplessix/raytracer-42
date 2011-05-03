//
// checkerBoard.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42/src
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Tue May  3 12:49:29 2011 loick michard
// Last update Tue May  3 13:45:23 2011 loick michard
//

#include "CheckerBoard.hpp"

CheckerBoard::CheckerBoard():
  Texture(1, 1), _color1(0, 0, 0), _color2(255, 255, 255)
{

}

CheckerBoard::CheckerBoard(double repeatWidth, double repeatHeight):
  Texture(repeatWidth, repeatHeight),
  _color1(0, 0, 0), _color2(255, 255, 255)
{
  
}

CheckerBoard::CheckerBoard(const Color& color1, const Color& color2,
			   double repeatWidth, double repeatHeight):
  Texture(repeatWidth, repeatHeight),
  _color1(color1), _color2(color2)
{
  
}

Color CheckerBoard::getPixel(double x, double y) const
{
  if ((x < 0.5) ^ (y < 0.5))
    return (_color1);
  else
    return (_color2);
}
