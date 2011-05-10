//
// guiRendering.cpp for  in /home/laviss_f//raytracer-42/src
// 
// Made by franck lavisse
// Login   <laviss_f@epitech.net>
// 
// Started on  Sat Apr 30 20:03:34 2011 franck lavisse
// Last update Tue May 10 14:07:31 2011 franck lavisse
//
#include <QTimer>
#include <iostream>
#include "gui.hpp"

using namespace std;

void	Gui::renderingHasPaused(void)
{
  _raytracer.pauseRendering();
  cout << "Rendering has paused" << endl;
}

void	Gui::renderingHasFinished(void)
{
  isRendering = 0;
  _timer->disconnect();
  cout << "Rendering has finished" << endl;
}

void	Gui::renderingHasBegun(void)
{  
  if (isRendering)
    {
      _raytracer.launchRendering();
      cout << "Rendering has begun" << endl;
    }
  else if (!isStarted)
    {
      isStarted = 1;
      _raytracer.launchRendering();
      cout << "Rendering has begun" << endl;
    }
}

void	Gui::renderingHasStoped(void)
{
  isRendering = 0;
  _raytracer.stopRendering();
  cout << "Rendering has stoped" << endl;
}

void	Gui::pixelHasBeenRendered(int x, int y, Color color)
{
  color.setA(255);
  putPixel(color, x, y);
}
