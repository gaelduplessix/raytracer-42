//
// gui_putpixel.cpp for  in /home/laviss_f//raytracer-42/gui
// 
// Made by franck lavisse
// Login   <laviss_f@epitech.net>
// 
// Started on  Fri Apr 29 15:39:43 2011 franck lavisse
// Last update Mon May  9 22:59:28 2011 franck lavisse
//
#include <iostream>
#include <QFileDialog>
#include "gui.hpp"
#include "../Color.hpp"

using namespace std;

void	Gui::saveImage(void)
{
  //  QMessageBox::information(this, "Sauvegarde de scene",
  //  _image->save("raytracer.png", "PNG");
  QString file = QFileDialog::getSaveFileName(this, "Enregistrer une scene", QString(), ".png");
  _image->save(file, "PNG");
}

void	Gui::putPixel(const Color& color, int x, int y)
{
  _image->setPixel(x, y, QColor(color._r, color._g, color._b, color._a).rgb());
}
