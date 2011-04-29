//
// gui_putpixel.cpp for  in /home/laviss_f//raytracer-42/gui
// 
// Made by franck lavisse
// Login   <laviss_f@epitech.net>
// 
// Started on  Fri Apr 29 15:39:43 2011 franck lavisse
// Last update Fri Apr 29 21:56:53 2011 gael jochaud-du-plessix
//

#include "gui.hpp"
#include "../Color.hpp"

void	Gui::putPixel(const Color& color, int x, int y)
{
  QPolygon	Pixel;
  QGraphicsItem	*Item;
  QColor	Color(color.getR(), color.getG(), color.getB(), color.getA());
  QPen		PixelPen(Color, 0, Qt::SolidLine);
  QBrush	PixelBrush(Color);

  _Scene->addRect(x, y, 1, 1, PixelPen, PixelBrush);
}
