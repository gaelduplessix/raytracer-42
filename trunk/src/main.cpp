//
// main.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Wed Apr 27 15:48:47 2011 loick michard
// Last update Thu Apr 28 23:35:00 2011 samuel olivier
//

#include <iostream>

#include "Raytracer.hpp"

using namespace std;

int main()
{
  Raytracer rt;

#ifdef CACA
  cout << "salut";
#else
  cout << "bla";
#endif
  cout << endl;
  return (0);
}
