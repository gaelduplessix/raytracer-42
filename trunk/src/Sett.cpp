//
// Cube.cpp for Raytracer in /home/olivie_a//rendu/cpp/raytracer-42
// 
// Made by samuel olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  Tue May 10 13:49:47 2011 samuel olivier
// Last update Tue May 10 14:24:38 2011 samuel olivier
//

#include "Sett.hpp"
#include "Parallelogram.hpp"

Sett::Sett(void)
{
}

Sett::Sett(const Rotation& rotation, const Point& position, bool isSolid,
	   const Vector& width, const Vector& height, const Vector& depth,
	   const Material& material)
{
  _rotation = rotation;
  _position = position;
  _isSolid = isSolid;
  vector<ObjectPrimitive*>      primitives;
  primitives.push_back(new Parallelogram(this, position, position + width,
					 position + height, Rotation(0, 0, 0),
					 material));
  primitives.push_back(new Parallelogram(this, position, position + width,
  					 position + depth, Rotation(0, 0, 0),
  					 material));
  primitives.push_back(new Parallelogram(this, position, position + height,
  					 position + depth, Rotation(0, 0, 0),
  					 material));

  Point	newVertex = position + width + height + depth;
  primitives.push_back(new Parallelogram(this, newVertex, newVertex - width,
  					 newVertex - height, Rotation(0, 0, 0),
  					 material));
  primitives.push_back(new Parallelogram(this, newVertex, newVertex - width,
  					 newVertex - depth, Rotation(0, 0, 0),
  					 material));
  primitives.push_back(new Parallelogram(this, newVertex, newVertex - height,
  					 newVertex - depth, Rotation(0, 0, 0),
  					 material));
  _primitives = primitives;
}
