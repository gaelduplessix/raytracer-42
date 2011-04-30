//
// Camera.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Wed Apr 27 18:47:14 2011 loick michard
// Last update Sat Apr 30 13:12:04 2011 gael jochaud-du-plessix
//

#include "Camera.hpp"

Camera::Camera()
{

}

Camera::Camera(const Point& position, const Rotation& rotation,
	       const double focalLenght, const bool hasDepthOfField,
	       const double apertureSize, const double focus):
  _position(position), _rotation(rotation), _focalLength(focus),
  _hasDepthOfField(hasDepthOfField), _apertureSize(apertureSize),
  _focus(focus)
{

}

Camera::~Camera()
{
  
}

const Point&	Camera::getPosition(void) const
{
  return (_position);
}

const Rotation&	Camera::getRotation(void) const
{
  return (_rotation);
}

double		Camera::getFocalLength(void) const
{
  return (_focalLength);
}

bool		Camera::hasDepthOfField(void) const
{
  return (_hasDepthOfField);
}

double		Camera::getApertureSize(void) const
{
  return (_apertureSize);
}

double		Camera::getFocus(void) const
{
  return (_focus);
}

void		Camera::setPosition(const Point& position)
{
  _position = position;
}

void		Camera::setRotation(const Rotation& rotation)
{
  _rotation = rotation;
}

void		Camera::setFocalLength(double focalLength)
{
  _focalLength = focalLength;
}

void		Camera::setApertureSize(double apertureSize)
{
  _apertureSize = apertureSize;
}

void		Camera::setFocus(double focus)
{
  _focus = focus;
}
