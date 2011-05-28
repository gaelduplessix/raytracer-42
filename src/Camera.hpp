//
// Camera.hpp for raytracer in /home/jochau_g//data/dev/c/raytracer/raytracer-42
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Tue Apr 26 18:54:28 2011 gael jochaud-du-plessix
// Last update Sat May 28 10:01:03 2011 loick michard
//

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <string>
#include "Point.hpp"
#include "Rotation.hpp"
#include "Ray.hpp"

using namespace std;

class Camera
{
public:
  Camera();
  Camera(const Point& position, const Rotation& rotation,
		 const double focalLenght, const bool hasDepthOfField,
		 const double apertureSize, const double focus);
  Camera(const Point& position, const Point& target,
	 const double focalLenght, const bool hasDepthOfField,
	 const double apertureSize, const double focus, bool hasTarget);
  ~Camera();

  const Point&		getPosition(void) const;
  const Rotation&	getRotation(void) const;
  bool			hasDepthOfField(void) const;
  double		getFocalLength(void) const;
  double		getApertureSize(void) const;
  double		getFocus(void) const;
  string		getName() const;

  void			setPosition(const Point& position);
  void			setRotation(const Rotation& rotation);  
  void			setFocalLength(double focalLength);  
  void			setApertureSize(double apertureSize);
  void			setFocus(double focus);
  void			setTarget(const Point &taget);
  void			setName(const string& name);

  void			updateTarget();
  virtual Ray			getRay(double x, double y,
				       bool other, double space) const = 0;
  virtual Ray			
  getRayWithSampling(double x, double y,
		     double samplingPos, 
		     bool other, double space) const = 0;

  double        _width;
  double        _height;
protected:
  string	_name;
  Point		_position;
  Rotation	_rotation;
  double	_focalLength;
  bool		_hasDepthOfField;
  double	_apertureSize;
  double	_focus;
  bool		_hasTarget;
  Vector	_target;
  Vector	_realTarget;
  Vector	_vectorSpace;
};

#endif
