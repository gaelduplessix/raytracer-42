//
// Object.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
//
// Made by loick michard
// Login   <michar_l@epitech.net>
//
// Started on  Wed Apr 27 18:53:38 2011 loick michard
// Last update Tue Jun  7 16:07:26 2011 gael jochaud-du-plessix
//

#include "Object.hpp"
#include "Triangle.hpp"

Object::Object(vector<ObjectPrimitive*> primitives, const Rotation& rotation,
	       const Point& position, bool isSolid):
  _primitives(primitives), _rotation(rotation), _scale(1, 1, 1),
  _position(position), _isSolid(isSolid)
{
}

Object::~Object(void)
{
  this->freePrimitives();
}

void	Object::freePrimitives(void)
{
  int	size = _primitives.size();

  for (int i = 0; i < size; i++)
    delete _primitives[i];
  _primitives.clear();
}

Object::Object(void)
{
}

const Vector&		Object::getRefractedVector(const Point& intersectPoint,
						   const Vector& vector)
{
  Point	tmp;

  tmp = intersectPoint;
  return (vector);
}

const vector<ObjectPrimitive*>&	Object::getPrimitives(void) const
{
  return (_primitives);
}

const ObjectPrimitive&	Object::getPrimitiveAtIndex(int index) const
{
  return (*_primitives[index]);
}

int			Object::getNbPrimitives(void) const
{
  return (_primitives.size());
}

const Rotation&		Object::getRotation(void) const
{
  return (_rotation);
}

const Point&		Object::getPosition(void) const
{
  return (_position);
}

bool			Object::isSolid(void)
{
  return (_isSolid);
}

void			Object::addPrimitive(ObjectPrimitive* primitive)
{
  _primitives.push_back(primitive);
}

void			Object::removePrimitiveAtIndex(int index)
{
  delete _primitives[index];
  _primitives.erase(_primitives.begin() + index);
}

void			Object::applyTransformations(void)
{
  Point			max(0, 0, 0);
  Point			min(0, 0, 0);
  Point			middle(0, 0, 0);
  bool			first = true;

  for (int i = 0, l = _primitives.size(); i < l; i++)
    {
      Point tmpMax = _primitives[i]->getMax();
      Point tmpMin = _primitives[i]->getMin();
      if (first || tmpMax._x > max._x)
	max._x = tmpMax._x;
      if (first || tmpMax._y > max._y)
	max._y = tmpMax._y;
      if (first || tmpMax._z > max._z)
	max._z = tmpMax._z;
      if (first || tmpMin._x < min._x)
	min._x = tmpMin._x;
      if (first || tmpMin._y < min._y)
	min._y = tmpMin._y;
      if (first || tmpMin._z < min._z)
	max._z = tmpMax._z;
      first = false;
    }
  middle = (max + min) / 2.0;
  for (int i = 0, l = _primitives.size(); i < l; i++)
    {
      Point p1 = ((Triangle*)_primitives[i])->getPosition();
      Point p2 = ((Triangle*)_primitives[i])->getVertex1();
      Point p3 = ((Triangle*)_primitives[i])->getVertex2();
      p1 -= middle;
      p2 -= middle;
      p3 -= middle;
      p1._x *= _scale._x;
      p1._y *= _scale._y;
      p1._z *= _scale._z;
      p2._x *= _scale._x;
      p2._y *= _scale._y;
      p2._z *= _scale._z;
      p3._x *= _scale._x;
      p3._y *= _scale._y;
      p3._z *= _scale._z;
      p1.rotate(_rotation);
      p2.rotate(_rotation);
      p3.rotate(_rotation);
      p1 += middle + _position;
      p2 += middle + _position;
      p3 += middle + _position;
      ((Triangle*)_primitives[i])->setPosition(p1);
      ((Triangle*)_primitives[i])->setVertex1(p2);
      ((Triangle*)_primitives[i])->setVertex2(p3);
      ((Triangle*)_primitives[i])->setCachedValues();
    }
}

void			Object::setPosition(const Point& position)
{
  _position = position;
}

void			Object::setRotation(const Rotation& rotation)
{
  _rotation = rotation;
}

void			Object::setScale(const Vector& scale)
{
  _scale = scale;
}

void			Object::setSolid(bool solid)
{
  _isSolid = solid;
}

void			Object::intersectWithRay(const Ray& ray,
						 ObjectPrimitive*& primitive,
						 double& k) const
{
  int			nbPrimitive;
  int			i = -1;

  nbPrimitive = _primitives.size();
  while (++i < nbPrimitive && primitive == NULL)
    _primitives[i]->intersectWithRay(ray, primitive, k);
}
