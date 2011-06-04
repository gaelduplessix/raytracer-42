//
// main.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
//
// Made by loick michard
// Login   <michar_l@epitech.net>
//
// Started on  Wed Apr 27 15:48:47 2011 loick michard
// Last update Thu Jun  2 13:52:15 2011 gael jochaud-du-plessix
//

#include <vector>
#include <iostream>
#include <cmath>

#include "Raytracer.hpp"
#include "CinemaCamera.hpp"
#include "Color.hpp"
#include "Point.hpp"
#include "Vector.hpp"
#include "Rotation.hpp"
#include "ObjectPrimitive.hpp"
#include "EquationPrimitive.hpp"
#include "Sphere.hpp"
#include "Parallelogram.hpp"
#include "Spot.hpp"
#include "ParallelogramLight.hpp"
#include "SphericalLight.hpp"
#include "ParallelLight.hpp"
#include "Plane.hpp"
#include "Texture.hpp"
#include "PerlinNoise.hpp"
#include "CheckerBoard.hpp"
#include "Cone.hpp"
#include "Cylinder.hpp"
#include "Torus.hpp"
#include "CubeTroue.hpp"
#include "Sett.hpp"
#include "RenderingInterface.hpp"

#include "gui/gui.hpp"

using namespace std;

/*
#include <SDL/SDL.h>
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
*/
#include <QTranslator>

int main(int ac, char **av)
{
  gui(ac, av);
  return (0);
}
