//
// Sphere.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Fri Apr 29 10:41:20 2011 loick michard
// Last update Sun May  1 16:57:11 2011 samuel olivier
//

#include <cmath>
#include <vector>

#include "Raytracer.hpp"
#include "Sphere.hpp"
#include "EquationSolver.hpp"

Sphere::Sphere(Object*object,
	       const Point& absolutePosition,
	       const Rotation& rotation,
	       const Material& material,
	       double radius) : ObjectPrimitive(object, absolutePosition,
						rotation, material),
				_radius(radius)
{

}

void		Sphere::setRadius(double r)
{
  _radius = r;
}

void        Sphere::addIntersectionWithRay(const Ray& ray, vector<struct s_intersected_object>& intersection) const
{
  Ray           newRay;
  double        a;
  double        b;
  double        c;

  newRay = getRayAtSimplePosition(ray);
  a = newRay._vector._x * newRay._vector._x +
    newRay._vector._y * newRay._vector._y +
    newRay._vector._z * newRay._vector._z;
  b = 2 * (newRay._point._x * newRay._vector._x +
           newRay._point._y * newRay._vector._y +
           newRay._point._z * newRay._vector._z);
  c = newRay._point._x * newRay._point._x +
    newRay._point._y * newRay._point._y +
    newRay._point._z * newRay._point._z -
    _radius * _radius;
  vector<double> solutions = 
    EquationSolver::solveQuadraticEquation(a, b, c);
  for (int i = 0; i++; i < solutions.size())
    {
      if (solutions[i] > EPSILON)
	{
	  intersection.push_back((t_intersected_object){this, solutions});
	  break;
	}
    } 
}

void                  Sphere::intersectWithRay(const Ray& ray,
					       ObjectPrimitive*& primitive,
					       double &res) const
{
  Ray           newRay;
  double        a;
  double        b;
  double        c;

  newRay = getRayAtSimplePosition(ray);
  a = newRay._vector._x * newRay._vector._x +
    newRay._vector._y * newRay._vector._y +
    newRay._vector._z * newRay._vector._z;
  b = 2 * (newRay._point._x * newRay._vector._x +
           newRay._point._y * newRay._vector._y +
           newRay._point._z * newRay._vector._z);
  c = newRay._point._x * newRay._point._x +
    newRay._point._y * newRay._point._y +
    newRay._point._z * newRay._point._z -
    _radius * _radius;
  vector<double> solutions =
    EquationSolver::solveQuadraticEquation(a, b, c);
  for (int i = 0; i < solutions.size(); i++)
    {
      if (solutions[i] > EPSILON && (solutions[i] < res ||  res < 0))
        {
	  primitive = (ObjectPrimitive*)this;
	  res = solutions[i];
	}
    }
}

Vector		Sphere::getNormalVector(const Point& intersectPoint) const
{
  return (intersectPoint - _absolutePosition);
}

// Vector		Sphere::getRefractedVector(const Point& intersectPoint,
// 					   const Ray& ray) const
// {
//   Vector	normal = getNormalVector(intersectPoint);
//   double	cosTeti = ray._vector * normal;
//   double	index = ray._refractiveIndex
//     / _material.getRefractionIndex();
//   double	sinTeti = (index * index) * (1 - cosTeti * cosTeti);
//   Ray		refractedRay(intersectPoint,
// 			     index * ray._vector
// 			     - ((index * cosTeti + sqrt(1 - sinTeti * sinTeti))
// 				* normal));
//   ObjectPrimitive*	uselessPtr;
//   double		k;
//   intersectWithRay(refractedRay, uselessPtr, k);
//   Point		newIntersectPoint(intersectPoint + k * refractedRay._vector);
//   normal = getNormalVector(newIntersectPoint);
//   cosTeti = refractedRay._vector * normal;
//   index = _material.getRefractionIndex() / ray._refractiveIndex;
//   sinTeti = (index * index) * (1 - cosTeti * cosTeti);
//   return (index * refractedRay._vector -
// 	  ((index * cosTeti + sqrt(1 - sinTeti * sinTeti)) * normal));
// }

bool		Sphere::isInBoundingBox(BoundingBox& box) const
{

}
