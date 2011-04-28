//
// BoundingBox.cpp for raytracer in /home/jochau_g//dev/c/raytracer/raytracer-42
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Thu Apr 28 15:45:41 2011 gael jochaud-du-plessix
// Last update Thu Apr 28 18:03:05 2011 gael jochaud-du-plessix
//

#include "BoundingBox.hpp"

BoundingBox::BoundingBox()
{

}

BoundingBox::~BoundingBox()
{

}

const Point&	BoundingBox::getVertex1() const
{
  return (_vertex1);
}

const Point&	BoundingBox::getVertex2() const
{
  return (_vertex2);
}

Point	BoundingBox::getCenterPosition() const
{
  return ((_vertex1 + _vertex2) / 2);
}
