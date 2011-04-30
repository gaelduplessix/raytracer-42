//
// guiRendering.cpp for  in /home/laviss_f//raytracer-42/src
// 
// Made by franck lavisse
// Login   <laviss_f@epitech.net>
// 
// Started on  Sat Apr 30 20:03:34 2011 franck lavisse
// Last update Sat Apr 30 20:13:37 2011 franck lavisse
//
#include "gui.hpp"

void	Gui::pixelHasBeenRendered(int x, int y, Color color)
{
  putPixel(color, x, y);
}

void	Gui::pixelHasStartedRendering(int x, int y) {}
void	Gui::photonMappingHasBegun() {}
void	Gui::photonMappingHasFinished() {}
void	Gui::kdtreeGenerationHasBegun() {}
void	Gui::kdtreeGenerationHasFinished() {}
void	Gui::renderingHasBegun() {}
void	Gui::renderingHasPaused() {}
void	Gui::renderingHasStoped() {}
void	Gui::renderingHasFinished() {}
void	Gui::renderingHasProgressed(double progress) {}
