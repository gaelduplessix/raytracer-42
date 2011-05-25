//
// Cylinder.hpp for ratracer in /home/michar_l//Raytracer/raytracer-42
//
// Made by loick michard
// Login   <michar_l@epitech.net>
//
// Started on  Fri Apr 29 10:36:38 2011 loick michard
// Last update Wed May 25 10:49:59 2011 loick michard
//

#ifndef _CYLINDER_HPP_
#define _CYLINDER_HPP_

#include "ObjectPrimitive.hpp"

class Cylinder : public ObjectPrimitive
{
public:
  Cylinder(Object *object,
	   const Point& absolutePosition,
	   const Rotation& rotation,
	   Material* material,
	   double radius);

  Cylinder(void);

  void		setRadius(double r);
  void		setLimitMin(double z);
  void		setLimitMax(double z);

  void		getMappedCoords(const Point& intersectPoint,
				double& x, double &y) const;
  void	addIntersectionWithRay(const Ray& ray,
			       vector<struct s_intersected_object>&
			       intersection) const;
  void                  intersectWithRay(const Ray& ray, ObjectPrimitive*&
					 primitive, double &res) const;
  Vector	getNormalVector(const Point& intersectPoint,
				const Vector& viewVector) const;
  bool		isInBoundingBox(BoundingBox& box) const;

private:
  double	_radius;
  double	_limitMin;
  double	_limitMax;
};

#endif
