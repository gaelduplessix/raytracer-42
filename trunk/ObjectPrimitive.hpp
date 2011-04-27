//
// ObjectPrimitive.hpp for raytracer in /home/jochau_g//dev/c/raytracer/raytracer-42
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Tue Apr 26 17:15:41 2011 gael jochaud-du-plessix
// Last update Tue Apr 26 23:09:54 2011 gael jochaud-du-plessix
//

#ifndef _OBJECTPRIMITIVE_HPP_
#define _OBJECTPRIMITIVE_HPP_

#include "Vector.hpp"
#include "Point.hpp"
#include "Rotation.hpp"
#include "BoundingBox.hpp"
#include "Ray.hpp"
#include "Material.hpp"

class Object;

class ObjectPrimitive
{
public:
  ObjectPrimitive();
  ~ObjectPrimitive();
  
  Object&	getObject() const;
  Point&	getPosition() const;
  Rotation&	getRotation() const;
  Point&	getAbsolutePosition() const;

  virtual bool		intersectWithRay(Ray& ray) = 0;
  virtual Vector	getNormalVector(Point& intersectPoint) = 0;
  virtual Vector	getReflectedVector(Point& intersectPoint, Vector& vector) = 0;
  virtual Vector	getRefractedVector(Point& intersectPoint, Vector& vector) = 0;
  virtual bool		isInBoundingBox(BoundingBox& box) = 0;

private:
  Object&	_object;
  Point		_position;
  Rotation	_rotation;
  Point		_absolutePosition;
  Material	_material;
};

#endif
