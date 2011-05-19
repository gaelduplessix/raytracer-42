//
// Camera.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Wed Apr 27 18:47:14 2011 loick michard
// Last update Thu May 19 16:59:57 2011 loick michard
//

#include "Camera.hpp"

Camera::Camera()
{

}

Camera::Camera(const Point& position, const Rotation& rotation,
	       const double focalLenght, const bool hasDepthOfField,
	       const double apertureSize, const double focus):
  _position(position), _rotation(rotation), _focalLength(focalLenght),
  _hasDepthOfField(hasDepthOfField), _apertureSize(apertureSize),
  _focus(focus), _hasTarget(false)
{

}

Camera::Camera(const Point& position, const Point& target,
               const double focalLenght, const bool hasDepthOfField,
               const double apertureSize, const double focus, 
	       bool hasTarget):
  _position(position), _focalLength(focalLenght),
  _hasDepthOfField(hasDepthOfField), _apertureSize(apertureSize),
  _focus(focus), _hasTarget(hasTarget), _target(target)
{
  _target -= _position;
  _target.normalize();
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

string		Camera::getName() const
{
  return (_name);
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
  _hasDepthOfField = true;
  _focus = focus;
}

void		Camera::setName(const string& name)
{
  _name = name;
}

void		Camera::setTarget(const Point& target)
{
  _target = target - _position;
  _hasTarget = true;
  _target.normalize();
}
