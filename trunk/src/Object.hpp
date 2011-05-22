//
// Object.hpp for raytracer in /home/michar_l//Raytracer
//
// Made by loick michard
// Login   <michar_l@epitech.net>
//
// Started on  Tue Apr 26 16:52:19 2011 loick michard
// Last update Sat May 21 10:42:27 2011 loick michard
//

#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_

#include <vector>

#include "Vector.hpp"
#include "Point.hpp"
#include "Rotation.hpp"
#include "ObjectPrimitive.hpp"

using namespace std;

class Object
{
public:
  Object(vector<ObjectPrimitive*> primitives, const Rotation& rotation,
  	 const Point& position, bool isSolid);

  Object(void);

  int					getNbPrimitives() const;
  const ObjectPrimitive&		getPrimitiveAtIndex(int index) const;
  const vector<ObjectPrimitive*>&	getPrimitives(void) const;
  const Rotation&			getRotation() const;
  const Point&				getPosition() const;
  bool					isSolid();
  void				addPrimitive(ObjectPrimitive *primitive);
  void				removePrimitiveAtIndex(int index);
  void				setPosition(const Point& position);
  void				setRotation(const Rotation& rotation);
  void				setSolid(bool solid = true);

  virtual const Vector&		getRefractedVector(const Point& intersectPoint,
						   const Vector& vector);

  void				intersectWithRay(const Ray& ray,
						 ObjectPrimitive*& primitive,
						 double& k) const;

  vector<ObjectPrimitive*>	_primitives;
protected:
  Rotation			_rotation;
  Point				_position;
  bool				_isSolid;
};

#endif
