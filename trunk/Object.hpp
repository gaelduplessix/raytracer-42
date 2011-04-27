//
// Object.hpp for raytracer in /home/michar_l//Raytracer
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Tue Apr 26 16:52:19 2011 loick michard
// Last update Wed Apr 27 18:08:05 2011 loick michard
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
  Object();
  ~Object();
  
  int			getNbPrimitives() const;
  ObjectPrimitive&	getPrimitiveAtIndex(int index) const;
  Rotation&		getRotation() const;
  Point&		getPosition() const;
  void			addPrimitive(const ObjectPrimitive& primitive);
  void			removePrimitiveAtIndex(int index);
  void			setPosition(const Point& position);
  void			setRotation(const Rotation& rotation);
  bool			isSolid();
  bool			setSolid(int solid=1);

  virtual Vector        getRefractedVector(Point& intersectPoint, Vector& vector);

private:
  vector<ObjectPrimitive>	_primitives;
  Rotation			_rotation;
  Point				_position;
  bool				_isSolid;
};

#endif
