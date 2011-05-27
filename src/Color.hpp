//
// Camera.hpp for raytracer in /home/jochau_g//data/dev/c/raytracer/raytracer-42
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Tue Apr 26 18:54:28 2011 gael jochaud-du-plessix
// Last update Thu May 26 16:04:33 2011 samuel olivier
//

#ifndef _COLOR_HPP_
#define _COLOR_HPP_

#include <QColor>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class Color
{
public:
  static const int MAX_VALUE = 255;

  Color();
  Color(int r, int g, int b, int a=255);
  explicit Color(int color);
  Color(QRgb color);

  int	getR(void) const;
  int	getG(void) const;
  int	getB(void) const;
  int	getA(void) const;

  void	setR(int r);
  void	setG(int g);
  void	setB(int b);
  void	setA(int a);
  void	setColor(int r, int g, int b, int a);
  void	setColor(int color);

  const Color&	satureTo(int value);
  const Color&	exposure(double value);

  Color&	operator+=(const Color& color);
  Color&	operator-=(const Color& color);
  Color&	operator*=(const Color& color);
  Color&	operator/=(const Color& color);
  Color&	operator%=(const Color& color);
  Color&	operator&=(const Color& color);

  template <class T>
  Color&	operator+=(T value);
  template <class T>
  Color&	operator-=(T value);
  template <class T>
  Color&	operator/=(T value);
  template <class T>
  Color&	operator%=(T value);

  Color&	operator*=(double value);
  Color		operator*(double value);

  friend class          boost::serialization::access;
  template<class Archive>
  void                  serialize(Archive& ar, unsigned int version);

  int	_r;
  int	_g;
  int	_b;
  int	_a;
};

template<class Archive>
void			Color::serialize(Archive& ar, unsigned int version)
{
  version = version;
  ar & _r;
  ar & _g;
  ar & _b;
  ar & _a;
}

Color	operator+(const Color& color1, const Color& color2);
Color	operator-(const Color& color1, const Color& color2);
Color	operator*(const Color& color1, const Color& color2);
Color	operator/(const Color& color1, const Color& color2);
Color	operator%(const Color& color1, const Color& color2);
Color	operator&(const Color& color1, const Color& color2);

template <class T>
Color		operator+(const Color& color1, T value);
template <class T>
Color		operator-(const Color& color1, T value);
template <class T>
Color		operator/(const Color& color1, T value);
template <class T>
Color		operator%(const Color& color1, T value);

template <class T>
Color&		Color::operator+=(T value)
{
  _r += value;
  _g += value;
  _b += value;
  _a += value;
  return (*this);
}

template <class T>
Color&		Color::operator-=(T value)
{
  _r -= value;
  _g -= value;
  _b -= value;
  _a -= value;
  return (*this);
}

template <class T>
Color&		Color::operator/=(T value)
{
  _r /= value;
  _g /= value;
  _b /= value;
  _a /= value;
  return (*this);
}

template <class T>
Color&		Color::operator%=(T value)
{
  _r %= value;
  _g %= value;
  _b %= value;
  _a %= value;
  return (*this);
}

template <class T>
Color		operator+(const Color& color1, T value)
{
  Color		res(color1.getR() + value,
		    color1.getG() + value,
		    color1.getB() + value,
		    color1.getA() + value);
  return (res);
}

template <class T>
Color		operator-(const Color& color1, T value)
{
  Color		res(color1.getR() - value,
		    color1.getG() - value,
		    color1.getB() - value,
		    color1.getA() - value);
  return (res);
}

template <class T>
Color		operator/(const Color& color1, T value)
{
  Color		res(color1.getR() / value,
		    color1.getG() / value,
		    color1.getB() / value,
		    color1.getA() / value);
  return (res);
}

template <class T>
Color		operator%(const Color& color1, T value)
{
  Color		res(color1.getR() % value,
		    color1.getG() % value,
		    color1.getB() % value,
		    color1.getA() % value);
  return (res);
}

#endif
