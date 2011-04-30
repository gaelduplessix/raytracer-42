//
// Scene.hpp for raytracer in /home/michar_l//Raytracer
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Tue Apr 26 11:43:19 2011 loick michard
// Last update Sat Apr 30 13:50:20 2011 gael jochaud-du-plessix
//

#ifndef _SCENE_HPP_
#define _SCENE_HPP_

#include "Camera.hpp"
#include "Object.hpp"
#include "Light.hpp"

#include <vector>
#include <string>

using namespace std;

class	Scene
{
public:
  Scene(vector<Camera*> cameras,
	vector<Object*> objects,
	vector<Light*> lights);
  Scene(string filename);

  void			loadFromFile(string filename);

  const vector<Camera*>&	getCameras(void) const;
  const vector<Object*>&	getObjects(void) const;
  const vector<Light*>&		getLights(void) const;
  const Camera&		getCamera(int index) const;
  const Object&		getObject(int index) const;
  const Light&		getLight(int index) const;
  int			getNbCameras(void) const;
  int			getNbObjects(void) const;
  int			getNbLights(void) const;

private:
  vector<Camera*>	_cameras;
  vector<Object*>	_objects;
  vector<Light*>	_lights;
};

#endif
