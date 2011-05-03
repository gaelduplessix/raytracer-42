//
// checkerBoard.hpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Tue May  3 12:20:48 2011 loick michard
// Last update Tue May  3 13:40:27 2011 loick michard
//

#ifndef _CHECKER_BOARD_HPP_
#define _CHECKER_BOARD_HPP_

#include "Texture.hpp"
#include "Color.hpp"

class CheckerBoard : public Texture
{
public:
  CheckerBoard();
  CheckerBoard(double repeatWidth, double repeatHeight);
  CheckerBoard(const Color& color1, const Color& color2,
	       double repeatWidth = 1, double repeatHeight = 1);
  
  Color getPixel(double x, double y) const;

private:
  Color	_color1;
  Color _color2;
};

#endif
