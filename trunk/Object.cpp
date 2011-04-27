//
// Object.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Wed Apr 27 18:53:38 2011 loick michard
// Last update Wed Apr 27 23:48:57 2011 samuel olivier
//

#include "Object.hpp"

Object::Object()
{

}

Object::~Object()
{
  
}

Vector Object::getRefractedVector(Point& intersectPoint, Vector& vector)
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

// void			Object::addPrimitive(ObjectPrimitive* primitive)
// {
//   _primitives.push_back(primitive);
// }

void			Object::removePrimitiveAtIndex(int index)
{
  _primitives.erase(_primitives.begin() + index);
}
