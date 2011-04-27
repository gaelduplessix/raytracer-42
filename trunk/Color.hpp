//
// Camera.hpp for raytracer in /home/jochau_g//data/dev/c/raytracer/raytracer-42
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Tue Apr 26 18:54:28 2011 gael jochaud-du-plessix
// Last update Tue Apr 26 23:01:59 2011 gael jochaud-du-plessix
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

  void	setR(int r) const;
  void	setG(int g) const;
  void	setB(int b) const;
  void	setB(int a) const;
  void	setColor(int color) const;
  void	setColor(int r, int g, int b, int a) const;

  Color&	operator+=(Color& color);
  Color&	operator-=(Color& color);
  Color&	operator*=(Color& color);
  Color&	operator/=(Color& color);
  Color&	operator%=(Color& color);
  Color&	operator&=(Color& color);

private:
  int	r;
  int	g;
  int	b;
  int	a;
  int	color;
};

Color&	operator+(const Color& color1, const Color& color2);
Color&	operator-(const Color& color1, const Color& color2);
Color&	operator*(const Color& color1, const Color& color2);
Color&	operator/(const Color& color1, const Color& color2);
Color&	operator%(const Color& color1, const Color& color2);
Color&	operator&(const Color& color1, const Color& color2);

#endif
