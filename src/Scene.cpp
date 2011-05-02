//
// Scene.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Wed Apr 27 18:24:15 2011 loick michard
// Last update Mon May  2 14:51:34 2011 samuel olivier
//

#include "Scene.hpp"

Scene::Scene(vector<Camera*> cameras,
	     vector<Object*> objects,
	     vector<Light*> lights):
  _cameras(cameras), _objects(objects), _lights(lights)
{

}

Scene::Scene(string filename)
{
  filename = filename;
}

void			Scene::loadFromFile(string filename)
{
  filename = filename;
}

const vector<Camera*>&	Scene::getCameras(void) const
{
  return (_cameras);
}

const vector<Object*>&	Scene::getObjects(void) const
{
  return (_objects);
}

const vector<Light*>&	Scene::getLights(void) const
{
  return (_lights);
}

#include <iostream>

const Camera&		Scene::getCamera(int index) const
{
  return(*_cameras[index]);
}

const Object&		Scene::getObject(int index) const
{
  return(*_objects[index]);
}

const Light&		Scene::getLight(int index) const
{
  return(*_lights[index]);
}

int			Scene::getNbCameras(void) const
{
  return(_cameras.size());
}

int			Scene::getNbObjects(void) const
{
  return(_objects.size());
}

int			Scene::getNbLights(void) const
{
  return(_lights.size());
}
