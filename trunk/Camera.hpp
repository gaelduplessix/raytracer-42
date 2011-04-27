//
// Camera.hpp for raytracer in /home/jochau_g//data/dev/c/raytracer/raytracer-42
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Tue Apr 26 18:54:28 2011 gael jochaud-du-plessix
// Last update Wed Apr 27 22:23:09 2011 samuel olivier
//

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Point.hpp"
#include "Rotation.hpp"
#include "Ray.hpp"

class Camera
{
public:
  Camera();
  ~Camera();

  const Point&		getPosition() const;
  const Rotation&	getRotation() const;
  bool			hasDepthOfField() const;
  double		getFocalLength() const;
  double		getApertureSize() const;
  double		getFocus() const;

  void			setPosition(const Point& position);
  void			setRotation(const Rotation& rotation);  
  void			setFocalLength(double focalLength);  
  void			setApertureSize(double apertureSize);
  void			setFocus(double focus);

  Ray			getRay(double x, double y);
  Ray			getRayWithSampling(double x, double y,
					   double samplingPos);

private:
  Point		_position;
  Rotation	_rotation;
  double	_focalLength;
  bool		_hasDepthOfField;
  double	_apertureSize;
  double	_focus;
};

#endif
