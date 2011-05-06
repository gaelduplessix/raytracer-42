//
// main.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Wed Apr 27 15:48:47 2011 loick michard
// Last update Sun May  1 15:54:27 2011 franck lavisse
//

#include <vector>
#include "Raytracer.hpp"
#include "CinemaCamera.hpp"
#include "Color.hpp"
#include "Point.hpp"
#include "Vector.hpp"
#include "Rotation.hpp"
#include "ObjectPrimitive.hpp"
#include "Sphere.hpp"
#include "Spot.hpp"
#include "Plan.hpp"
#include "Texture.hpp"
#include "PerlinNoise.hpp"
#include "Cone.hpp"
#include "ParrallelLight.hpp"
#include "Triangle.hpp"

// #include "gui/gui.hpp"
#include <iostream>
#include <SDL/SDL.h>
#include "RenderingInterface.hpp"

using namespace std;

Scene		createScene2()
{
  Material	mat("base");
  mat.setColor(Color(255, 0, 0, 0));
  mat.setSpecularCoeff(0.2);
  mat.setSpecularPow(50);
  Material	reflection = mat;
  reflection.setReflectionCoeff(0);
  Material	refraction = mat;
  refraction.setTransmissionCoeff(0);
  refraction.setRefractionIndex(1.33);
  Material	matFloor("sol");
  matFloor.setReflectionCoeff(0);
  matFloor.setColor(Color(255, 255, 255));
  matFloor.setSpecularCoeff(0.5);
  matFloor.setSpecularPow(50);

  vector<Camera*> cam;
  cam.push_back(new CinemaCamera(Point(0, 0, 0), Rotation(0, 0, 0)));

  vector<ObjectPrimitive*> primitives;
  // primitives.push_back(new Sphere(NULL, Point(12, 0, 0),
  // 				  Rotation(0, 0, 0), reflection, 0.3));
  Material special = refraction;
  PerlinNoise *perlin = new PerlinNoise();//new Texture("heightmap.png");
  //perlin->setMarbleProperties();
  //special.setHeightmap(perlin);
  special.setTransmissionCoeff(0);
  special.setTexture(perlin);
  // primitives.push_back(new Sphere(NULL, Point(20, -4, 0),
  // 				  Rotation(0, 0, 0), special, 3));
  // primitives.push_back(new Sphere(NULL, Point(18, 4, 0),
  // 				  Rotation(0, 0, 0), reflection, 3));
  primitives.push_back(new Triangle(NULL, Point(7.5, -1.5, -1), Rotation(0, 0,0),
				    special, Point(5, 1.5, -1),
				    Point(7.5, 0, 0)));
  refraction.setTransmissionCoeff(0.9);
  refraction.setRefractionIndex(1.5);
  primitives.push_back(new Plan(NULL, Point(0, 0, -5),
  				Rotation(0, 0, 0), matFloor));
  vector<Object*> obj;
  obj.push_back(new Object(primitives, Rotation(0, 0, 0), Point(0, 0, 0),
			   true));

  vector<Light*> light;
  // light.push_back(new ParrallelLight(Point(-1, -3, -3), Color(255, 255, 255), 0.1));
  light.push_back(new Spot(Point(10, -2, 3), Color(255, 255, 255), 1));
  // light.push_back(new Spot(Point(18, 10, 0), Color(255, 0, 0)));

  Scene		res(cam, obj, light);
  return (res);
}

RenderingConfiguration	createConfig2()
{
  RenderingConfiguration res;

  res.setWidth(853);
  res.setHeight(480);
  res.setAntialiasing(1);
  res.setExposure(2);
  res.setDiffuseLighting(true);
  res.setDirectLighting(true);
  res.setDirectLightingCoeff(1);
  res.setSpecularLighting(true);
  res.setReflection(true);
  res.setTransparency(true);
  res.setAmbientOcclusionEnabled(false);
  res.setDiffuseShadingEnabled(false);
  res.setFieldDepthEnabled(false);
  // res.setAdditiveAmbiantLighting(0.1);
  // res.setMinimalAmbiantLighting(0.1);
  res.setRenderingSamplingMethod(RSM_LINEAR_HORIZONTAL);
  //res.setCubeMap(new CubeMap("cubemaps/Tantolunden6"));
  return (res);
}

SDL_Surface	*screen;

class SDLInterface : public RenderingInterface
{
  void pixelHasBeenRendered(int x, int y, Color color)
  {
    Uint8 *p;
    
    if (x < 0 || y < 0 || x >= screen->w || y >= screen->h)
      return ;
    int bpp = screen->format->BytesPerPixel;
    p = (Uint8 *)screen->pixels + y * screen->pitch + x * bpp;
    p[3] = color._a;
    p[2] = color._r;
    p[1] = color._g;
    p[0] = color._b;
    if (x == 0)
      SDL_Flip(screen);
  }

  void renderingHasFinished()
  {
    SDL_Flip(screen);
  }
};

int main(int ac, char **av)
{
  Raytracer rt;
  Scene scene = createScene2();
  RenderingConfiguration conf = createConfig2();

  rt.setScene(scene);
  rt.setRenderingConfiguration(&conf);
  gui(ac, av);
  /*SDL_Init(SDL_INIT_VIDEO);
  screen = SDL_SetVideoMode(853, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
  SDLInterface	interface;
  rt.setRenderingInterface(&interface);
  rt.launchRendering();
  getchar();
  rt.stopRendering();
  SDL_Quit();*/
  return (0);
}
