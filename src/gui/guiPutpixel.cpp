//
// gui_putpixel.cpp for  in /home/laviss_f//raytracer-42/gui
// 
// Made by franck lavisse
// Login   <laviss_f@epitech.net>
// 
// Started on  Fri Apr 29 15:39:43 2011 franck lavisse
// Last update Fri Apr 29 21:21:03 2011 samuel olivier
//

#include "gui.hpp"
#include "../Color.hpp"

void	Gui::putPixel(const Color& color, int x, int y)
{
  QPolygon	Pixel;
  QGraphicsItem	*Item;
  QColor	Color;
  QPen		PixelPen(Color, 0, Qt::SolidLine);
  QBrush	PixelBrush(Color);

  Color.setRgb(color.getR(), color.getG(), color.getB(), color.getA());
  Item = _Scene->addRect(x, y, 1, 1, PixelPen, PixelBrush);
}
