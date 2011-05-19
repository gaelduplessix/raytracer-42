//
// CinemaCamera.hpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Fri Apr 29 15:27:11 2011 loick michard
// Last update Thu May 19 16:40:39 2011 loick michard
//

#ifndef _CINEMA_CAMERA_HPP_
#define _CINEMA_CAMERA_HPP_

#include "Camera.hpp"
#include "Ray.hpp"

class CinemaCamera : public Camera
{
public:
  CinemaCamera();
  CinemaCamera(Point position, Rotation rotation);
  CinemaCamera(Point position, const Point& target, bool hasTarget);

  Ray                   getRay(double x, double y) const;
  Ray			getRayWithSampling(double x, double y,
					   double samplingPos) const;
};

#endif
