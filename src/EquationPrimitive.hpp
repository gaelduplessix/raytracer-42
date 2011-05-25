//
// EquationPrimitive.hpp for ratracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Fri Apr 29 10:36:38 2011 loick michard
// Last update Wed May 25 10:50:29 2011 loick michard
//

#ifndef _EQUATIONPRIMITIVE_HPP_
#define _EQUATIONPRIMITIVE_HPP_

#include "ObjectPrimitive.hpp"
#include "Equation.hpp"

class EquationPrimitive : public ObjectPrimitive
{
public:
  EquationPrimitive(string equation,
		    Object*object,
		    const Point& absolutePosition,
		    const Rotation& rotation,
		    Material* material);

  void		getMappedCoords(const Point& intersectPoint,
				double& x, double &y) const;

  void		addIntersectionWithRay(const Ray& ray, vector<struct s_intersected_object>& intersection) const;
  void		intersectWithRay(const Ray& ray, ObjectPrimitive*& primitive, double &res) const;

  void		_injectCoeffs(const Ray& ray, EqNode* node) const;

  void		_injectNormalValues(const Point& point,
				    EqNode* node) const;

  Vector	getNormalVector(const Point& intersectPoint,
				const Vector& viewVector) const;
  Vector	getRefractedVector(const Point& intersectPoint,
				   const Ray& ray) const;
  bool		isInBoundingBox(BoundingBox& box) const;


private:
  Equation	_equation_intersect;
  Equation	_equation_normal_x;
  Equation	_equation_normal_y;
  Equation	_equation_normal_z;
};

#endif
