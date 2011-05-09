//
// guiRendering.cpp for  in /home/laviss_f//raytracer-42/src
// 
// Made by franck lavisse
// Login   <laviss_f@epitech.net>
// 
// Started on  Sat Apr 30 20:03:34 2011 franck lavisse
// Last update Mon May  9 16:27:07 2011 franck lavisse
//
#include <QTimer>
#include <iostream>
#include "gui.hpp"

using namespace std;

void	Gui::renderingHasPaused(void)
{
  cout << "Rendering has paused" << endl;
}

void	Gui::renderingHasFinished(void)
{
  _timer->disconnect();
  cout << "Rendering has finished" << endl;
}

void	Gui::renderingHasBegun(void)
{
  QObject::connect(_timer, SIGNAL(timeout()), this, SLOT(repaint()));
  cout << "Rendering has begun" << endl;
}

void	Gui::renderingHasStoped(void)
{
  cout << "Rendering has stoped" << endl;
}

void	Gui::pixelHasBeenRendered(int x, int y, Color color)
{
  color.setA(255);
  putPixel(color, x, y);
}
