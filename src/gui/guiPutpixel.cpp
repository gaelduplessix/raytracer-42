//
// gui_putpixel.cpp for  in /home/laviss_f//raytracer-42/gui
// 
// Made by franck lavisse
// Login   <laviss_f@epitech.net>
// 
// Started on  Fri Apr 29 15:39:43 2011 franck lavisse
// Last update Sat Apr 30 16:46:33 2011 franck lavisse
//

#include "gui.hpp"
#include "../Color.hpp"

void	Gui::putPixel(const Color& color, int x, int y)
{
  QColor	Color(color.getR(), color.getG(), color.getB(), color.getA());
  QPen		PixelPen(Color, 0, Qt::SolidLine);
  
  _Scene->addLine(x,y,x,y,PixelPen);
}
