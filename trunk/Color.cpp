//
// Color.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Wed Apr 27 19:00:06 2011 loick michard
// Last update Wed Apr 27 22:45:39 2011 samuel olivier
//

#include "Color.hpp"

Color::Color()
{
  _r = 0;
  _g = 0;
  _b = 0;
  _a = 0;
}

Color::Color(int r, int g, int b, int a)
{
  _r = r;
  _g = g;
  _b = b;
  _a = a;
}

Color::Color(int color)
{
  char	*ptr;

  ptr = (char *)&color;
#ifdef BIG_ENDIAN
  _r = ptr[3];
  _g = ptr[2];
  _b = ptr[1];
  _a = ptr[0];
#else
  _r = ptr[0];
  _g = ptr[1];
  _b = ptr[2];
  _a = ptr[3];
#endif
}

Color::~Color()
{

}

int	Color::getR(void) const
{
  return (_r);
}

int	Color::getG(void) const
{
  return (_g);
}

int	Color::getB(void) const
{
  return (_b);
}

int	Color::getA(void) const
{
  return (_a);
}

void	Color::setR(int r)
{
  _r = r;
}

void	Color::setG(int g)
{
  _g = g;
}

void	Color::setB(int b)
{
  _b = b;
}

void	Color::setA(int a)
{
  _a = a;
}

void	Color::setColor(int color)
{
  char	*ptr;

  ptr = (char *)&color;
#ifdef BIG_ENDIAN
  _r = ptr[3];
  _g = ptr[2];
  _b = ptr[1];
  _a = ptr[0];
#else
  _r = ptr[0];
  _g = ptr[1];
  _b = ptr[2];
  _a = ptr[3];
#endif
}

void	Color::setColor(int r, int g, int b, int a)
{
  _r = r;
  _g = g;
  _b = b;
  _a = a;
}

Color&		Color::operator+=(Color& color)
{
  _r += color.getR();
  _g += color.getG();
  _b += color.getB();
  _a += color.getA();
}

Color&		Color::operator-=(Color& color)
{
  _r -= color.getR();
  _g -= color.getG();
  _b -= color.getB();
  _a -= color.getA();
}

Color&		Color::operator*=(Color& color)
{
  _r *= color.getR();
  _g *= color.getG();
  _b *= color.getB();
  _a *= color.getA();
}

Color&		Color::operator/=(Color& color)
{
  _r /= color.getR();
  _g /= color.getG();
  _b /= color.getB();
  _a /= color.getA();
}

Color&		Color::operator%=(Color& color)
{
  _r %= color.getR();
  _g %= color.getG();
  _b %= color.getB();
  _a %= color.getA();
}

Color&		Color::operator&=(Color& color)
{
  _r &= color.getR();
  _g &= color.getG();
  _b &= color.getB();
  _a &= color.getA();
}

Color		operator+(const Color& color1, const Color& color2)
{
  Color		res(color1.getR() + color2.getR(),
		  color1.getG() + color2.getG(),
		  color1.getB() + color2.getB(),
		  color1.getA() + color2.getA());
  return (res);
}

Color		operator-(const Color& color1, const Color& color2)
{
  Color		res(color1.getR() - color2.getR(),
		  color1.getG() - color2.getG(),
		  color1.getB() - color2.getB(),
		  color1.getA() - color2.getA());
  return (res);
}

Color		operator*(const Color& color1, const Color& color2)
{
  Color		res(color1.getR() * color2.getR(),
		  color1.getG() * color2.getG(),
		  color1.getB() * color2.getB(),
		  color1.getA() * color2.getA());
  return (res);
}

Color		operator/(const Color& color1, const Color& color2)
{
  Color		res(color1.getR() / color2.getR(),
		  color1.getG() / color2.getG(),
		  color1.getB() / color2.getB(),
		  color1.getA() / color2.getA());
  return (res);
}

Color		operator%(const Color& color1, const Color& color2)
{
  Color		res(color1.getR() % color2.getR(),
		  color1.getG() % color2.getG(),
		  color1.getB() % color2.getB(),
		  color1.getA() % color2.getA());
  return (res);
}

Color		operator&(const Color& color1, const Color& color2)
{
  Color		res(color1.getR() & color2.getR(),
		  color1.getG() & color2.getG(),
		  color1.getB() & color2.getB(),
		  color1.getA() & color2.getA());
  return (res);
}
