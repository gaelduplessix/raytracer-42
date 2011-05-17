//
// Photon.cpp for raytracer in /home/olivie_a//rendu/cpp/raytracer-42/src
// 
// Made by samuel olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  Tue May 17 13:47:28 2011 samuel olivier
// Last update Tue May 17 13:53:42 2011 samuel olivier
//

#include "Photon.hpp"

Photon::Photon(Point position, Color color, Vector vector) :
  _position(position), _color(color), _vector(vector)
{

}

Photon::Photon(void) :
  _position(Point(0, 0, 0)), _color(Color(0, 0, 0)), _vector(Vector(0, 0, 0))
{

}
