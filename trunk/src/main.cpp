//
// main.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Wed Apr 27 15:48:47 2011 loick michard
// Last update Mon May  2 14:38:45 2011 samuel olivier
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
// #include "gui/gui.hpp"

Scene		createScene2()
{
  Material	mat("bleu");
  mat.setColor(Color(255, 5, 55, 255));
  mat.setSpecularCoeff(0.6);
  mat.setSpecularPow(50);
  mat.setReflectionCoeff(0);
  mat.setTransmissionCoeff(0.6);
  mat.setRefractionIndex(2);
  Material	mat3 = mat;
  mat3.setColor(Color(255, 255, 255));
  Material	mat2 = mat;
  mat2.setName("rouge");
  mat2.setColor(Color(80, 80, 80));
  mat2.setReflectionCoeff(0.2);
  mat2.setTransmissionCoeff(0);

  vector<Camera*> cam;
  cam.push_back(new CinemaCamera(Point(0, 0, 0), Rotation(0, 0, 0)));

  vector<ObjectPrimitive*> sphere;
  sphere.push_back(new Sphere(NULL, Point(30, 0, 0),
  			      Rotation(0, 0, 10), mat, 4));
  sphere.push_back(new Sphere(NULL, Point(60, -5, -3),
  			      Rotation(0, 0, 0), mat3, 2));
  // sphere.push_back(new Sphere(NULL, Point(30, -4, -2),
  // 			      Rotation(0, 0, 0), mat, 2));
  sphere.push_back(new Plan(NULL, Point(0, 0, -5),
  			    Rotation(0, 0, 0), mat2));
  vector<Object*> obj;
  obj.push_back(new Object(sphere, Rotation(0, 0, 0), Point(0, 0, 0), true));

  vector<Light*> light;
  light.push_back(new Spot(Point(20, -50, 4), Color(255, 0, 0)));
  light.push_back(new Spot(Point(0, 0, 30), Color(0, 255, 255)));
  light.push_back(new Spot(Point(50, 0, 10), Color(0, 255, 255)));

  Scene		res(cam, obj, light);
  return (res);
}

RenderingConfiguration	createConfig2()
{
  RenderingConfiguration res;

  res.setWidth(853);
  res.setHeight(480);
  res.setAntialiasing(1);
  res.setDirectLighting(true);
  res.setReflection(true);
  res.setTransparency(true);
  res.setAmbientOcclusionEnabled(false);
  res.setDiffuseLightingEnabled(false);
  res.setFieldDepthEnabled(false);
  res.setRenderingSamplingMethod(RSM_LINEAR_VERTICAL);
  return (res);
}

#include <iostream>
#include <SDL/SDL.h>
#include "RenderingInterface.hpp"

using namespace std;

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
    if (y == 0)
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
  //gui(ac, av);
  SDL_Init(SDL_INIT_VIDEO);
  screen = SDL_SetVideoMode(853, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
  SDLInterface	interface;
  rt.setRenderingInterface(&interface);
  rt.launchRendering();
  getchar();
  rt.stopRendering();
  SDL_Quit();
  return (0);
  ac = (int)av;
}
