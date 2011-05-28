//
// RenderingInterface.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Wed Apr 27 18:28:09 2011 loick michard
// Last update Sat May 28 14:58:14 2011 samuel olivier
//

#include "RenderingInterface.hpp"

void RenderingInterface::pixelHasBeenRendered(int x,
					      int y,
					      Color color)
{
  color._r = x + y;
}

void RenderingInterface::pixelHasStartedRendering(int x, int y)
{
  x = y;
}

void RenderingInterface::photonMappingHasBegun()
{
}

void RenderingInterface::photonMappingHasFinished()
{
}

void RenderingInterface::kdtreeGenerationHasBegun()
{
}

void RenderingInterface::kdtreeGenerationHasFinished()
{
}

void RenderingInterface::renderingHasBegun()
{
}

void RenderingInterface::renderingHasPaused()
{
}

void RenderingInterface::renderingHasStoped()
{
}

void RenderingInterface::renderingHasFinished()
{
}

void RenderingInterface::renderingHasProgressed(double progress)
{
  progress = progress;
}

void RenderingInterface::sendWarningMessage(string message)
{
  message = message;
}

void RenderingInterface::sendErrorMessage(string message)
{
  message = message;
}

void RenderingInterface::sendSuccessMessage(string message)
{
  message = message;
}

void RenderingInterface::sendMessage(string message)
{
  message = message;
}

void RenderingInterface::logServerConsoleMessage(string message)
{
  message = message;
}
