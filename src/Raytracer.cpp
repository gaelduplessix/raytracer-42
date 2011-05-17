//
// Raytracer.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Wed Apr 27 18:02:30 2011 loick michard
// Last update Tue May 17 18:08:07 2011 samuel olivier
//

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Raytracer.hpp"

Raytracer::Raytracer()
{
  _thread = new RaytracerThread(this);
  _interface = NULL;
  srand(time(NULL));
}

Raytracer::~Raytracer()
{
  if (_thread)
    delete _thread;
}

Raytracer::Raytracer(Scene* scene,
                     RenderingConfiguration* config,
                     RenderingInterface* interface,
		     PhotonMap* photonMap) :
  _scene(scene), _config(config), _interface(interface), _photonMap(photonMap)
{

}

void
Raytracer::setScene(Scene& scene)
{
  _scene = &scene;
}

void
Raytracer::setPhotonMap(PhotonMap& photonMap)
{
  _photonMap = &photonMap;
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

const PhotonMap*
Raytracer::getPhotonMap(void) const
{
  return (_photonMap);
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
  if (_thread->isLaunched())
    return ;
  if (!_scene)
    throw (Raytracer::NO_SCENE_SPECIFIED);
  if (!_config)
    throw (Raytracer::NO_CONFIG_SPECIFIED);
  if (!_interface)
    throw (Raytracer::NO_INTERFACE_SPECIFIED);
  _thread->start();
  _interface->renderingHasBegun();
}

void
Raytracer::stopRendering(void)
{
  _thread->stop();
  _thread->wait();
  _interface->renderingHasStoped();
}

void
Raytracer::pauseRendering(void)
{
  _thread->pause();
  _thread->wait();
  _interface->renderingHasPaused();
}

const Camera&		Raytracer::getCurrentCamera(void)
{
  return (_scene->getCamera(_config->getCurrentCamera()));
}

void		Raytracer::renderingLoop(double& progress)
{
  Point		pixelToRender = getPixelToRender();
  _interface->pixelHasStartedRendering(pixelToRender._x, pixelToRender._y);
  Color		pixelColor = renderPixel(pixelToRender._x, pixelToRender._y);

  progress = (double)++_thread->_currentPixel
	/ (_config->getWidth() * _config->getHeight());
  _interface->pixelHasBeenRendered(pixelToRender._x, pixelToRender._y,
				   pixelColor);
  _interface->renderingHasProgressed(progress);
}

Point			Raytracer::getPixelToRender(void) const
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

#include <stdio.h>

Color			Raytracer::renderPixel(double x, double y)
{
  Ray			ray;
  double		subx, suby;
  int			antialiasing = _config->getAntialiasing();
  int			samplingDepth = 
    (_config->isFieldDepthEnabled()) ? _config->getFieldDepthSampling() : 1;
  const Camera&		currentCamera = getCurrentCamera();
  Color			pixelColor;
  
  if (_interface)
    _interface->pixelHasStartedRendering(x, y);
  for (int i = 0; i < antialiasing; ++i)
    {
      subx = x + (double)i / antialiasing;
      for (int j = 0; j < antialiasing; ++j)
	{
	  suby = y + (double)j / antialiasing;
	  if (samplingDepth > 1)
	    {
	      for (int k = 0; k < samplingDepth; k++)
		{
		  ray = currentCamera.getRayWithSampling(subx /
							 _config->getWidth(),
							 suby / 
							 _config->getHeight(),
							 0);
		  pixelColor += throwRay(ray);
		}
	    }
	  else
	    {
	      ray = currentCamera.getRay(subx / _config->getWidth(),
					 suby / _config->getHeight());
	      pixelColor += throwRay(ray);
	    }
	}
    }
  if (antialiasing > 0)
    pixelColor /= antialiasing * antialiasing * samplingDepth;
  pixelColor.exposure(- _config->getExposure() / Color::MAX_VALUE);
  return (pixelColor);
}

Color			Raytracer::throwRay(Ray& ray)
{
  double		k;
  ObjectPrimitive*	nearestObject;

  nearestObject = getNearestObject(ray, k);
  if (nearestObject)
    {
      Color	diffuseLight, specularLight;
      Point	intersectPoint = ray._point + ray._vector * k;
      if (_config->isDirectLighting() || _config->isSpecularLighting())
	calcLightForObject(*nearestObject, intersectPoint,
			   ray._vector, diffuseLight, specularLight);
      Color	reflectedLight = calcReflectedLight(nearestObject,
						    intersectPoint,
						    ray);
      Color	refractedLight = calcTransmetedLight(nearestObject,
						     intersectPoint,
						     ray);
      double	ambientOcclusionCoeff = 0;
      Color	ambientOcclusion = calcAmbiantOcclusion(nearestObject,
							intersectPoint,
							ray,
							ambientOcclusionCoeff);

      Color	mixedColor =
	(((((diffuseLight
	     * (1.0 - nearestObject->getMaterial().getSpecularCoeff()))
	    + (specularLight
	       * nearestObject->getMaterial().getSpecularCoeff()))
	   * (1.0 - nearestObject->getMaterial().getReflectionCoeff()))
	  + (reflectedLight
	     * nearestObject->getMaterial().getReflectionCoeff()))
	 * (1.0 - nearestObject->getMaterial().getTransmissionCoeff()))
	+ refractedLight
	* nearestObject->getMaterial().getTransmissionCoeff();
      mixedColor += calcDirectLight(ray);
      mixedColor = (ambientOcclusion * mixedColor) / 255;
      mixedColor *= (1 - ambientOcclusionCoeff);
      if (_config->isAdditiveAmbiantLighting())
	mixedColor += _config->getAdditiveAmbiantLighting();
      return (mixedColor);
    }
  else if (_config->getCubeMap() != NULL)
    return (_config->getCubeMap()->getMapColor(ray._vector)
	    + calcDirectLight(ray));
  else
    return (_config->getBackgroundColor() + calcDirectLight(ray));
}

void
Raytracer::getIntersectingObjects(const Ray ray, vector<t_intersected_object>&
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
	primitives = objects[i]->getPrimitives();
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
  Color			objectColor = object.getColor(intersectPoint);

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

#include <stdio.h>

Color	Raytracer::calcAmbiantOcclusion(const ObjectPrimitive* object,
					const Point& intersectPoint,
					Ray& ray, double& coeff)
{
  if (_config->isAmbientOcclusionEnabled() == false)
    return (Color(255, 255, 255));
  else
    {
      int			i;
      Vector			newV;
      Color			res;
      int			sampling
	= _config->getAmbientOcclusionSampling();
      Vector			normal
	= object->getNormal(intersectPoint, ray._vector) * -1;
      ObjectPrimitive*		nearestObject;
      double			k;

      coeff = 0;
      i = 0;
      res = 0;
      while (i < sampling)
	{
	  do
	    {
	      newV.setVector(2 * ((double)rand() / RAND_MAX) - 1,
			     2 * ((double)rand() / RAND_MAX) - 1,
			     2 * ((double)rand() / RAND_MAX) - 1);
	    } while (newV * normal < 0);
	  Ray	newRay(intersectPoint, newV);

	  nearestObject = getNearestObject(newRay, k);
	  if (nearestObject != NULL && k < 7)
	      coeff = coeff + 1;
	  res += (nearestObject == NULL) ? Color(255, 255, 255) :
	    nearestObject->getColor(intersectPoint + newV * k);
	  i++;
	}
      res /= sampling;
      coeff /= sampling;
      return (res);
    }
}

Color	Raytracer::calcDiffusedReflection(Ray& ray,
					  const ObjectPrimitive* nearestObject)
{
  if (!_config->isReflectionDiffused())
    return (throwRay(ray));
  double	diffCoeff
    = nearestObject->getMaterial().getDiffusedReflectionCoeff();
  Vector	newV1(ray._vector._z, ray._vector._y, -ray._vector._x);
  Vector	newV2 = newV1;
  newV2 *= ray._vector;
  Color		res;
  int		sampling = _config->getReflectionDiffusedSampling();
  int		i = 0;

  while (i < sampling && diffCoeff > 0)
    {
      double	xoffs, yoffs;
      Vector	newV;
      do
	{
	  xoffs = (((double)rand() / RAND_MAX)) * diffCoeff;
	  yoffs = (((double)rand() / RAND_MAX)) * diffCoeff;
	}
      while ((xoffs * xoffs + yoffs * yoffs) > (diffCoeff * diffCoeff));
      newV = ray._vector + newV1 * xoffs + newV2 * yoffs;
      newV.normalize();
      Ray	newRay(ray._point, newV);
      newRay._reflectionLevel = _config->getReflectionMaxDepth();
      newRay._reflectionIntensity = ray._reflectionIntensity;
      newRay._refractionLevel = ray._refractionLevel;
      newRay._refractionIntensity = ray._refractionIntensity;
      res += throwRay(newRay);
      i++;
    }
  if (diffCoeff > 0 && sampling > 1)
    res /= sampling;
  return (res);
}

Color	Raytracer::calcReflectedLight(const ObjectPrimitive* nearestObject,
				      const Point& intersectPoint,
				      Ray& ray)
{
  if (_config->isReflectionEnabled() &&
      nearestObject->getMaterial().getReflectionCoeff() > 0
      && ray._reflectionLevel <
      _config->getReflectionMaxDepth())
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
	  reflectedRay._reflectionIntensity = ray._reflectionIntensity;
	  reflectedRay._refractionLevel = ray._refractionLevel;
	  reflectedRay._refractionIntensity = ray._refractionIntensity;
	  return (calcDiffusedReflection(reflectedRay, nearestObject));
	}
    }
  return (Color());
}

