//
// Raytracer.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Wed Apr 27 18:02:30 2011 loick michard
// Last update Mon May  2 16:17:54 2011 gael jochaud-du-plessix
//

#include <stdio.h>
#include <stdio.h>

#include "Raytracer.hpp"

Raytracer::Raytracer()
{
  _thread = new RaytracerThread(this);
  _interface = NULL;
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

const Camera&		Raytracer::getCurrentCamera(void)
{
  return (_scene->getCamera(_config->getCurrentCamera()));
}

#include <iostream>

void		Raytracer::renderingLoop(double& progress)
{
  Point		pixelToRender = getPixelToRender(progress);
  Color		pixelColor = renderPixel(pixelToRender._x, pixelToRender._y);

  progress = (double)++_thread->_currentPixel
    / (_config->getWidth() * _config->getHeight());
  if (_interface)
    _interface->pixelHasBeenRendered(pixelToRender._x,
				     pixelToRender._y,
				     pixelColor);
}

Point			Raytracer::getPixelToRender(double progress) const
{
  int			width = _config->getWidth();
  int			height = _config->getHeight();

  if (_config->getRenderingSamplingMethod() == RSM_LINEAR_HORIZONTAL)
    {
      return (Point(_thread->_currentPixel % width,
		    _thread->_currentPixel / width, 0));
    }
  else if (_config->getRenderingSamplingMethod() == RSM_LINEAR_VERTICAL)
    {
      return (Point(_thread->_currentPixel / height,
		    _thread->_currentPixel % height, 0));
    }
  return (Point(0,0,0));
}

Color			Raytracer::renderPixel(double x, double y)
{
  Ray			ray;
  const Camera&		currentCamera = getCurrentCamera();

  if (_interface)
    _interface->pixelHasStartedRendering(x, y);
  ray = currentCamera.getRay(x / _config->getWidth(),
                             y / _config->getHeight());
  Color pixelColor = throwRay(ray);
  pixelColor.exposure(- _config->getExposure() / Color::MAX_VALUE);
  return (pixelColor);
}

#include <stdio.h>

Color			Raytracer::throwRay(Ray& ray)
{
  double		k;
  ObjectPrimitive*	nearestObject;
  Color			directLight, specularLight;
  Color			reflectedLight, refractedLight;

  // printf("refraction : %d | reflection : %d\n",
  // 	 ray._refractionLevel,
  // 	 ray._reflectionLevel);
  nearestObject = getNearestObject(ray, k);
  if (nearestObject)
    {
      Point	intersectPoint = ray._point + ray._vector * k;
      if (_config->isDirectLighting() || _config->isSpecularLighting())
	calcLightForObject(*nearestObject, intersectPoint,
			   ray._vector, directLight, specularLight);

      if (getRenderingConfiguration()->isReflectionEnabled()
	  && ray._reflectionLevel < 
	  getRenderingConfiguration()->getReflectionMaxDepth())
        {
	  ray._reflectionIntensity *= 
	    nearestObject->getMaterial().getReflectionCoeff();
	  if (ray._reflectionIntensity > EPSILON_REFLECTION)
	    {
	      Ray	reflectedRay(intersectPoint,
				     nearestObject->
				     getReflectedVector(intersectPoint,
						     ray._vector, true));

	      reflectedRay._reflectionLevel = ray._reflectionLevel + 1;
	      reflectedRay._refractionLevel = ray._refractionLevel;
	      reflectedRay._refractionIntensity = ray._refractionIntensity;
	      reflectedRay._reflectionIntensity =
		ray._reflectionIntensity;
	      reflectedLight = throwRay(reflectedRay);
	    }
	}

      if (getRenderingConfiguration()->isTransparencyEnabled()
      	  && ray._refractionLevel <
      	  getRenderingConfiguration()->getTransparencyMaxDepth())
        {
	  if (_refractivePath.size() > 0)
	    ray._refractiveIndex =
	      _refractivePath.top()->getMaterial().getRefractionIndex();
	  else
	    ray._refractiveIndex = 1;
      	  ray._refractionIntensity *=
      	    nearestObject->getMaterial().getRefractionIndex();
      	  if (ray._refractionIntensity > Raytracer::EPSILON_REFRACTION)
      	    {
      	      Ray	refractedRay =
	      	nearestObject->getRefractedRay(intersectPoint, ray,
	      				       _refractivePath);
	      ObjectPrimitive*	tmp = NULL;
	      double		useless = -1;

	      nearestObject->intersectWithRay(refractedRay, tmp, useless);
	      if (tmp != NULL)
	      	_refractivePath.push(tmp);
      	      refractedRay._refractionLevel = ray._refractionLevel + 1;
	      refractedRay._reflectionLevel = ray._reflectionLevel;
	      refractedRay._reflectionIntensity = ray._reflectionIntensity;
      	      refractedRay._refractionIntensity = ray._refractionIntensity;
	      refractedLight = throwRay(refractedRay);
      	    }
      	}
      return ((((((directLight
		   * (1.0 - nearestObject->getMaterial().getSpecularCoeff()))
		  + (specularLight
		     * nearestObject->getMaterial().getSpecularCoeff()))
		 * (1.0 - nearestObject->getMaterial().getReflectionCoeff()))
		+ (reflectedLight
		   * nearestObject->getMaterial().getReflectionCoeff()))
	       * (1.0 - nearestObject->getMaterial().getTransmissionCoeff()))
	      + refractedLight
	      * nearestObject->getMaterial().getTransmissionCoeff());
    }
  else
    return (directLight);
}

void
Raytracer::getIntersectingObjects(Ray ray, vector<t_intersected_object>&
				  intersection) const
{
  const vector<Object*>&		objects(_scene->getObjects());
  int					nbObject(objects.size());

  for (int i = 0 ; i < nbObject ; i++)
    {
      const vector<ObjectPrimitive*>&	primitives=objects[i]->getPrimitives();
      int				nbPrimitive(primitives.size());
      for (int j = 0 ; j < nbPrimitive ; j++)
	primitives[j]->addIntersectionWithRay(ray, intersection);
    }
}

ObjectPrimitive*		Raytracer::getNearestObject(Ray& ray,
							    double& res) const
{
  const vector<Object*>&		objects(_scene->getObjects());
  int					nbObject(objects.size());
  ObjectPrimitive*			primitive = NULL;

  res = -1;
  for (int i = 0 ; i < nbObject ; i++)
    {
      const vector<ObjectPrimitive*>&  
	primitives=objects[i]->getPrimitives();
      int nb_primitive(primitives.size());
      for (int j = 0 ; j < nb_primitive ; j++)
	primitives[j]->intersectWithRay(ray, primitive, res);
    }
  return (primitive);
}

void		Raytracer::calcLightForObject(const ObjectPrimitive& object,
					      const Point& intersectPoint,
					      const Vector& viewRay,
					      Color& directLight,
					      Color& specularLight) const
{
  const vector<Light*>&	lights = _scene->getLights();
  int			nbLights = lights.size();
  Color			objectColor = object.getMaterial().getColor(0, 0);

  for (int i = 0; i < nbLights; i++)
    {
      Color		directLighting;
      Color		specularLighting;

      lights[i]->getLighting(object, intersectPoint, *this, viewRay,
			     directLighting,
			     specularLighting);
      directLight += objectColor * directLighting / 255;
      specularLight += specularLighting;
    }
}
