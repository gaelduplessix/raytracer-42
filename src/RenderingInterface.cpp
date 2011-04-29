//
// RenderingInterface.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Wed Apr 27 18:28:09 2011 loick michard
// Last update Wed Apr 27 19:10:47 2011 loick michard
//

#include "RenderingInterface.hpp"

RenderingInterface::RenderingInterface()
{
}

RenderingInterface::~RenderingInterface()
{
}

void RenderingInterface::pixelHasBeenRendered(int x,
					      int y,
					      const Color& color)
{
}

void RenderingInterface::pixelHasStartedRendering(int x, int y)
{
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
}
