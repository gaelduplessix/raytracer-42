//
// gui_putpixel.cpp for  in /home/laviss_f//raytracer-42/gui
// 
// Made by franck lavisse
// Login   <laviss_f@epitech.net>
// 
// Started on  Fri Apr 29 15:39:43 2011 franck lavisse
// Last update Mon May  9 23:44:06 2011 franck lavisse
//
#include <iostream>
#include <string>
#include <vector>
#include <QFileDialog>
#include "gui.hpp"
#include "../Color.hpp"

using namespace std;



void	Gui::saveImage(void)
{
  vector<string> validFormat(4);
  validFormat[0] = "png";
  validFormat[1] = "gif";
  validFormat[2] = "bmp";
  validFormat[3] = "peg";
  string format;
  //  _image->save("raytracer.png", "PNG");
  QString file = QFileDialog::getSaveFileName(this, "Enregistrer une scene", QString(), "Images *.png *.gif *.jpeg *.bmp");
  format = file.toStdString();
  format = format.substr(format.size() - 3, format.size());
  if (format.compare(validFormat[0]) != 0 &&
      format.compare(validFormat[1]) != 0 &&
      format.compare(validFormat[2]) != 0 &&
      format.compare(validFormat[3]) != 0)
    {
      format = "png";
      file += ".png";
    }
  if (format.compare("peg") == 0)
    format = "jpeg";
  cout << format <<  endl << file.toStdString() << endl;
  _image->save(file, format.c_str());
}

void	Gui::putPixel(const Color& color, int x, int y)
{
  _image->setPixel(x, y, QColor(color._r, color._g, color._b, color._a).rgb());
}
