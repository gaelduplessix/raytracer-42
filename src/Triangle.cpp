//
// Triangle.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
//
// Made by loick michard
// Login   <michar_l@epitech.net>
//
// Started on  Fri Apr 29 10:41:20 2011 loick michard
// Last update Thu May 12 17:11:41 2011 gael jochaud-du-plessix
//

#include <cmath>
#include <vector>
#include "Raytracer.hpp"
#include "Triangle.hpp"
#include "EquationSolver.hpp"

Triangle::Triangle(Object*object,
		   const Point& absolutePosition,
		   const Rotation& rotation,
		   const Material& material,
		   const Point& vertex1,
		   const Point& vertex2) : ObjectPrimitive(object,
							   absolutePosition,
							   rotation, material),
					   _vertex1(vertex1), _vertex2(vertex2)
{

}

Triangle::Triangle(void)
{

}

void		Triangle::setVertex1(const Point& vertex1)
{
  _vertex1 = vertex1;
}

void		Triangle::setVertex2(const Point& vertex2)
{
  _vertex2 = vertex2;
}

void		Triangle::getMappedCoords(const Point& intersectPoint,
					  double& x, double &y) const
{
  x = 0;
  y = 0;
  return ;
  (void)intersectPoint;
}

void
Triangle::addIntersectionWithRay(const Ray& ray,
				 vector<struct s_intersected_object>&
				 intersection) const
{
  Vector	v1 = _vertex1 - _absolutePosition;
  Vector	v2 = _vertex2 - _absolutePosition;
  double	D = -v1._z * ray._vector._y * v2._x + v1._y * ray._vector._z *
    v2._x + ray._vector._x * v1._z * v2._y + ray._vector._y * v1._x * v2._z
    - ray._vector._z * v1._x * v2._y-ray._vector._x * v1._y * v2._z;
  double	u = -(-ray._vector._y * v2._x * _absolutePosition._z -
		      ray._vector._y * ray._point._x * v2._z + ray._vector._y *
		      v2._x * ray._point._z + ray._vector._y *
		      _absolutePosition._x * v2._z + ray._vector._x * v2._y *
		      _absolutePosition._z - ray._vector._x * v2._y *
		      ray._point._z + v2._x * ray._vector._z *
		      _absolutePosition._y - v2._x * ray._vector._z *
		      ray._point._y + ray._point._x * ray._vector._z * v2._y +
		      ray._vector._x * ray._point._y * v2._z - ray._vector._x *
		      _absolutePosition._y * v2._z - _absolutePosition._x *
		      ray._vector._z * v2._y)/ D;
  double	v = (-ray._vector._x * v1._z * _absolutePosition._y -
		     ray._vector._x * v1._y * ray._point._z + ray._vector._x *
		     v1._z * ray._point._y + ray._vector._x * v1._y *
		     _absolutePosition._z + ray._vector._z * v1._x *
		     _absolutePosition._y + v1._y * ray._vector._z *
		     ray._point._x + v1._z * ray._vector._y *
		     _absolutePosition._x - ray._vector._z * v1._x *
		     ray._point._y - ray._vector._y * v1._x *
		     _absolutePosition._z - v1._y * ray._vector._z *
		     _absolutePosition._x + ray._vector._y * v1._x *
		     ray._point._z - v1._z * ray._vector._y * ray._point._x)
    / D;
  double	t = (-ray._point._x * v1._z * v2._y + ray._point._x * v1._y *
		     v2._z + _absolutePosition._x * v1._z * v2._y -
		     _absolutePosition._x * v1._y * v2._z - v1._x * v2._y *
		     _absolutePosition._z + v1._x * v2._y * ray._point._z -
		     v1._x * ray._point._y * v2._z + v1._x *
		     _absolutePosition._y * v2._z - v2._x * v1._z *
		     _absolutePosition._y - v2._x * v1._y * ray._point._z +
		     v2._x * v1._z * ray._point._y + v2._x * v1._y *
		     _absolutePosition._z) / D;

  if (u < 0 || t <= EPSILON || v < 0 || u + v > 1 || D == 0)
    return ;
  vector<double>       k;
  k.push_back(t);
  intersection.push_back((t_intersected_object){this, k});
}

