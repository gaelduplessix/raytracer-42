//
// Vector.hpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Wed Apr 27 22:39:57 2011 loick michard
// Last update Thu Apr 28 14:01:15 2011 loick michard
//

#ifndef _VECTOR_H_
#define _VECTOR_H_

class Rotation;

class Vector
{
public:
  Vector();
  Vector(double x, double y, double z);
  ~Vector();
  
  double	getX(void) const;
  double	getY(void) const;
  double	getZ(void) const;
  void		setX(double value);
  void		setY(double value);
  void		setZ(double value);

  double	getNorm(void);
  void		rotate(Vector& rotation);
  void		normalize(void);

  Vector&       operator+=(const Vector& vector);
  Vector&       operator-=(const Vector& vector);
  Vector&       operator*=(const Vector& vector);

private:
  void		rotateX(double alpha);
  void		rotateY(double alpha);
  void		rotateZ(double alpha);
  double	_x;
  double	_y;
  double	_z;
};

Vector   operator+(const Vector& vector1, const Vector& vector2);
Vector   operator-(const Vector& vector1, const Vector& vector2);
Vector   operator*(const Vector& vector1, const Vector& vector2);

#endif
