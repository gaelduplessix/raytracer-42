//
// Raytracer.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Wed Apr 27 18:02:30 2011 loick michard
// Last update Fri Apr 29 12:32:31 2011 gael jochaud-du-plessix
//

#include "Raytracer.hpp"

Raytracer::Raytracer()
{
  _thread = new RaytracerThread(this);
}

Raytracer::~Raytracer()
{
  delete _thread;
}

void
Raytracer::setScene(Scene& scene)
{
  _scene = &scene;
}

void
Raytracer::setRenderingConfiguration(RenderingConfiguration& config)
{
  _config = &config;
}

void
Raytracer::setRenderingInterface(RenderingInterface& interface)
{
  _interface = &interface;
}

const Scene*
Raytracer::getScene(void) const
{
  return (_scene);
}

const RenderingConfiguration*
Raytracer::getRenderingConfiguration(void) const
{
  return (_config);
}

const RenderingInterface*
Raytracer::getRenderingInterface(void) const
{
  return (_interface);
}

void
Raytracer::launchRendering(void)
{
  _thread->start();
}

void
Raytracer::stopRendering(void)
{
  _thread->stop();
  _thread->wait();
}
