//
// checkerBoard.hpp for raytracer in /home/michar_l//Raytracer/raytracer-42
//
// Made by loick michard
// Login   <michar_l@epitech.net>
//
// Started on  Tue May  3 12:20:48 2011 loick michard
// Last update Sat Jun  4 18:29:01 2011 melvin laplanche
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
  void	setColor1(const Color& color1);
  void	setColor2(const Color& color2);

private:
  Color	_color1;
  Color _color2;
};

#endif
