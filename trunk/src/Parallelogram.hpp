//
// Parallelogram.hpp for ratracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Fri Apr 29 10:36:38 2011 loick michard
// Last update Tue May 31 15:09:29 2011 loick michard
//

#ifndef _PARALLELOGRAM_HPP_
#define _PARALLELOGRAM_HPP_

#include "ObjectPrimitive.hpp"

class Parallelogram : public ObjectPrimitive
{
public:
  Parallelogram(Object* object,
		const Point& absolutePosition,
		const Point& vertex1,
		const Point& vertex2,
		Material* material,
		const Point& _textureVertex1 = Point(0, 0),
		const Point& _textureVertex2 = Point(0, 1),
		const Point& _textureVertex3 = Point(1, 1));
  Parallelogram(void);
  void		setCachedValues(void);
  void		setVertex1(const Point& vertex1);
  void		setVertex2(const Point& vertex2);

  void		setTextureVertex1(const Point& textureVertex1);
  void		setTextureVertex2(const Point& textureVertex2);
  void		setTextureVertex3(const Point& textureVertex3);
  const Point&	getTextureVertex1(void);
  const Point&	getTextureVertex2(void);
  const Point&	getTextureVertex3(void);

  void		getMappedCoords(const Point& intersectPoint,
				double& x, double &y) const;
  void		addIntersectionWithRay(const Ray& ray,
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
  Point		getMax(void) const;
  Point		getMin(void) const;

private:
  Point		_vertex1;
  Point		_vertex2;
  Vector        _normal;
  Point		_textureVertex1;
  Point		_textureVertex2;
  Point		_textureVertex3;
  Vector	_textureV1;
  Vector	_textureV2;
  Vector        _v1;
  Vector        _v2;
  double        _var1;
  double        _var2;
  double        _var3;
  double        _var4;
  double        _var5;
  double        _var6;
  double        _var7;
  double        _var8;
  double        _var9;
  double        _var10;
  double        _var11;
  double        _var12;
  double        _var13;
  double        _var14;
  double        _var15;
  double        _var16;
  double        _var17;
  double        _var18;
  double        _var19;
  double        _var20;
  double        _var21;
  double        _var22;
  double        _var23;
  double        _var24;
  double        _var25;
  double        _var26;
  double        _var27;
};

#endif
