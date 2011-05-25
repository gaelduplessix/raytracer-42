//
// Raytracer.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Wed Apr 27 18:02:30 2011 loick michard
// Last update Wed May 25 10:57:50 2011 loick michard
//

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>

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
  _photonMap(photonMap), _scene(scene), _config(config), _interface(interface)
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

bool Raytracer::isPixelRaytraced(int x, int y)
{
  if (_thread->_raytracedPixels.size() > 0 &&
      _thread->_raytracedPixels[0].size() > 0)
    {
      if (x >= 0 && y >= 0
	  && (unsigned int)x < _thread->_raytracedPixels.size()
	  && (unsigned int)y < _thread->_raytracedPixels[0].size())
	return (_thread->_raytracedPixels[x][y]);
    }
  return (false);
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

void		Raytracer::renderingLoop(double& progress,
					 RaytracerSubThread* thread)
{
  Point			pixelToRender = getPixelToRender(thread);
  _thread->setRaytracedPixel(pixelToRender._x, pixelToRender._y, true);
  _interface->pixelHasStartedRendering(pixelToRender._x, pixelToRender._y);
  Color		pixelColor = renderPixel(pixelToRender._x, pixelToRender._y);

  progress = (double)(++thread->_currentPixel)
    / (_config->getWidth() * _config->getHeight());
  _interface->pixelHasBeenRendered(pixelToRender._x, pixelToRender._y,
  				   pixelColor);
  _interface->renderingHasProgressed(_thread->getProgress());
}

Point	Raytracer::getPixelToRender(RaytracerSubThread* thread) const
{
  int			width = _config->getWidth();
  int			height = _config->getHeight();

  if (_config->getRenderingSamplingMethod() == RSM_LINEAR_HORIZONTAL)
    {
      return (Point(thread->_currentPixel % width,
		    thread->_currentPixel / width, 0));
    }
  else if (_config->getRenderingSamplingMethod() == RSM_LINEAR_VERTICAL)
    {
      return (Point(thread->_currentPixel / height,
		    thread->_currentPixel % height, 0));
    }
  else if (_config->getRenderingSamplingMethod() == RSM_UNPIXELISING)
    {
      int pixel = thread->_currentPixel;
      int plus = (10 * pixel) / (width * height);
      pixel = (10 * pixel + plus) % (width * height);
      return (Point(pixel % width,
		    pixel / width));
    }
  else if (_config->getRenderingSamplingMethod() == RSM_RANDOM_HORIZONTAL)
    {
      if (thread->_currentLine == -1
	  || (thread->_currentPixelInLine % width) == width - 1)
	{
	  do
	    thread->_currentLine = rand() % height;
	  while (_thread->isRaytracedPixel(0, thread->_currentLine));
	  thread->_currentPixelInLine = -1;
	}
      thread->_currentPixelInLine++;
      return (Point(thread->_currentPixelInLine, thread->_currentLine));
    }
  else if (_config->getRenderingSamplingMethod() == RSM_RANDOM_VERTICAL)
    {
      if (thread->_currentLine == -1
	  || (thread->_currentPixelInLine % height) == height - 1)
	{
	  do
	    thread->_currentLine = rand() % width;
	  while (_thread->isRaytracedPixel(thread->_currentLine, 0));
	  thread->_currentPixelInLine = -1;
	}
      thread->_currentPixelInLine++;
      return (Point(thread->_currentLine, thread->_currentPixelInLine));
    }
  else if (_config->getRenderingSamplingMethod() == RSM_RANDOM_PIXEL)
    {
      int pixel;
      do
	pixel = rand() % (width * height);
      while (_thread->isRaytracedPixel(pixel % width, pixel / width));
      return (Point(pixel % width,
		    pixel / width, 0));
    }
  return (Point(0,0,0));
}

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
	     * (1.0 - nearestObject->getMaterial()->getSpecularCoeff()))
	    + (specularLight
	       * nearestObject->getMaterial()->getSpecularCoeff()))
	   * (1.0 - nearestObject->getMaterial()->getReflectionCoeff()))
	  + (reflectedLight
	     * nearestObject->getMaterial()->getReflectionCoeff()))
	 * (1.0 - nearestObject->getMaterial()->getTransmissionCoeff()))
	+ refractedLight
	* nearestObject->getMaterial()->getTransmissionCoeff();
      mixedColor += calcDirectLight(ray);
      mixedColor = (ambientOcclusion * mixedColor) / 255;
      mixedColor *= (1 - ambientOcclusionCoeff);
      mixedColor += calcAmbiantLight(intersectPoint);
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
Raytracer::getIntersectingObjects(const Ray& ray, vector<t_intersected_object>&
				  intersection) const
{
  if (_config->isKdTreeEnabled())
    return (_kdTree->getIntersectingObjects(ray, intersection));
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
  if (_config->isKdTreeEnabled())
    return (_kdTree->getNearestObject(ray, res));
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
    = nearestObject->getMaterial()->getDiffusedReflectionCoeff();
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
      nearestObject->getMaterial()->getReflectionCoeff() > 0
      && ray._reflectionLevel <
      _config->getReflectionMaxDepth())
    {
      ray._reflectionIntensity *= 
	nearestObject->getMaterial()->getReflectionCoeff();
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
      nearestObject->getMaterial()->getTransmissionCoeff() >
      Raytracer::EPSILON_REFRACTION && ray._refractionLevel <
      _config->getTransparencyMaxDepth())
    {
      if (_refractivePath.size() > 0)
	ray._refractiveIndex =
	  _refractivePath.top()->getMaterial()->getRefractionIndex();
      else
	ray._refractiveIndex = 1;
      ray._refractionIntensity *=
	nearestObject->getMaterial()->getTransmissionCoeff();
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

void		Raytracer::getNearestPhoton(vector<Photon*>& nearest, int size,
					    const Point& intersectPoint, int n)
{
  double	dist;
  Vector	vector;
  int		newSize = 0;
  int		i = -1;

  while (++i < size)
    {
      vector = intersectPoint - _photonMap->_map[i]._position;
      dist = vector.getNorm();
      int j = 0;
      while (j < newSize && dist > nearest[j]->_dist)
	j++;
      if (j < n)
	{
	  _photonMap->_map[i]._dist = dist;
	  nearest.insert(nearest.begin() + j, &_photonMap->_map[i]);
	  if (newSize < n)
	    newSize++;
	  else
	    nearest.pop_back();
	}
    }
  // printf("%d / %d\n", nearest.size(), i);
}

Color		Raytracer::calcAmbiantLight(const Point& intersectPoint)
{
  if (!_config->isPhotonMappingEnabled())
    return (Color(0, 0, 0));
  int			mapSize = _photonMap->_map.size();
  Color			res(0, 0, 0);
  vector<Photon*>	nearest;
  double		maxDist = 0;;
  double		aire ;
  int			newSize;

  getNearestPhoton(nearest, mapSize, intersectPoint, mapSize / 50);
  newSize = nearest.size();
  for (int i = 0 ; i < newSize ; i++)
    {
      if (nearest[i]->_dist > maxDist)
	maxDist = nearest[i]->_dist;
      // printf("%d => %d %d %d\n", i, res._r, res._g, res._b);
      res += nearest[i]->_color;
    }
  if (newSize > 0)
    {
      aire = M_PI * maxDist * maxDist;
      res /= aire * mapSize;
    }
  // printf("\n");
  // printf("%d %d %d : %f %f\n", res._r, res._g, res._b, aire, maxDist);
  return (res);
}

void	Raytracer::deleteKdTree()
{
  delete _kdTree;
}

// Color		Raytracer::calcAmbiantLight(const Point& intersectPoint)
// {
//   if (!_config->isPhotonMappingEnabled())
//     return (Color(0, 0, 0));
//   int			mapSize = _photonMap->_map.size();
//   Color			res(0, 0, 0);
//   double		dist;
//   Vector		vector;
//   double		nbPhoton = 0;
//   double maxDist = 0.00001;

//   for (int i = 0 ; i < mapSize ; i++)
//     {
//       vector = intersectPoint - _photonMap->_map[i]._position;
//       dist = vector.getNorm();
//       if (dist < 0.2)
// 	{
// 	  if (dist > maxDist)
// 	    maxDist = dist;
// 	  nbPhoton++;
// 	  res += _photonMap->_map[i]._color * (1.0 - ((1.0 / 0.2) * dist));
// 	}
//     }
//   //  if (nbPhoton > 1.0)
//   //  res /= nbPhoton;
//   // res *= 1.0 - (((double)mapSize - nbPhoton) / (double)mapSize);
//   res /= (3.14 * 4) * 5;
//   return (res);
// }
