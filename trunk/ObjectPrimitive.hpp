//
// ObjectPrimitive.hpp for raytracer in /home/jochau_g//dev/c/raytracer/raytracer-42
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Tue Apr 26 17:15:41 2011 gael jochaud-du-plessix
// Last update Thu Apr 28 16:25:37 2011 loick michard
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
  ObjectPrimitive(Object *object);
  ~ObjectPrimitive();
  
  const Object&		getObject(void) const;
  const Point&		getPosition(void) const;
  const Rotation&	getRotation(void) const;

  void		setObject(Object *object);
  void		setPosition(const Point& position);
  void		setRotation(const Rotation& rotation);
  void		setMaterial(const Material& material);

  virtual bool		intersectWithRay(const Ray& ray) = 0;
  virtual Vector	getNormalVector(const Point& intersectPoint) = 0;
  virtual Vector	getReflectedVector(const Point& intersectPoint,
					   const Vector& vector) = 0;
  virtual Vector	getRefractedVector(const Point& intersectPoint,
					   Vector& vector) = 0;
  virtual bool		isInBoundingBox(BoundingBox& box) = 0;

private:
  Object*	_object;
  Rotation	_rotation;
  Point		_absolutePosition;
  Material	_material;
};

#endif
