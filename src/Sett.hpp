//
// Cube.hpp for raytracer in /home/olivie_a//rendu/cpp/raytracer-42/src
// 
// Made by samuel olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  Tue May 10 13:39:45 2011 samuel olivier
// Last update Wed May 25 11:04:47 2011 loick michard
//

#ifndef _SETT_HPP_
#define _SETT_HPP_

#include "Object.hpp"

class Sett : public Object
{
public:
  Sett(void);
  Sett(const Point& position, bool isSolid, const Vector& width,
       const Vector& height, const Vector& depth, Material* material);
};

#endif
