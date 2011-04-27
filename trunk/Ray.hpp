//
// Ray.hpp for raytracer in /home/michar_l//Raytracer
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Wed Apr 27 15:11:51 2011 loick michard
// Last update Wed Apr 27 15:24:21 2011 loick michard
//

#ifndef _RAY_HPP_
#define _RAY_HPP_

class Ray
{
public:
  Ray();
  Ray(const Color& color, const Point& point,
      const Vector& vector, double refractiveIndex);
  ~Ray();

  void		setColor(const Color& color);
  void		setPoint(const Point& point);
  void		setVector(const Vector& vector);
  void		setRefractiveIndex(double refractiveIndex);

  const Color&	getColor() const;
  const Point&	getPoint() const;
  const Vector&	getVector() const;
  double	getRefractiveIndex() const;

private:
  Color		_color;
  Point		_point;
  Vector	_vector;
  double	_refractiveIndex;
};

#endif
