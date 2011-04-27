//
// Vector.hpp for raytracer in /home/jochau_g//dev/c/raytracer/raytracer-42
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Tue Apr 26 18:21:04 2011 gael jochaud-du-plessix
// Last update Wed Apr 27 22:05:12 2011 samuel olivier
//


#ifndef _VECTOR_H_
#define _VECTOR_H_

class Rotation;

class Vector
{
public:
  Vector();
  ~Vector();
  
  double	getX() const;
  double	getY() const;
  double	getZ() const;
  void		setX(double value);
  void		setY(double value);
  void		setZ(double value);
  void		rotate(Rotation& rotation);
  void		unitarize();

private:
  double	_x;
  double	_y;
  double	_z;
};

#endif