Color	Raytracer::calcTransmetedLight(const ObjectPrimitive* nearestObject,
				       const Point& intersectPoint,
				       Ray& ray)
{
  if (_config->isTransparencyEnabled() &&
      nearestObject->getMaterial().getTransmissionCoeff() >
      Raytracer::EPSILON_REFRACTION && ray._refractionLevel <
      _config->getTransparencyMaxDepth())
    {
      if (_refractivePath.size() > 0)
	ray._refractiveIndex =
	  _refractivePath.top()->getMaterial().getRefractionIndex();
      else
	ray._refractiveIndex = 1;
      ray._refractionIntensity *=
	nearestObject->getMaterial().getTransmissionCoeff();
      if (ray._refractionIntensity > Raytracer::EPSILON_REFRACTION)
	{
	  Ray	refractedRay =
	    nearestObject->getRefractedRay(intersectPoint, ray,
					   _refractivePath);
	  ObjectPrimitive*	tmp = NULL;
	  double		useless = -1;
	  Object*		tmpObject;

	  tmpObject = nearestObject->getObject();
	  if (tmpObject != NULL && tmpObject->isSolid() == true)
	    tmpObject->intersectWithRay(refractedRay,
					tmp, useless);
	  else
	    nearestObject->intersectWithRay(refractedRay, tmp, useless);
	  if (tmp != NULL)
	    _refractivePath.push(tmp);
	  else
	    {
	      refractedRay._vector = ray._vector;
	      refractedRay._refractiveIndex = ray._refractiveIndex; 
	    }
	  refractedRay._refractionLevel = ray._refractionLevel + 1;
	  refractedRay._reflectionLevel = ray._reflectionLevel;
	  refractedRay._reflectionIntensity = ray._reflectionIntensity;
	  refractedRay._refractionIntensity = ray._refractionIntensity;
	  return (throwRay(refractedRay));
	}
    }
  return (Color());
}

Color		Raytracer::calcDirectLight(Ray& ray)
{
  Color		directLight;

  if (_config->isDirectLighting())
    {
      const vector<Light*>&	lights = _scene->getLights();
      int			nbLights = lights.size();

      for (int i = 0; i < nbLights; i++)
	directLight += lights[i]->getDirectLighting(*this, ray);
      return (directLight * _config->getDirectLightingCoeff());
    }
  return (directLight);
}
