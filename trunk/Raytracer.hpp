//
// Raytracer.hpp for raytracer in /home/michar_l//Raytracer
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Tue Apr 26 12:24:26 2011 loick michard
// Last update Wed Apr 27 18:22:58 2011 loick michard
//

#ifndef _RAYTRACER_HPP_
#define _RAYTRACER_HPP_

#include "Scene.hpp"
#include "RenderingConfiguration.hpp"
#include "RenderingInterface.hpp"

class	Raytracer
{
public:
  Raytracer();
  Raytracer(Scene& scene,
	    RenderingConfiguration& config,
	    RenderingInterface& interface);
  ~Raytracer();

  void launchRendering();
  void stopRendering();
  void pauseRendering();

  void setScene(Scene& scene);
  void setRenderingConfiguration(RenderingConfiguration& config);
  void setRenderingInterface(RenderingInterface& interface);
  Scene&			getScene() const;
  RenderingConfiguration&	getRenderingConfiguration() const;
  RenderingInterface&		getRenderingInterface() const;

private:
  Scene*			_scene;
  RenderingConfiguration*	_config;
  RenderingInterface*		_interface;
};

#endif
