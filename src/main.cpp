//
// main.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Wed Apr 27 15:48:47 2011 loick michard
// Last update Sun May  8 21:22:37 2011 gael jochaud-du-plessix
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
#include "Parallelogram.hpp"
#include "Spot.hpp"
#include "ParallelLight.hpp"
#include "Plan.hpp"
#include "Texture.hpp"
#include "PerlinNoise.hpp"
#include "Cone.hpp"
#include "Torus.hpp"
#include "CubeTroue.hpp"
//#include "gui/gui.hpp"
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
  reflection.setReflectionCoeff(1);
  reflection.setTransmissionCoeff(0);
  reflection.setRefractionIndex(1.33);
  Material	refraction = mat;
  refraction.setTransmissionCoeff(0);
  refraction.setRefractionIndex(1.33);
  Material	matFloor("sol");
  matFloor.setReflectionCoeff(0);
  matFloor.setColor(Color(255, 255, 255));
  matFloor.setSpecularCoeff(0.5);
  matFloor.setSpecularPow(50);
  Material	object = matFloor;
  object.setColor(Color(255, 0, 0));
  object.setTransmissionCoeff(0.6);
  object.setRefractionIndex(1);

  vector<Camera*> cam;
  cam.push_back(new CinemaCamera(Point(0, -4, 0), Rotation(0, 0, 0.3)));

  vector<ObjectPrimitive*> primitives;
  // primitives.push_back(new CubeTroue(NULL, Point(23, 5, 0),
  // 				     Rotation(0.3, 0.5, 0), reflection));
  // primitives.push_back(new Torus(NULL, Point(23, 0, 0),
  // 				 Rotation(0.3, 0.5, 0), matFloor, 3, 0.8));

  // Face de devant
  primitives.push_back(new Parallelogram(NULL, Point(20, 1, 1),
  					 Point(20, 1, 4),
  					 Point(20, 4, 1),
  					 Rotation(0, 0, 0), object));

  // Face de derriere
  primitives.push_back(new Parallelogram(NULL, Point(23, 1, 1),
  					 Point(23, 1, 4),
  					 Point(23, 4, 1),
  					 Rotation(0, 0, 0), object));

  // Face de dessous
  primitives.push_back(new Parallelogram(NULL, Point(20, 1, 1),
  					 Point(23, 1, 1),
  					 Point(20, 4, 1),
  					 Rotation(0, 0, 0), object));

  // Face de dessus
  primitives.push_back(new Parallelogram(NULL, Point(20, 1, 4),
  					 Point(23, 1, 4),
  					 Point(20, 4, 4),
  					 Rotation(0, 0, 0), object));

  // Face de gauche
  primitives.push_back(new Parallelogram(NULL, Point(20, 1, 1),
  					 Point(20, 1, 4),
  					 Point(23, 1, 1),
  					 Rotation(0, 0, 0), object));

  // Face de droite
  primitives.push_back(new Parallelogram(NULL, Point(20, 4, 1),
  					 Point(20, 4, 4),
  					 Point(23, 4, 1),
  					 Rotation(0, 0, 0), object));
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
  //primitives.push_back(new Triangle(NULL, Point(7.5, -1.5, -1), Rotation(0, 0,0),
  //				    special, Point(5, 1.5, -1),
  //				    Point(7.5, 0, 0)));
  refraction.setTransmissionCoeff(0.9);
  refraction.setRefractionIndex(1.5);
  primitives.push_back(new Plan(NULL, Point(0, 0, -5),
  				Rotation(0, 0, 0), matFloor));
  vector<Object*> obj;
  obj.push_back(new Object(primitives, Rotation(0, 0, 0), Point(0, 0, 0),
			   true));

  vector<Light*> light;
  // light.push_back(new ParallelLight(Point(0, -3, -3), Color(255, 255, 255)));
  light.push_back(new Spot(Point(21.5, 2.5, 2.5), Color(255, 255, 255)));
  light.push_back(new Spot(Point(10, 0, 2), Color(255, 255, 255)));
  light.push_back(new Spot(Point(10, 5, 2), Color(255, 255, 255)));
  light.push_back(new Spot(Point(20, 10, 0), Color(255, 255, 255)));

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
  //gui(ac, av);
  SDL_Init(SDL_INIT_VIDEO);
  screen = SDL_SetVideoMode(853, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
  SDLInterface	interface;
  rt.setRenderingInterface(&interface);
  rt.launchRendering();
  SDL_Event event;
  bool quit = false;
  while (!quit)
    {
      if (SDL_WaitEvent(&event))
	{
	  if (event.type == SDL_QUIT
              || (event.type == SDL_KEYDOWN
                  && (event.key.keysym.sym == SDLK_ESCAPE
		      || event.key.keysym.sym == SDLK_RETURN)))
	    quit = true;
	}
    }
  rt.stopRendering();
  SDL_Quit();
  return (0);
}
