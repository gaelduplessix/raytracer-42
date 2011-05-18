//
// Photon.hpp for raytracer in /home/olivie_a//rendu/cpp/raytracer-42
// 
// Made by samuel olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  Tue May 17 13:39:04 2011 samuel olivier
// Last update Wed May 18 20:42:07 2011 samuel olivier
//

#ifndef _PHOTON_
#define _PHOTON_

#include "Point.hpp"
#include "Vector.hpp"
#include "Color.hpp"

class Photon
{
public:
  Photon(Point position, Color color, Vector vector, double dist = 0);
  Photon(void);

  Point		_position;
  Color		_color;
  Vector	_vector;
  double	_dist;
};

#endif
