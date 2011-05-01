//
// guiRendering.cpp for  in /home/laviss_f//raytracer-42/src
// 
// Made by franck lavisse
// Login   <laviss_f@epitech.net>
// 
// Started on  Sat Apr 30 20:03:34 2011 franck lavisse
// Last update Sun May  1 14:10:39 2011 loick michard
//

#include "gui.hpp"

#include <iostream>
using namespace std;
void	Gui::pixelHasBeenRendered(int x, int y, Color color)
{
  color.setA(255);
  // cout<< x << ":" << y << ":" << color.getR() << "."
  //     << color.getG() << "." << color.getB() << "." << color.getA() << endl;
  putPixel(color, x, y);
  if (y == 0)
    show();
}
