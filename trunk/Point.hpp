//
// Point.hpp for raytracer in /home/jochau_g//data/dev/c/raytracer/raytracer-42
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Tue Apr 26 18:22:56 2011 gael jochaud-du-plessix
// Last update Tue Apr 26 18:25:17 2011 gael jochaud-du-plessix
//

#ifndef _POINT_H_
#define _POINT_H_

#include "Vector.hpp"

class Point: Vector
{
public:
  void	translate(Vector& vector);
};

#endif
