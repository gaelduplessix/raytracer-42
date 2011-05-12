//
// RenderingInterface.hpp for raytracer in /home/michar_l//Raytracer
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Tue Apr 26 15:20:09 2011 loick michard
// Last update Thu May 12 16:57:23 2011 loick michard
//

#ifndef _RENDERINGINTERFACE_HPP_
#define _RENDERINGINTERFACE_HPP_

#include <string>
#include "Color.hpp"

using namespace std;

class RenderingInterface
{
public:  
  virtual void pixelHasBeenRendered(int x, int y, Color color);
  virtual void pixelHasStartedRendering(int x, int y);
  virtual void photonMappingHasBegun(void);
  virtual void photonMappingHasFinished(void);
  virtual void kdtreeGenerationHasBegun(void);
  virtual void kdtreeGenerationHasFinished(void);
  virtual void renderingHasBegun(void);
  virtual void renderingHasPaused(void);
  virtual void renderingHasStoped(void);
  virtual void renderingHasFinished(void);
  virtual void renderingHasProgressed(double progress);
  virtual void sendWarningMessage(string message);
  virtual void sendErrorMessage(string message);
  virtual void sendSuccessMessage(string message);
  virtual void sendMessage(string message);
};

#endif
