//
// gui_putpixel.cpp for  in /home/laviss_f//raytracer-42/gui
// 
// Made by franck lavisse
// Login   <laviss_f@epitech.net>
// 
// Started on  Fri Apr 29 15:39:43 2011 franck lavisse
// Last update Tue May 10 14:07:03 2011 franck lavisse
//
#include <iostream>
#include <string>
#include <vector>
#include <QDialog>
#include <QFileDialog>
#include <stdlib.h>
#include "gui.hpp"
#include "../Color.hpp"

using namespace std;

void	Gui::saveImage(void)
{
  int	found;
  vector<string> validFormat(4);
  validFormat[0] = "png";
  validFormat[1] = "gif";
  validFormat[2] = "bmp";
  validFormat[3] = "jpeg";
  string format;
  QString file = QFileDialog::getSaveFileName(this, "Enregistrer une scene", QString(), "*.png;;*.gif;;*.jpeg;;*.bmp", 0, QFileDialog::DontUseNativeDialog);

  if (file != NULL)
    {
      format = file.toStdString();
      found = format.find(".");
      format = format.substr(found + 1);
      if (format.compare(validFormat[0]) != 0 &&
	  format.compare(validFormat[1]) != 0 &&
	  format.compare(validFormat[2]) != 0 &&
	  format.compare(validFormat[3]) != 0)
	{
	  format = "png";
	  file += ".png";
	}
    }
  _image->save(file);
}

void	Gui::putPixel(const Color& color, int x, int y)
{
  _image->setPixel(x, y, QColor(color._r, color._g, color._b, color._a).rgb());
}
