//
// ObjectPrimitive.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Wed Apr 27 18:55:34 2011 loick michard
// Last update Thu Apr 28 16:24:25 2011 loick michard
//

#include "ObjectPrimitive.hpp"

ObjectPrimitive::ObjectPrimitive()
{
  _object = NULL;
}

ObjectPrimitive::ObjectPrimitive(Object *object)
{
  _object = object;
}

ObjectPrimitive::~ObjectPrimitive()
{

}

const Object&         ObjectPrimitive::getObject() const
{
  return (*_object);
}

const Point&          ObjectPrimitive::getPosition() const
{
  return (_absolutePosition);
}

const Rotation&       ObjectPrimitive::getRotation() const
{
  return (_rotation);
}

void          ObjectPrimitive::setObject(Object *object)
{
  _object = object;
}

void          ObjectPrimitive::setPosition(const Point& position)
{
  _absolutePosition = position;
}

void          ObjectPrimitive::setRotation(const Rotation& rotation)
{
  _rotation = rotation;
}

void          ObjectPrimitive::setMaterial(const Material& material)
{
  _material = material;
}

