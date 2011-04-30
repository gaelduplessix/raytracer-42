//
// Raytracer.hpp for raytracer in /home/michar_l//Raytracer
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Tue Apr 26 12:24:26 2011 loick michard
// Last update Sat Apr 30 10:57:58 2011 loick michard
//

#ifndef _RAYTRACER_HPP_
#define _RAYTRACER_HPP_

#define EPSILON 1e-5

#include "Scene.hpp"
#include "RenderingConfiguration.hpp"
#include "RenderingInterface.hpp"
#include "RaytracerThread.hpp"

typedef struct			s_intersected_object
{
  const ObjectPrimitive*        primitive;
  vector<double>                k;
}				t_intersected_object;

class	Raytracer
{
public:
  const static int	NO_SCENE_SPECIFIED = 0;
  const static int	NO_CONFIG_SPECIFIED = 1;
  const static int	NO_INTERFACE_SPECIFIED = 2;

  Raytracer();
  Raytracer(Scene* scene,
	    RenderingConfiguration* config,
	    RenderingInterface* interface);
  ~Raytracer();

  void setScene(Scene& scene);
  void setRenderingConfiguration(RenderingConfiguration* config);
  void setRenderingInterface(RenderingInterface* interface);

  const Scene*			getScene(void) const;
  const RenderingConfiguration*	getRenderingConfiguration(void) const;
  RenderingInterface*	getRenderingInterface(void) const;

  void launchRendering();
  void stopRendering();
  void pauseRendering();

  void		renderingLoop(double& progress);
  const Camera&	getCurrentCamera(void);
  Point		getPixelToRender(double progress) const;

  const vector<t_intersected_object>&
  getIntersectingObjects(Ray ray) const;
  const ObjectPrimitive*
  getNearestObject(const vector<t_intersected_object>&, double& res) const;

  void	calcLightForObject(const ObjectPrimitive& object,
			   const Point& intersectPoint,
			   Color& color) const;

private:
  Scene*			_scene;
  RenderingConfiguration*	_config;
  RenderingInterface*		_interface;
  RaytracerThread*		_thread;
};

#endif
