//
// Camera.hpp for raytracer in /home/jochau_g//data/dev/c/raytracer/raytracer-42
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Tue Apr 26 18:54:28 2011 gael jochaud-du-plessix
// Last update Fri Apr 29 21:31:30 2011 gael jochaud-du-plessix
//

#ifndef _COLOR_HPP_
#define _COLOR_HPP_

class Color
{
public:
  Color();
  Color(int r, int g, int b, int a=255);
  Color(int color);
  ~Color();

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
  Color&	operator*=(T value);
  template <class T>
  Color&	operator/=(T value);
  template <class T>
  Color&	operator%=(T value);
  template <class T>
  Color&	operator&=(T value);

private:
  int	_r;
  int	_g;
  int	_b;
  int	_a;
};

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
Color		operator*(const Color& color1, T value);
template <class T>
Color		operator/(const Color& color1, T value);
template <class T>
Color		operator%(const Color& color1, T value);
template <class T>
Color		operator&(const Color& color1, T value);

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
Color&		Color::operator*=(T value)
{
  _r *= value;
  _g *= value;
  _b *= value;
  _a *= value;
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
Color&		Color::operator&=(T value)
{
  _r &= value;
  _g &= value;
  _b &= value;
  _a &= value;
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
Color		operator*(const Color& color1, T value)
{
  Color		res(color1.getR() * value,
		    color1.getG() * value,
		    color1.getB() * value,
		    color1.getA() * value);
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

template <class T>
Color		operator&(const Color& color1, T value)
{
  Color		res(color1.getR() & value,
		    color1.getG() & value,
		    color1.getB() & value,
		    color1.getA() & value);
  return (res);
}


#endif