void                  Triangle::intersectWithRay(const Ray& ray,
						 ObjectPrimitive*& primitive,
						 double &res) const
{
  Vector	v1 = _vertex1 - _absolutePosition;
  Vector	v2 = _vertex2 - _absolutePosition;
  double	D = -v1._z * ray._vector._y * v2._x + v1._y * ray._vector._z *
    v2._x + ray._vector._x * v1._z * v2._y + ray._vector._y * v1._x * v2._z
    - ray._vector._z * v1._x * v2._y-ray._vector._x * v1._y * v2._z;
  double	u = -(-ray._vector._y * v2._x * _absolutePosition._z -
		      ray._vector._y * ray._point._x * v2._z + ray._vector._y *
		      v2._x * ray._point._z + ray._vector._y *
		      _absolutePosition._x * v2._z + ray._vector._x * v2._y *
		      _absolutePosition._z - ray._vector._x * v2._y *
		      ray._point._z + v2._x * ray._vector._z *
		      _absolutePosition._y - v2._x * ray._vector._z *
		      ray._point._y + ray._point._x * ray._vector._z * v2._y +
		      ray._vector._x * ray._point._y * v2._z - ray._vector._x *
		      _absolutePosition._y * v2._z - _absolutePosition._x *
		      ray._vector._z * v2._y)/ D;
  double	v = (-ray._vector._x * v1._z * _absolutePosition._y -
		     ray._vector._x * v1._y * ray._point._z + ray._vector._x *
		     v1._z * ray._point._y + ray._vector._x * v1._y *
		     _absolutePosition._z + ray._vector._z * v1._x *
		     _absolutePosition._y + v1._y * ray._vector._z *
		     ray._point._x + v1._z * ray._vector._y *
		     _absolutePosition._x - ray._vector._z * v1._x *
		     ray._point._y - ray._vector._y * v1._x *
		     _absolutePosition._z - v1._y * ray._vector._z *
		     _absolutePosition._x + ray._vector._y * v1._x *
		     ray._point._z - v1._z * ray._vector._y * ray._point._x)
    / D;
  double	t = (-ray._point._x * v1._z * v2._y + ray._point._x * v1._y *
		     v2._z + _absolutePosition._x * v1._z * v2._y -
		     _absolutePosition._x * v1._y * v2._z - v1._x * v2._y *
		     _absolutePosition._z + v1._x * v2._y * ray._point._z -
		     v1._x * ray._point._y * v2._z + v1._x *
		     _absolutePosition._y * v2._z - v2._x * v1._z *
		     _absolutePosition._y - v2._x * v1._y * ray._point._z +
		     v2._x * v1._z * ray._point._y + v2._x * v1._y *
		     _absolutePosition._z) / D;

  if (u < 0 || t <= EPSILON || v < 0 || u + v > 1 || D == 0)
    return ;
  if (t < res || res < 0)
    {
      res = t;
      primitive = (ObjectPrimitive*)this;
    }
}

Vector		Triangle::getNormalVector(const Point& intersectPoint,
					const Vector& viewVector) const
{
  Vector	u = _absolutePosition - _vertex1;
  Vector	v = _absolutePosition - _vertex2;
  Vector	normal(u._y * v._z - v._y * u._z,
		       u._z * v._x - v._z * u._x,
		       u._x * v._y - v._x * u._y);
  double	cosA = viewVector * normal;

  cosA = cosA / (viewVector.getNorm() * normal.getNorm());
  if (cosA <= 0)
    return (normal.normalize() * -1);
  return (normal.normalize());
  (void)intersectPoint;
}

bool		Triangle::isInBoundingBox(BoundingBox& box) const
{
  box = box;
  return (true);
}
