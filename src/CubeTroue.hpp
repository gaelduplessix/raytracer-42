//
// CubeTroue.hpp for raytracer in /home/michar_l//Raytracer/raytracer-42/src
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Fri May  6 15:49:30 2011 loick michard
// Last update Fri May  6 16:03:23 2011 loick michard
//

#ifndef _CUBE_TROUE_HPP_
#define _CuBE_TROUE_HPP_

#include "ObjectPrimitive.hpp"

class CubeTroue: public ObjectPrimitive
{
public:
  CubeTroue(Object*object,
	    const Point& absolutePosition,
	    const Rotation& rotation,
	    const Material& material,
	    double coeff = 11.8);

  void	setCoeff(double coeff);
  void                  getMappedCoords(const Point& intersectPoint,
                                        double& x, double &y) const;
  void
  addIntersectionWithRay(const Ray& ray,
                         vector<struct s_intersected_object>& intersection) const;
  void                  intersectWithRay(const Ray& ray,
                                         ObjectPrimitive*& primitive,
                                         double &res) const;
  Vector        getNormalVector(const Point& intersectPoint,
                                const Vector& viewVector) const;
  Vector        getRefractedVector(const Point& intersectPoint,
                                   const Ray& ray) const;
  bool          isInBoundingBox(BoundingBox& box) const;

private:
  double	_coeff;
};

#endif
