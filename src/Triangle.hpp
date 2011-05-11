//
// Triangle.hpp for ratracer in /home/michar_l//Raytracer/raytracer-42
//
// Made by loick michard
// Login   <michar_l@epitech.net>
//
// Started on  Fri Apr 29 10:36:38 2011 loick michard
// Last update Wed May 11 23:16:27 2011 melvin laplanche
//

#ifndef _TRIANGLE_HPP_
#define _TRIANGLE_HPP_

#include "ObjectPrimitive.hpp"

class Triangle : public ObjectPrimitive
{
public:
  Triangle(Object*object,
	 const Point& absolutePosition,
	 const Rotation& rotation,
	 const Material& material,
	 const Point& vertex1,
	 const Point& vertex2);

  Triangle(void);

  void		setVertex1(const Point& vertex1);
  void		setVertex2(const Point& vertex2);
  void		getMappedCoords(const Point& intersectPoint,
				double& x, double &y) const;
  void        addIntersectionWithRay(const Ray& ray,
				     vector<struct s_intersected_object>&
				     intersection) const;
  void                  intersectWithRay(const Ray& ray,
					 ObjectPrimitive*& primitive,
					 double &res) const;
  Vector	getNormalVector(const Point& intersectPoint,
				const Vector& viewVector) const;
  Vector	getRefractedVector(const Point& intersectPoint,
				   const Ray& ray) const;
  bool		isInBoundingBox(BoundingBox& box) const;

private:
  Point		_vertex1;
  Point		_vertex2;
};

#endif
