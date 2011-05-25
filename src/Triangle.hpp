//
// Triangle.hpp for ratracer in /home/michar_l//Raytracer/raytracer-42
//
// Made by loick michard
// Login   <michar_l@epitech.net>
//
// Started on  Fri Apr 29 10:36:38 2011 loick michard
// Last update Wed May 25 11:07:35 2011 loick michard
//

#ifndef _TRIANGLE_HPP_
#define _TRIANGLE_HPP_

#include "ObjectPrimitive.hpp"

class Triangle : public ObjectPrimitive
{
public:
  Triangle(Object*object,
	 const Point& absolutePosition,
	 Material* material,
	 const Point& vertex1,
	 const Point& vertex2);

  Triangle(void);

  void		setCachedValues(void);

  void		setVertex1(const Point& vertex1);
  void		setVertex2(const Point& vertex2);
  void		getMappedCoords(const Point& intersectPoint,
				double& x, double &y) const;
  void		addIntersectionWithRay(const Ray& ray,
				       vector<struct s_intersected_object>&
				       intersection) const;
  void		intersectWithRay(const Ray& ray,
				 ObjectPrimitive*& primitive,
				 double &res) const;
  Vector	getNormalVector(const Point& intersectPoint,
				const Vector& viewVector) const;
  Vector	getRefractedVector(const Point& intersectPoint,
				   const Ray& ray) const;
  bool		isInBoundingBox(BoundingBox& box) const;

  Point		getMax(void) const;
  Point		getMin(void) const;

private:
  Vector	_normal;
  Point		_vertex1;
  Point		_vertex2;
  Vector	_v1;
  Vector	_v2;
  double	_var1;
  double	_var2;
  double	_var3;
  double	_var4;
  double	_var5;
  double	_var6;
  double	_var7;
  double	_var8;
  double	_var9;
  double	_var10;
  double	_var11;
  double	_var12;
  double	_var13;
  double	_var14;
  double	_var15;
  double	_var16;
  double	_var17;
  double	_var18;
  double	_var19;
  double	_var20;
  double	_var21;
  double	_var22;
  double	_var23;
  double	_var24;
  double	_var25;
  double	_var26;
  double	_var27;
};

#endif
