//
// Object.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
//
// Made by loick michard
// Login   <michar_l@epitech.net>
//
// Started on  Wed Apr 27 18:53:38 2011 loick michard
// Last update Sat Jun  4 17:46:49 2011 melvin laplanche
//

#include "Object.hpp"

Object::Object(vector<ObjectPrimitive*> primitives, const Rotation& rotation,
	       const Point& position, bool isSolid):
  _primitives(primitives), _rotation(rotation), _position(position),
  _isSolid(isSolid)
{
}

Object::~Object(void)
{
  this->freePrimitives();
}

void	Object::freePrimitives(void)
{
  int	size = _primitives.size();

  for (int i = 0; i < size; i++)
    delete _primitives[i];
  _primitives.clear();
}

Object::Object(void)
{
}

const Vector&		Object::getRefractedVector(const Point& intersectPoint,
						   const Vector& vector)
{
  Point	tmp;

  tmp = intersectPoint;
  return (vector);
}

const vector<ObjectPrimitive*>&	Object::getPrimitives(void) const
{
  return (_primitives);
}

const ObjectPrimitive&	Object::getPrimitiveAtIndex(int index) const
{
  return (*_primitives[index]);
}

int			Object::getNbPrimitives(void) const
{
  return (_primitives.size());
}

const Rotation&		Object::getRotation(void) const
{
  return (_rotation);
}

const Point&		Object::getPosition(void) const
{
  return (_position);
}

bool			Object::isSolid(void)
{
  return (_isSolid);
}

void			Object::addPrimitive(ObjectPrimitive* primitive)
{
  _primitives.push_back(primitive);
}

void			Object::removePrimitiveAtIndex(int index)
{
  delete _primitives[index];
  _primitives.erase(_primitives.begin() + index);
}

void			Object::setPosition(const Point& position)
{
  _position = position;
}

void			Object::setRotation(const Rotation& rotation)
{
  _rotation = rotation;
}

void			Object::setSolid(bool solid)
{
  _isSolid = solid;
}

void			Object::intersectWithRay(const Ray& ray, ObjectPrimitive*& primitive, double& k) const
{
  int			nbPrimitive;
  int			i = -1;

  nbPrimitive = _primitives.size();
  while (++i < nbPrimitive && primitive == NULL)
    _primitives[i]->intersectWithRay(ray, primitive, k);
}
