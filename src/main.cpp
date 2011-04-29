//
// main.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Wed Apr 27 15:48:47 2011 loick michard
// Last update Fri Apr 29 19:41:16 2011 gael jochaud-du-plessix
//

#include <vector>
#include "gui.hpp"
#include "Raytracer.hpp"
#include "CinemaCamera.hpp"
#include "Color.hpp"
#include "Point.hpp"
#include "Vector.hpp"
#include "Rotation.hpp"
#include "ObjectPrimitive.hpp"
#include "Sphere.hpp"
#include "Spot.hpp"

Scene		createScene()
{
  Material	mat("bleu");
  mat.setColor(Color(255, 0, 0, 0));
  mat.setSpecularCoeff(0.8);
  mat.setSpecularPow(50);
  mat.setReflectionCoeff(0.5);
  mat.setTransmissionCoeff(0.5);
  mat.setRefractionIndex(0.5);

  vector<Camera*> cam;
  cam.push_back(new CinemaCamera(Point(0, 0, 0), Rotation(0, 0, 0)));

  vector<ObjectPrimitive*> sphere;
  sphere.push_back(new Sphere(NULL, Point(-20, 0, 0),
			      Rotation(0, 0, 0), mat, 5));
  vector<Object*> obj;
  obj.push_back(new Object(sphere, Rotation(0, 0, 0), Point(0, 0, 0), true));

  vector<Light*> light;
  light.push_back(new Spot(Point(0, 5, 5), Color(255, 255, 255)));

  Scene		res(cam, obj, light);
  return (res);
}

RenderingConfiguration	createConfig()
{
  RenderingConfiguration res;

  res.setWidth(800);
  res.setHeight(800);
  res.setAntialiasing(1);
  res.setDirectLighting(false);
  res.setReflection(false);
  res.setTransparency(false);
  res.setAmbientOcclusionEnabled(false);
  res.setDiffuseLightingEnabled(false);
  res.setFieldDepthEnabled(false);
  res.setRenderingSamplingMethod(RSM_LINEAR_HORIZONTAL);
  return (res);
}

RenderingInterface	createInterface()
{
  RenderingInterface	res;

  return (res);
}

int main(int ac, char **av)
{
  Raytracer rt;
  Scene scene = createScene();
  RenderingInterface interface = createInterface();
  RenderingConfiguration conf = createConfig();

  rt.setScene(scene);
  rt.setRenderingConfiguration(conf);
  rt.setRenderingInterface(interface);
  gui(ac, av);
  return (0);
}
