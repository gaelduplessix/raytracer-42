//
// ObjectPrimitive.hpp for raytracer in /home/jochau_g//dev/c/raytracer/raytracer-42
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Tue Apr 26 17:15:41 2011 gael jochaud-du-plessix
// Last update Sat Apr 30 20:51:15 2011 loick michard
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
struct s_intersected_object;

class ObjectPrimitive
{
public:
  ObjectPrimitive();
  ObjectPrimitive(Object *object,
		  const Point& absolutePosition,
		  const Rotation& rotation,
		  const Material& material);

  const Object&		getObject(void) const;
  const Point&		getPosition(void) const;
  const Rotation&	getRotation(void) const;
  const Material&	getMaterial(void) const;

  void		setObject(Object *object);
  void		setPosition(const Point& position);
  void		setRotation(const Rotation& rotation);
  void		setMaterial(const Material& material);

  virtual void			addIntersectionWithRay(const Ray& ray, vector<struct s_intersected_object>& intersection) const = 0;

  virtual void
  intersectWithRay(const Ray& ray, ObjectPrimitive*& primitive,
		   double &res) const = 0;
  virtual Vector
  getNormalVector(const Point& intersectPoint) const = 0;
  Vector	getReflectedVector(const Point& intersectPoint,
				   const Vector& vector,
				   bool doNormalize=false) const;
  virtual Vector	getRefractedVector(const Point& intersectPoint,
					   Vector& vector) const = 0;
  virtual bool		isInBoundingBox(BoundingBox& box) const = 0;

protected:
  inline virtual Ray		getRayAtSimplePosition(const Ray& ray) const;
  Point			_absolutePosition;

  Object*	_object;
  Rotation	_rotation;
  Material	_material;
};

#endif
