//
// ObjectPrimitive.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
//
// Made by loick michard
// Login   <michar_l@epitech.net>
//
// Started on  Wed Apr 27 18:55:34 2011 loick michard
// Last update Sat Jun  4 22:16:49 2011 loick michard
//

#include <cmath>

#include "ObjectPrimitive.hpp"
#include "Object.hpp"

ObjectPrimitive::ObjectPrimitive(void):
  _absolutePosition(Point(0, 0, 0)), _rotation(Point(0, 0, 0)),
  _material(NULL), _object(NULL), _isLimited(false)
{
}

ObjectPrimitive::ObjectPrimitive(Object *object,
				 const Point& absolutePosition,
				 const Rotation& rotation,
				 Material* material):
  _absolutePosition(absolutePosition), _rotation(rotation),
  _material(material), _object(object), _isLimited(false)
{
  if (!_material)
    _material = new Material("NULL");
}

Object*		ObjectPrimitive::getObject(void) const
{
  return (_object);
}

const Point&	ObjectPrimitive::getPosition(void) const
{
  return (_absolutePosition);
}

const Rotation&	ObjectPrimitive::getRotation(void) const
{
  return (_rotation);
}

Material*	ObjectPrimitive::getMaterial(void) const
{
  return (_material);
}

bool		ObjectPrimitive::isLimited(void)
{
  return (_isLimited);
}

void		ObjectPrimitive::setObject(Object *object)
{
  _object = object;
}

void		ObjectPrimitive::setPosition(const Point& position)
{
  _absolutePosition = position;
}

void		ObjectPrimitive::setRotation(const Rotation& rotation)
{
  _rotation = rotation;
}

void		ObjectPrimitive::setMaterial(Material* material)
{
  _material = material;
  if (!_material)
    _material = new Material("NULL");
}

Color
ObjectPrimitive::getColor(const Point& intersectPoint) const
{
  double      x;
  double      y;

  getMappedCoords(intersectPoint, x, y);
  if (_material)
    return (_material->getColor(x, y));
  else
    return (Color(255, 255, 255));
}
#include <iostream>
Vector
ObjectPrimitive::getNormal(const Point& intersectPoint,
			   const Vector& viewVector) const
{
  if (_material && _material->_hasNormalDeformation)
    {
      Vector normal = this->getNormalVector(intersectPoint, viewVector);

      if (_material->_hasBumpMap)
	{
	  double x, y;
	  getMappedCoords(intersectPoint, x, y);
	  double p = 5.0 * _material->_heightmap->_repeatWidth
	    / _material->_heightmap->getWidth();

	  double normX, normY;
	  normX = (double)_material->getHeightmapColor(x - p, y)._r / 255.0
	    - (double)_material->getHeightmapColor(x + p, y)._r / 255.0;
	  normY = (double)_material->getHeightmapColor(x, y - p)._r / 255.0
	    - (double)_material->getHeightmapColor(x, y + p)._r / 255.0;

	  Vector        newV1(normal._z, normal._y, -normal._x);
	  Vector        newV2 = newV1;
	  newV2 *= normal;

	  normX *= 10;
	  normY *= 10;
	  normal = normal + newV1 * normX + newV2 * normY;
	  normal.normalize();
	}
      if (_material->_deformationType == Material::WAVES_X)
	{
	  normal._x += cos((intersectPoint._x - _absolutePosition._x) *
			   _material->_deformationCoeff) *
	    (normal.getNorm() / 2);
	  normal.normalize();
	}
      if (_material->_deformationType == Material::WAVES_Y)
	{
          normal._y += cos((intersectPoint._y - _absolutePosition._y) *
			    _material->_deformationCoeff) *
            (normal.getNorm() / 2);
          normal.normalize();
        }
      if (_material->_deformationType == Material::WAVES_Z)
	{
          normal._z += cos((intersectPoint._z - _absolutePosition._z) *
			    _material->_deformationCoeff) *
            (normal.getNorm() / 2);
          normal.normalize();
        }
      return (normal);
    }
  else
    return (this->getNormalVector(intersectPoint, viewVector));
}

inline Ray	ObjectPrimitive::getRayAtSimplePosition(const Ray& ray) const
{
  Ray	      modified = ray;
  Vector      vector = ray._vector;
  Point       point = ray._point;

  point -= _absolutePosition;
  if (_rotation._x || _rotation._y || _rotation._z)
    {
      point.rotate(_rotation, true);
      vector.rotate(_rotation, true);
    }
  modified.setVector(vector);
  modified.setPoint(point);

  return (modified);
}

#include <iostream>

Vector
ObjectPrimitive::getReflectedVector(const Point& intersectPoint,
				    const Vector& vector,
				    bool doNormalize) const
{
  Vector	normal = this->getNormal(intersectPoint, vector);
  if (doNormalize)
    normal.normalize();
  double	scal = normal * vector;

  normal = normal * (-2 * scal) + vector;
  return (normal);
}

#include <stdio.h>

Ray		ObjectPrimitive::getRefractedRay(const Point& intersectPoint,
						 const Ray& ray,
						 stack<ObjectPrimitive*>&
						 refractivePath) const
{
  double	n2;
  if (refractivePath.size() > 0 && (this == refractivePath.top()
				    || (_object && refractivePath.top()
					->_object->isSolid() &&
					this->_object ==
					refractivePath.top()->_object)))
    {
      refractivePath.pop();
      n2 = (refractivePath.size() > 0) ?
  	refractivePath.top()->getMaterial()->getRefractionIndex() : 1;
    }
  else
    n2 = _material->getRefractionIndex();
  double	n = ray._refractiveIndex / n2;
  Vector	normal = getNormal(intersectPoint,
				   ray._vector);
  Ray		res(intersectPoint, ray._vector);
  res._vector.normalize();
  double	cos1 = normal * (res._vector * -1);
  double	cos2 = sqrt(1 - (n * n) * (1 - (cos1 * cos1)));

  res.setPoint(intersectPoint);
  res.setVector((res._vector * n) + normal * ((n * cos1) + cos2));
  return (res);
}

Point		ObjectPrimitive::getMax(void) const
{
  return (Point(0, 0, 0));
}

Point           ObjectPrimitive::getMin(void) const
{
  return (Point(0, 0, 0));
}
