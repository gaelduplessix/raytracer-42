//
// ObjectPrimitive.hpp for raytracer in /home/jochau_g//dev/c/raytracer/raytracer-42
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Tue Apr 26 17:15:41 2011 gael jochaud-du-plessix
// Last update Fri Apr 29 18:39:36 2011 samuel olivier
//

#ifndef _OBJECTPRIMITIVE_HPP_
#define _OBJECTPRIMITIVE_HPP_

#include <vector>
#include "Vector.hpp"
#include "Point.hpp"
#include "Rotation.hpp"
#include "BoundingBox.hpp"
#include "Ray.hpp"
#include "Material.hpp"

using namespace std;

class Object;

class ObjectPrimitive
{
public:
  ObjectPrimitive();
  ObjectPrimitive(Object *object,
		  const Point& absolutePosition,
		  const Rotation& rotation,
		  const Material& material);
  ~ObjectPrimitive();
  
  const Object&		getObject(void) const;
  const Point&		getPosition(void) const;
  const Rotation&	getRotation(void) const;

  void		setObject(Object *object);
  void		setPosition(const Point& position);
  void		setRotation(const Rotation& rotation);
  void		setMaterial(const Material& material);

  virtual vector<double>	intersectWithRay(const Ray& ray) const = 0;

  virtual Vector	getNormalVector(const Point& intersectPoint) const = 0;
  virtual Vector	getReflectedVector(const Point& intersectPoint,
					   const Vector& vector) const = 0;
  virtual Vector	getRefractedVector(const Point& intersectPoint,
					   Vector& vector) const = 0;
  virtual bool		isInBoundingBox(BoundingBox& box) const = 0;

protected:
  virtual Ray		getRayAtSimplePosition(const Ray& ray) const;
  Point			_absolutePosition;

private:
  Object*	_object;
  Rotation	_rotation;
  Material	_material;
};

#endif
