//
// main.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Wed Apr 27 15:48:47 2011 loick michard
// Last update Fri Apr 29 12:32:17 2011 gael jochaud-du-plessix
//

#include <stdio.h>
#include <iostream>

#include "Raytracer.hpp"

int main()
{
  Raytracer rt;

  std::cout << "Launching" << endl;
  rt.launchRendering();
  std::cout << "Launched" << endl;
  getchar();
  rt.stopRendering();
  return (0);
}
