//
// Cube.cpp for Raytracer in /home/olivie_a//rendu/cpp/raytracer-42
// 
// Made by samuel olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  Tue May 10 13:49:47 2011 samuel olivier
// Last update Wed May 25 11:04:55 2011 loick michard
//

#include "Sett.hpp"
#include "Parallelogram.hpp"

Sett::Sett(void)
{
}

Sett::Sett(const Point& position, bool isSolid, const Vector& width,
	   const Vector& height, const Vector& depth, Material* material)
{
  _rotation = Rotation(0, 0, 0);
  _position = position;
  _isSolid = isSolid;
  vector<ObjectPrimitive*>      primitives;
  primitives.push_back(new Parallelogram(this, position, position + width,
					 position + height, material));
  primitives.push_back(new Parallelogram(this, position, position + width,
  					 position + depth, material));
  primitives.push_back(new Parallelogram(this, position, position + height,
  					 position + depth, material));

  Point	newVertex = position + width + height + depth;
  primitives.push_back(new Parallelogram(this, newVertex, newVertex - width,
  					 newVertex - height, material));
  primitives.push_back(new Parallelogram(this, newVertex, newVertex - width,
  					 newVertex - depth, material));
  primitives.push_back(new Parallelogram(this, newVertex, newVertex - height,
  					 newVertex - depth, material));
  _primitives = primitives;
}
