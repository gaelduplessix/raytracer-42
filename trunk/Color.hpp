//
// Camera.hpp for raytracer in /home/jochau_g//data/dev/c/raytracer/raytracer-42
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Tue Apr 26 18:54:28 2011 gael jochaud-du-plessix
// Last update Wed Apr 27 15:22:45 2011 loick michard
//

#ifndef _COLOR_HPP_
#define _COLOR_HPP_

class Color
{
public:
  Color();
  ~Color();

  int	getR() const;
  int	getG() const;
  int	getB() const;
  int	getA() const;
  int	getHexaValue() const;

  void	setR(int r);
  void	setG(int g);
  void	setB(int b);
  void	setA(int a);
  void	setColor(int color);
  void	setColor(int r, int g, int b, int a);

  Color&	operator+=(Color& color);
  Color&	operator-=(Color& color);
  Color&	operator*=(Color& color);
  Color&	operator/=(Color& color);
  Color&	operator%=(Color& color);
  Color&	operator&=(Color& color);

private:
  int	_r;
  int	_g;
  int	_b;
  int	_a;
  int	_color;
};

Color&	operator+(const Color& color1, const Color& color2);
Color&	operator-(const Color& color1, const Color& color2);
Color&	operator*(const Color& color1, const Color& color2);
Color&	operator/(const Color& color1, const Color& color2);
Color&	operator%(const Color& color1, const Color& color2);
Color&	operator&(const Color& color1, const Color& color2);

#endif
