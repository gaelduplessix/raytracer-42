//
// gui_putpixel.cpp for  in /home/laviss_f//raytracer-42/gui
// 
// Made by franck lavisse
// Login   <laviss_f@epitech.net>
// 
// Started on  Fri Apr 29 15:39:43 2011 franck lavisse
// Last update Fri Apr 29 15:40:04 2011 franck lavisse
//
#include "gui.hpp"

void	Gui::putPixel(unsigned char color[3], int x, int y)
{
  QPolygon	Pixel;
  QGraphicsItem	*Item;
  QColor	Color;

  Color.setRgb((int)color[0], (int)color[1], (int)color[2], 255);
  QPen		PixelPen(Color, 0, Qt::SolidLine);
  QBrush	PixelBrush(Color);
  Item = _Scene->addRect(x,y,1,1,PixelPen,PixelBrush);
}
