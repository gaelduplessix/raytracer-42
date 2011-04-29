//
// DirectLighting.hpp for raytracer in /home/olivie_a//rendu/cpp/raytracer-42
// 
// Made by samuel olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  Fri Apr 29 10:53:30 2011 samuel olivier
// Last update Fri Apr 29 11:06:10 2011 samuel olivier
//

#ifndef _DIRECT_LIGHT_HPP_
#define _DIRECT_LIGHT_HPP_

#include "Light.hpp"

class DirectLight : public Light
{
  void	getLighting(const Ray& ray,
		    const Point& intersectPoint,
		    const RenderingConfiguration& config,
		    Color& directLighting,
		    Color& specularLighting);
};

#endif
