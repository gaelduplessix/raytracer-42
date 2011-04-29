//
// ObjectPrimitive.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Wed Apr 27 18:55:34 2011 loick michard
// Last update Fri Apr 29 18:39:51 2011 samuel olivier
//

#include "ObjectPrimitive.hpp"

ObjectPrimitive::ObjectPrimitive()
{
  _object = NULL;
}

ObjectPrimitive::ObjectPrimitive(Object *object,
				 const Point& absolutePosition,
				 const Rotation& rotation,
				 const Material& material)
{
  _object = object;
  _absolutePosition = absolutePosition;
  _rotation = rotation;
  _material = material;
}

ObjectPrimitive::~ObjectPrimitive()
{

}

const Object&         ObjectPrimitive::getObject(void) const
{
  return (*_object);
}

const Point&          ObjectPrimitive::getPosition(void) const
{
  return (_absolutePosition);
}

const Rotation&       ObjectPrimitive::getRotation(void) const
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

Ray           ObjectPrimitive::getRayAtSimplePosition(const Ray& ray) const
{
  Ray	      modified = ray;
  Vector      vector = ray.getVector();
  Rotation    rotation = _rotation * -1;
  Point       point = ray.getPoint();

  vector.rotate(rotation);
  modified.setVector(vector);

  point -= _absolutePosition;
  point.rotate(rotation);
  modified.setPoint(point);

  return (modified);
}
