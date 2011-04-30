//
// Raytracer.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Wed Apr 27 18:02:30 2011 loick michard
// Last update Sat Apr 30 12:45:15 2011 gael jochaud-du-plessix
//

#include "Raytracer.hpp"

Raytracer::Raytracer()
{
  _thread = new RaytracerThread(this);
  _interface = new RenderingInterface();
}

Raytracer::~Raytracer()
{
  if (_thread)
    delete _thread;
}

Raytracer::Raytracer(Scene* scene,
                     RenderingConfiguration* config,
                     RenderingInterface* interface) :
  _scene(scene), _config(config), _interface(interface)
{

}

void
Raytracer::setScene(Scene& scene)
{
  _scene = &scene;
}

void
Raytracer::setRenderingConfiguration(RenderingConfiguration* config)
{
  _config = config;
}

void
Raytracer::setRenderingInterface(RenderingInterface* interface)
{
  _interface = interface;
}

const Scene*
Raytracer::getScene(void) const
{
  return (_scene);
}

const RenderingConfiguration*
Raytracer::getRenderingConfiguration(void) const
{
  return (_config);
}

RenderingInterface*
Raytracer::getRenderingInterface(void) const
{
  return (_interface);
}

void
Raytracer::launchRendering(void)
{
  if (!_scene)
    throw (Raytracer::NO_SCENE_SPECIFIED);
  if (!_config)
    throw (Raytracer::NO_CONFIG_SPECIFIED);
  if (!_interface)
    throw (Raytracer::NO_INTERFACE_SPECIFIED);
  _thread->start();
}

void
Raytracer::stopRendering(void)
{
  _thread->stop();
  _thread->wait();
}

void
Raytracer::pauseRendering(void)
{
  _thread->pause();
  _thread->wait();
}

#include <iostream>

using namespace std;

void		Raytracer::renderingLoop(double& progress)
{
  Point		pixelToRender = getPixelToRender(progress);
  _interface->pixelHasStartedRendering(pixelToRender._x,
				       pixelToRender._y);
  Color		pixelColor(0, 0, 0, 0);
  int		imageWidth = _config->getWidth();
  int		imageHeight = _config->getHeight();
  const Camera&	currentCamera = getCurrentCamera();
  Ray		ray = currentCamera.getRay(pixelToRender._x / imageWidth,
					   pixelToRender._y / imageHeight);

  const vector<t_intersected_object>&	intersections =
    getIntersectingObjects(ray);

  double	k = -1;
  const ObjectPrimitive*	nearestObject =
    getNearestObject(intersections, k);

  if (nearestObject)
    {
      Point	intersectPoint = ray._point + ray._vector * k;
      calcLightForObject(*nearestObject, intersectPoint, pixelColor);
    }
  progress += 1.f / (imageWidth * imageHeight);
  _interface->pixelHasBeenRendered(pixelToRender._x,
				   pixelToRender._y,
				   pixelColor);
  delete &intersections;
}

const Camera&		Raytracer::getCurrentCamera(void)
{
  return (_scene->getCamera(_config->getCurrentCamera()));
}

Point		Raytracer::getPixelToRender(double progress) const
{
  int		width = _config->getWidth();
  int		height = _config->getHeight();
  int		pixelIndex;

  if (_config->getRenderingSamplingMethod() == RSM_LINEAR_HORIZONTAL)
    {
      pixelIndex = progress * width * height;
      return (Point(pixelIndex % width, pixelIndex / width, 0));
    }
  else if (_config->getRenderingSamplingMethod() == RSM_LINEAR_VERTICAL)
    {
      pixelIndex = progress * width * height;
      return (Point(pixelIndex / height, pixelIndex % height, 0));
    }
  return (Point(0,0,0));
}

const vector<t_intersected_object>&
Raytracer::getIntersectingObjects(Ray ray) const
{
  int				nb_object;
  vector<t_intersected_object>	*intersections;
  const vector<Object*>&	objects = _scene->getObjects();
  t_intersected_object		tmp;

  intersections = new vector<t_intersected_object>;
  nb_object = objects.size();
  for (int i = 0 ; i < nb_object ; i++)
    {
      const vector<ObjectPrimitive*>&	primitives =
	objects[i]->getPrimitives();
      int				nb_primitive;
      nb_primitive = primitives.size();
      for (int j = 0 ; j < nb_primitive ; j++)
	{
	  tmp.primitive = primitives[j];
	  tmp.k = tmp.primitive->intersectWithRay(ray);
	  if (tmp.k.size() > 0)
	    intersections->push_back(tmp);
	}
    }
  return (*intersections);
}

const ObjectPrimitive*	Raytracer::
getNearestObject(const vector<t_intersected_object>& intersections,
		 double &res) const
{
  const ObjectPrimitive	*object;
  int			nbObject;

  object = NULL;
  res = -1;
  nbObject = intersections.size();
  if (nbObject > 0)
    {
      for (int i = 0 ; i < nbObject ; i++)
	{
	  int	nbK = intersections[i].k.size();

	  for (int j = 0 ; j < nbK ; j++)
	    if (res < 0 || (intersections[i].k[j] < res
			    && intersections[i].k[j] > EPSILON))
	      {
		res = intersections[i].k[j];
		object = intersections[i].primitive;
	      }
	}
    }
  return (res < 0 ? NULL : object);
}

void	Raytracer::calcLightForObject(const ObjectPrimitive& object,
				      const Point& intersectPoint,
				      Color& color) const
{
  const vector<Light*>&	lights = _scene->getLights();
  int			nbLights = lights.size();
  Color			objectColor = object.getMaterial().getColor(0, 0);

  color = Color(0, 0, 0);
  for (int i = 0; i < nbLights; i++)
    {
      Color	directLighting;
      Color	specularLighting;
      lights[i]->getLighting(object, intersectPoint, *this,
			     directLighting,
			     specularLighting);
      color += objectColor & directLighting;
    }
}
