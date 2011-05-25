//
// Plane.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
//
// Made by loick michard
// Login   <michar_l@epitech.net>
//
// Started on  Sat Apr 30 10:19:08 2011 loick michard
// Last update Wed May 25 10:55:55 2011 loick michard
//

#include <vector>
#include "Raytracer.hpp"
#include "Plane.hpp"

Plane::Plane(void):
  _limitX(-1), _limitY(-1)
{

}

Plane::Plane(Object*object,
	     const Point& absolutePosition,
	     const Rotation& rotation,
	     Material* material):
  ObjectPrimitive(object, absolutePosition, rotation, material),
  _limitX(-1), _limitY(-1)
{

}

void  Plane::setLimitX(double limitX)
{
  _limitX = limitX;
}

void  Plane::setLimitY(double limitY)
{
  _limitY = limitY;
}

double        Plane::getLimitX(void)
{
  return (_limitX);
}

double        Plane::getLimitY(void)
{
  return (_limitY);
}


void  Plane::getMappedCoords(const Point& intersectPoint,
		      double& x, double &y) const
{
  Point simplePoint = intersectPoint - _absolutePosition;
  simplePoint.rotate(_rotation);
  x = simplePoint._x;
  y = simplePoint._y;
}

void		       Plane::addIntersectionWithRay(const Ray& ray, vector<struct s_intersected_object>& intersection) const
{
  Ray           newRay;

  newRay = getRayAtSimplePosition(ray);
  if (newRay._vector._z == 0)
    return ;
  double result(- newRay._point._z / newRay._vector._z);
  if (result < EPSILON)
    return ;
  vector<double> k;
  Point		 intersectPoint;
  if (_limitX > 0 || _limitY > 0)
    {
      intersectPoint = newRay._point + newRay._vector * result;
      if (_limitX > 0 && ((intersectPoint._x < 0)
			  || (intersectPoint._x > _limitX)))
	return ;
      if (_limitY > 0 && ((intersectPoint._y < 0)
			  || (intersectPoint._y > _limitY)))
	return ;
    }
  intersectPoint = ray._point + ray._vector * result;
  double x, y;
  getMappedCoords(intersectPoint, x, y);
  if (!_material->isLimitedAtPoint(x, y))
    {
      k.push_back(result);
      intersection.push_back((t_intersected_object){this, k});
    }
}

void                  Plane::intersectWithRay(const Ray& ray,
					      ObjectPrimitive*& primitive,
					      double &res) const
{
  Ray           newRay;

  newRay = getRayAtSimplePosition(ray);
  if (newRay._vector._z == 0)
    return ;
  double result(- newRay._point._z / newRay._vector._z);
  if (result <= EPSILON)
    return ;
  if (result < res || res < 0)
    {
      Point	intersectPoint;
      if (_limitX > 0 || _limitY > 0)
      	{
      	  intersectPoint = newRay._point + newRay._vector * result;
      	  if (_limitX > 0 && ((intersectPoint._x < 0)
      			      || (intersectPoint._x > _limitX)))
      	    return ;
      	  if (_limitY > 0 && ((intersectPoint._y < 0)
      			      || (intersectPoint._y > _limitY)))
      	    return ;
      	}
      intersectPoint = ray._point + ray._vector * result;
      double x, y;
      getMappedCoords(intersectPoint, x, y);
      if (!_material->isLimitedAtPoint(x, y))
	{
	  primitive = (ObjectPrimitive*)this;
	  res = result;
	}
    }
}

Vector		Plane::getNormalVector(const Point& intersectPoint,
				       const Vector& viewVector) const
{
  Vector	normal(0, 0, 1);
  normal.rotate(_rotation);
  double        cosA = viewVector * normal;
  cosA = cosA / (viewVector.getNorm() * normal.getNorm());
  if (cosA < 0)
    return (normal * -1);
  return (normal);
  (void)intersectPoint;
}

bool		Plane::isInBoundingBox(BoundingBox& box) const
{
  return (true);
  (void)box;
}
