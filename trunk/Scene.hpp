//
// Scene.hpp for raytracer in /home/michar_l//Raytracer
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Tue Apr 26 11:43:19 2011 loick michard
// Last update Tue Apr 26 18:47:34 2011 gael jochaud-du-plessix
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
  Scene();
  Scene(vector<Camera> Cameras,
	vector<Object> Objects,
	vector<Light> Lights) : _cameras(Cameras),
				_objects(Objects),
				_lights(Lights);
  Scene(string filename);
  ~Scene();

  void			loadFromFile(string filename);

  vector<Camera>	getCameras() const;
  vector<Object>	getObjects() const;
  vector<Light>		getLights() const;
  Camera&		getCamera(int index) const;
  Object&		getObject(int index) const;
  Light&		getLight(int index) const;
  int			getNbCameras() const;
  int			getNbObjects() const;
  int			getNbLights() const;

private:
  vector<Camera>	_cameras;
  vector<Object>	_objects;
  vector<Light>		_lights;
};

#endif
