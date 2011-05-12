//
// guiInterface.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42-gui
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Thu May 12 00:09:02 2011 loick michard
// Last update Thu May 12 00:42:13 2011 loick michard
//

#include "gui.hpp"

void    RaytracerGUI::pauseRendering(void)
{
  _raytracer->pauseRendering();
}

void    RaytracerGUI::renderingHasFinished(void)
{
  _isRendering = false;
}

void    RaytracerGUI::renderingHasBegun(void)
{
  
}

void    RaytracerGUI::stopRendering(void)
{
  _raytracer->stopRendering();
    _isRendering = false;
}

void  RaytracerGUI::pixelHasBeenRendered(int x, int y, Color color)
{
  if (_image)
    _image->setPixel(x, y, QColor(color._r, color._g,
                                  color._b, color._a).rgb());
}
