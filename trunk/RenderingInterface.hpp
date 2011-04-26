//
// RenderingInterface.hpp for raytracer in /home/michar_l//Raytracer
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Tue Apr 26 15:20:09 2011 loick michard
// Last update Tue Apr 26 16:16:15 2011 loick michard
//

#ifndef _RENDERINGINTERFACE_HPP_
#define _RENDERINGINTERFACE_HPP_

class RenderingInterface
{
public:
  virtual RenderingInterface();
  ~RenderingInterface();

  virtual pixelHasBeenRendered(int x, int y, Color color);
  virtual pixelHasStartedRendering(int x, int y);
  virtual photonMappingHasBegun();
  virtual photonMappingHasFinished();
  virtual kdtreeGenerationHasBegun();
  virtual kdtreeGenerationHasFinished();
  virtual renderingHasBegun();
  virtual renderingHasPaused();
  virtual renderingHasStoped();
  virtual renderingHasFinished();
  virtual renderingHasProgressed(double progress);
};

#endif
