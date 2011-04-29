//
// CinemaCamera.hpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Fri Apr 29 15:27:11 2011 loick michard
// Last update Fri Apr 29 15:57:41 2011 loick michard
//

#ifndef _CINEMA_CAMERA_HPP_
#define _CINEMA_CAMERA_HPP_

#include "Camera.hpp"
#include "Ray.hpp"

class CinemaCamera : public Camera
{
public:
  CinemaCamera();

  Ray                   getRay(double x, double y) const;
  Ray			getRayWithSampling(double x, double y,
					   double samplingPos) const;
};

#endif
