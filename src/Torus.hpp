//
// Torus.hpp for raytracer in /home/michar_l//Raytracer/raytracer-42
//
// Made by loick michard
// Login   <michar_l@epitech.net>
//
// Started on  Thu May  5 18:26:31 2011 loick michard
// Last update Wed May 11 19:24:35 2011 melvin laplanche
//

#ifndef _TORUS_HPP_
#define _TORUS_HPP_

#include "ObjectPrimitive.hpp"

class Torus : public ObjectPrimitive
{
public:
  Torus(void);
  Torus(Object*object,
	const Point& absolutePosition,
	const Rotation& rotation,
	const Material& material,
	double R, double r);

  void                  setr(double r);
  void                  setR(double R);

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
  double	_R;
  double	_r;
};

#endif
