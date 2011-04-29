//
// BoundingBox.cpp for raytracer in /home/jochau_g//dev/c/raytracer/raytracer-42
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Thu Apr 28 15:45:41 2011 gael jochaud-du-plessix
// Last update Fri Apr 29 10:07:00 2011 loick michard
//

#include "BoundingBox.hpp"

BoundingBox::BoundingBox()
{

}

BoundingBox::BoundingBox(const Point& vertex1, const Point& vertex2)
{
  _vertex1 = vertex1;
  _vertex2 = vertex2;
}

BoundingBox::~BoundingBox()
{

}

void		BoundingBox::setVertices(const Point& vertex1,
					 const Point& vertex2)
{
  _vertex1 = vertex1;
  _vertex2 = vertex2;
}

void		BoundingBox::setVertex1(const Point& vertex)
{
  _vertex1 = vertex;
}

void            BoundingBox::setVertex2(const Point& vertex)
{
  _vertex2 = vertex;
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
