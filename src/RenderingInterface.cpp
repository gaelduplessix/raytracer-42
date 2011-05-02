//
// RenderingInterface.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Wed Apr 27 18:28:09 2011 loick michard
// Last update Mon May  2 14:48:37 2011 samuel olivier
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
