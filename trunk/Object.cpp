//
// Object.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Wed Apr 27 18:53:38 2011 loick michard
// Last update Thu Apr 28 16:08:47 2011 samuel olivier
//

#include "Object.hpp"

Object::Object()
{

}

// Object::Object(vector<ObjectPrimitive> primitives, const Rotation& rotation,
// 	       const Point& position, bool isSolid)
// {
//   _primitives = primitives;
//   _rotation = rotation;
//   _position = position;
//   _isSolid = isSolid;
// }

Object::~Object()
{
  
}

Vector		Object::getRefractedVector(const Point& intersectPoint,
					   const Vector& vector)
{

}

const ObjectPrimitive&	Object::getPrimitiveAtIndex(int index) const
{
  return (_primitives[index]);
}

int			Object::getNbPrimitives() const
{
  return (_primitives.size());
}

const Rotation&		Object::getRotation() const
{
  return (_rotation);
}

const Point&		Object::getPosition() const
{
  return (_position);
}

bool			Object::isSolid()
{
  return (_isSolid);
}

void			Object::addPrimitive(ObjectPrimitive* primitive)
{
  // _primitives.push_back(primitive);
}

void			Object::removePrimitiveAtIndex(int index)
{
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
