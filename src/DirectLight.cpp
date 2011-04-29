//
// DirectLight.cpp for raytracer in /home/olivie_a//rendu/cpp/raytracer-42
// 
// Made by samuel olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  Fri Apr 29 11:06:26 2011 samuel olivier
// Last update Fri Apr 29 12:51:29 2011 samuel olivier
//

#include "DirectLight.hpp"

void	DirectLight::getLighting(const Ray& ray,
			       const Point& intersectPoint,
			       const Raytracer& raytracer,
			       Color& directLighting,
			       Color& specularLighting)
{
  Ray	nray;
  Point	npoint;

  nray = ray;
  npoint = intersectPoint;
  directLighting = directLighting;
  specularLighting = specularLighting;
}
