//
// Cylinder.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
//
// Made by loick michard
// Login   <michar_l@epitech.net>
//
// Started on  Fri Apr 29 10:41:20 2011 loick michard
// Last update Thu May 26 15:13:33 2011 samuel olivier
//

#include <cmath>
#include <vector>
#include "Raytracer.hpp"
#include "Cylinder.hpp"
#include "EquationSolver.hpp"

Cylinder::Cylinder(Object*object,
		   const Point& absolutePosition,
		   const Rotation& rotation,
		   Material* material,
		   double radius) : ObjectPrimitive(object,absolutePosition,
						    rotation, material),
				    _radius(radius), _limitMin(-1),
				    _limitMax(-1)
{

}

Cylinder::Cylinder(void) : _limitMin(-1), _limitMax(-1)
{

}

void		Cylinder::setRadius(double r)
{
  _radius = r;
}

void		Cylinder::setLimitMin(double z)
{
  _limitMin = z;
}

void		Cylinder::setLimitMax(double z)
{
  _limitMax = z;
}

void		Cylinder::getMappedCoords(const Point& intersectPoint,
				double& x, double &y) const
{
  Point	intersect = intersectPoint;
  intersect.rotate(_rotation, true);
  Point newPoint = intersect - _absolutePosition;
  Vector vn(0, 0, -1);
  Vector ve(1, 0, 0);

  y = -newPoint._z;
  newPoint.rotate(_rotation);
  newPoint.normalize();
  double phi = acos(- (vn * newPoint));
  double theta = (acos((newPoint * ve) / sin(phi))) / (2 * M_PI);
  vn *= ve;
  double y2;
  if (vn * newPoint > 0)
    y2 = theta;
  else
    y2 =  1 - theta;
  x = y2;
}

void
Cylinder::addIntersectionWithRay(const Ray& ray,
				 vector<struct s_intersected_object>&
				 intersection) const
{
  Ray           newRay;
  double        a;
  double        b;
  double        c;

  newRay = getRayAtSimplePosition(ray);
  a = newRay._vector._x * newRay._vector._x +
    newRay._vector._y * newRay._vector._y;
  b = 2 * (newRay._point._x * newRay._vector._x +
           newRay._point._y * newRay._vector._y);
  c = newRay._point._x * newRay._point._x +
    newRay._point._y * newRay._point._y -
    _radius * _radius;
  vector<double> solutions =
    EquationSolver::solveQuadraticEquation(a, b, c);
  vector<double> validSolutions;
  for (unsigned int i = 0 ; i < solutions.size(); i++)
    if (solutions[i] > EPSILON)
      {
	bool	limited = false;
	Point   intersectPoint;
	intersectPoint = newRay._point + newRay._vector * solutions[i];
	if (_limitMin > 0 && ((intersectPoint._z < -_limitMin)))
	  limited = true;
	if (_limitMax > 0 && ((intersectPoint._z > _limitMax)))
	  limited = true;
        intersectPoint = ray._point + ray._vector * solutions[i];
        double x, y;
        getMappedCoords(intersectPoint, x, y);
        if (!limited && !_material->isLimitedAtPoint(x, y))
          validSolutions.push_back(solutions[i]);
      }
  if (validSolutions.size() > 0)
    intersection.push_back((t_intersected_object){this, validSolutions});
}

void                  Cylinder::intersectWithRay(const Ray& ray,
						 ObjectPrimitive*& primitive,
						 double &res) const
{
  Ray           newRay;
  double        a;
  double        b;
  double        c;

  newRay = getRayAtSimplePosition(ray);
  a = newRay._vector._x * newRay._vector._x +
    newRay._vector._y * newRay._vector._y;
  b = 2 * (newRay._point._x * newRay._vector._x +
           newRay._point._y * newRay._vector._y);
  c = newRay._point._x * newRay._point._x +
    newRay._point._y * newRay._point._y -
    _radius * _radius;
  vector<double> solutions =
    EquationSolver::solveQuadraticEquation(a, b, c);
  for (unsigned int i = 0; i < solutions.size(); i++)
    {
      if (solutions[i] > EPSILON && (solutions[i] < res ||  res < 0))
        {
	  Point intersectPoint;
	  bool	limited = false;
	  if (_limitMin > 0 || _limitMax > 0)
	    {
	      intersectPoint = newRay._point + newRay._vector * solutions[i];
	      if (_limitMin > 0 && ((intersectPoint._z < -_limitMin)))
		limited = true;
	      if (_limitMax > 0 && ((intersectPoint._z > _limitMax)))
		limited = true;
	    }
          intersectPoint = ray._point + ray._vector * solutions[i];
          double x, y;
          getMappedCoords(intersectPoint, x, y);
          if (!limited && !_material->isLimitedAtPoint(x, y))
            {
              primitive = (ObjectPrimitive*)this;
              res = solutions[i];
            }
        }
    }
}

Vector		Cylinder::getNormalVector(const Point& intersectPoint,
					  const Vector& viewVector) const
{
  Point		pos = intersectPoint - _absolutePosition;
  pos.rotate(_rotation, true);
  pos += _absolutePosition;
  Vector	normal = pos - _absolutePosition;
  normal._z = 0;
  normal.rotate(_rotation);
  double	cosA = viewVector * normal;

  cosA = cosA / (viewVector.getNorm() * normal.getNorm());
  if (cosA <= 0)
    return (normal.normalize() * -1);
  return (normal.normalize());
}

bool		Cylinder::isInBoundingBox(BoundingBox& box) const
{
  return (true);
  (void)box;
}
