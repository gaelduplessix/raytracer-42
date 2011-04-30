//
// Vector.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Wed Apr 27 22:40:10 2011 loick michard
// Last update Sat Apr 30 11:27:18 2011 loick michard
//

#include <cmath>
#include "Vector.hpp"

Vector::Vector()
{
  _x = _y = _z = 0;
}

Vector::Vector(double x, double y, double z)
{
  _x = x;
  _y = y;
  _z = z;
}

Vector::~Vector()
{

}

double	Vector::getX(void) const
{
  return (_x);
}

double	Vector::getY(void) const
{
  return (_y);
}

double	Vector::getZ(void) const
{
  return (_z);
}

void	Vector::setX(double x)
{
  _x = x;
}

void	Vector::setY(double y)
{
  _y = y;
}

void	Vector::setZ(double z)
{
  _z = z;
}

double	Vector::getNorm(void)
{
  return (sqrt(_x * _x + _y * _y + _z * _z));
}

void	Vector::normalize(void)
{
  double norm;

  norm = this->getNorm();
  _x = _x / norm;
  _y = _y / norm;
  _z = _z / norm;
}

void	Vector::rotateX(double alpha)
{
  double yp;
  double zp;

  yp = cos(alpha) * _y - sin(alpha) * _z;
  zp = sin(alpha) * _y + cos(alpha) * _z;
  _y = yp;
  _z = zp;
}

void    Vector::rotateY(double alpha)
{
  double xp;
  double zp;

  xp = cos(alpha) * _x + sin(alpha) * _z;
  zp = - sin(alpha) * _x + cos(alpha) * _z;
  _x = xp;
  _z = zp;
}

void    Vector::rotateZ(double alpha)
{
  double xp;
  double yp;

  xp = cos(alpha) * _x - sin(alpha) * _y;
  yp = sin(alpha) * _x + cos(alpha) * _y;
  _x = xp;
  _y = yp;
}

void	Vector::rotate(const Vector& rotation)
{
  this->rotateX(rotation.getX());
  this->rotateY(rotation.getY());
  this->rotateZ(rotation.getZ());
}

Vector&	Vector::operator+=(const Vector& vector)
{
  _x += vector.getX();
  _y += vector.getY();
  _z += vector.getZ();
  return (*this);
}

Vector&	Vector::operator-=(const Vector& vector)
{
  _x -= vector.getX();
  _y -= vector.getY();
  _z -= vector.getZ();
  return (*this);
}

Vector&	Vector::operator*=(const Vector& vector)
{
  double xp;
  double yp;
  double zp;

  xp = _y * vector.getZ() - _z * vector.getY();
  yp = _z * vector.getX() - _x * vector.getZ();
  zp = _x * vector.getY() - _y * vector.getX();
  _x = xp;
  _y = yp;
  _z = zp;
  return (*this);
}

double   operator*(const Vector& vector, const Vector& vector2)
{
  return (vector._x * vector2._x + vector._y * vector2._y +
	  vector._z * vector2._z);
}
