//
// BoundingBox.hpp for raytracer in /home/jochau_g//data/dev/c/raytracer/raytracer-42
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Tue Apr 26 18:49:27 2011 gael jochaud-du-plessix
// Last update Mon May 23 09:24:51 2011 loick michard
//

#ifndef _BOUNDINGBOX_H_
#define _BOUNDINGBOX_H_

#include "Vector.hpp"
#include "Point.hpp"
#include "Parallelogram.hpp"

class BoundingBox
{
public:
  BoundingBox();
  BoundingBox(const Point& vertex1, const Point& vertex2);
  ~BoundingBox();

  void		setVertices(const Point& vertex1, const Point&vertex2);
  void		setVertex1(const Point& vertex);
  void		setVertex2(const Point& vertex);
  
  Point		getCenterPosition() const;
  const Point&	getVertex1() const;
  const Point&	getVertex2() const;

  double	intersectWithRay(const Ray& ray);

  Point		getMaxPoint() const;
  Point		getMinPoint() const;

  double	size() const;

private:
  void          setParallelogram();

  Point	_vertex1;
  Point	_vertex2;
  Parallelogram _face1;
  Parallelogram _face2;
  Parallelogram _face3;
  Parallelogram _face4;
  Parallelogram _face5;
  Parallelogram _face6;
};

#endif
