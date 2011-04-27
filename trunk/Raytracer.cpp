//
// Raytracer.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Wed Apr 27 18:02:30 2011 loick michard
// Last update Wed Apr 27 18:23:03 2011 loick michard
//

#include "Raytracer.hpp"

Raytracer::Raytracer()
{
  _scene = new Scene();
  _config = new RenderingConfiguration();
  _interface = new RenderingInterface();
}

Raytracer::~Raytracer()
{

}
