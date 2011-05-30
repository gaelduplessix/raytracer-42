//
// Cube.cpp for Raytracer in /home/olivie_a//rendu/cpp/raytracer-42
// 
// Made by samuel olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  Tue May 10 13:49:47 2011 samuel olivier
// Last update Mon May 30 16:33:16 2011 samuel olivier
//

#include "Sett.hpp"
#include "Parallelogram.hpp"

Sett::Sett(void)
{
}

Sett::Sett(const Point& position, bool isSolid, const Vector& width,
	   const Vector& height, const Vector& depth, Material* material,
	   const Rotation& rotation)
{
  Vector	newWidth = width;
  Vector	newHeight = height;
  Vector	newDepth = depth;

  newWidth.rotate(rotation);
  newHeight.rotate(rotation);
  newDepth.rotate(rotation);
  _rotation = rotation;
  _position = position;
  _isSolid = isSolid;
  vector<ObjectPrimitive*>      primitives;
  primitives.push_back(new Parallelogram(this, position, position + newWidth,
					 position + newHeight, material));
  primitives.push_back(new Parallelogram(this, position, position + newWidth,
  					 position + newDepth, material));
  primitives.push_back(new Parallelogram(this, position, position + newHeight,
  					 position + newDepth, material));

  Point	newVertex = position + newWidth + newHeight + newDepth;
  primitives.push_back(new Parallelogram(this, newVertex, newVertex - newWidth,
  					 newVertex - newHeight, material));
  primitives.push_back(new Parallelogram(this, newVertex, newVertex - newWidth,
  					 newVertex - newDepth, material));
  primitives.push_back(new Parallelogram(this, newVertex, newVertex -newHeight,
  					 newVertex - newDepth, material));
  _primitives = primitives;
}
