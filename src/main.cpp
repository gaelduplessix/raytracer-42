//
// main.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
//
// Made by loick michard
// Login   <michar_l@epitech.net>
//
// Started on  Wed Apr 27 15:48:47 2011 loick michard
// Last update Mon Jun  6 18:17:08 2011 gael jochaud-du-plessix
//

#include <vector>
#include <cmath>

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

int main(int ac, char **av)
{
  gui(ac, av);
  return (0);
}
