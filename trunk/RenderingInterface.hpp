//
// RenderingInterface.hpp for raytracer in /home/michar_l//Raytracer
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Tue Apr 26 15:20:09 2011 loick michard
// Last update Wed Apr 27 17:54:29 2011 loick michard
//

#ifndef _RENDERINGINTERFACE_HPP_
#define _RENDERINGINTERFACE_HPP_

class RenderingInterface
{
public:
  RenderingInterface();
  ~RenderingInterface();

  virtual void pixelHasBeenRendered(int x, int y, Color color);
  virtual void pixelHasStartedRendering(int x, int y);
  virtual void photonMappingHasBegun();
  virtual void photonMappingHasFinished();
  virtual void kdtreeGenerationHasBegun();
  virtual void kdtreeGenerationHasFinished();
  virtual void renderingHasBegun();
  virtual void renderingHasPaused();
  virtual void renderingHasStoped();
  virtual void renderingHasFinished();
  virtual void renderingHasProgressed(double progress);
};

#endif
