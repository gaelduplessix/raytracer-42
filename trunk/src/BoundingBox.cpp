//
// BoundingBox.cpp for raytracer in /home/jochau_g//dev/c/raytracer/raytracer-42
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Thu Apr 28 15:45:41 2011 gael jochaud-du-plessix
// Last update Sun May 22 11:39:36 2011 loick michard
//

#include "BoundingBox.hpp"

BoundingBox::BoundingBox()
{

}

BoundingBox::BoundingBox(const Point& vertex1, const Point& vertex2):
  _vertex1(vertex1), _vertex2(vertex2)
{
  this->setParallelogram();
}

BoundingBox::~BoundingBox()
{

}

void		BoundingBox::setParallelogram()
{
  Point		point1;
  Point		point2;

  _face1.setPosition(_vertex1);
  point1 = _vertex1;
  point1._z = _vertex2._z;
  _face1.setVertex1(point1);
  point2 = _vertex1;
  point2._y = _vertex2._y;
  _face1.setVertex2(point2);

  _face2.setPosition(_vertex1);
  point1 = _vertex1;
  point1._x = _vertex2._x;
  _face2.setVertex1(point1);
  point2 = _vertex1;
  point2._z = _vertex2._z;
  _face2.setVertex2(point2);

  _face3.setPosition(_vertex1);
  point1 = _vertex1;
  point1._y = _vertex2._y;
  _face3.setVertex1(point1);
  point2 = _vertex1;
  point2._x = _vertex2._x;
  _face3.setVertex2(point2);


  _face4.setPosition(_vertex2);
  point1 = _vertex2;
  point1._z = _vertex1._z;
  _face4.setVertex1(point1);
  point2 = _vertex2;
  point2._y = _vertex1._y;
  _face4.setVertex2(point2);

  _face5.setPosition(_vertex2);
  point1 = _vertex2;
  point1._x = _vertex1._x;
  _face5.setVertex1(point1);
  point2 = _vertex2;
  point2._z = _vertex1._z;
  _face5.setVertex2(point2);

  _face6.setPosition(_vertex2);
  point1 = _vertex2;
  point1._y = _vertex1._y;
  _face6.setVertex1(point1);
  point2 = _vertex2;
  point2._x = _vertex1._x;
  _face6.setVertex2(point2);
}

double		BoundingBox::intersectWithRay(const Ray& ray)
{
  double	res = -1;
  ObjectPrimitive* primitive = NULL;

  _face1.intersectWithRay(ray, primitive, res);
  _face2.intersectWithRay(ray, primitive, res);
  _face3.intersectWithRay(ray, primitive, res);
  _face4.intersectWithRay(ray, primitive, res);
  _face5.intersectWithRay(ray, primitive, res);
  _face6.intersectWithRay(ray, primitive, res);
  return (res);
}

Point		BoundingBox::getMaxPoint() const
{
  return (Point((_vertex1._x > _vertex2._x) ? _vertex1._x 
		: _vertex2._x,
		(_vertex1._y > _vertex2._y) ? _vertex1._y
		: _vertex2._y,
		(_vertex1._z > _vertex2._z) ? _vertex1._z
		: _vertex2._z));
}

Point           BoundingBox::getMinPoint() const
{
  return (Point((_vertex1._x < _vertex2._x) ? _vertex1._x
		: _vertex2._x,
                (_vertex1._y < _vertex2._y) ? _vertex1._y
                : _vertex2._y,
		(_vertex1._z < _vertex2._z) ? _vertex1._z
                : _vertex2._z));
}

void		BoundingBox::setVertices(const Point& vertex1,
					 const Point& vertex2)
{
  _vertex1 = vertex1;
  _vertex2 = vertex2;
  this->setParallelogram();
}

void		BoundingBox::setVertex1(const Point& vertex)
{
  _vertex1 = vertex;
  this->setParallelogram();
}

void            BoundingBox::setVertex2(const Point& vertex)
{
  _vertex2 = vertex;
  this->setParallelogram();
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
