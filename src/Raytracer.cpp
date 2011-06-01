//
// Raytracer.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Wed Apr 27 18:02:30 2011 loick michard
// Last update Wed Jun  1 18:25:18 2011 gael jochaud-du-plessix
//

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>

#include "Raytracer.hpp"
#include "Resources.hpp"

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

QByteArray    Raytracer::saveState(void)
{
  QByteArray	data;
  QDataStream	stream(&data, QIODevice::ReadWrite);

  stream << (int)_thread->_raytracedPixels.size();
  for (uint i = 0, l = _thread->_raytracedPixels.size(); i < l; i++)
    {
      stream << (int)_thread->_raytracedPixels[0].size();
      for (uint j = 0, m = _thread->_raytracedPixels[i].size(); j < m; j++)
	stream << (bool)_thread->_raytracedPixels[i][j];
    }
  int size;
  size = _thread->_subThreads.size();
  stream << size;
  for (int i = 0; i < size; i++)
    {
      stream << (double)_thread->_subThreads[i]->_currentProgress;
      stream << (int)_thread->_subThreads[i]->_currentPixel;
      stream << (int)_thread->_subThreads[i]->_currentPixelInLine;
      stream << (int)_thread->_subThreads[i]->_currentLine;
    }
  return (data);
}

void  Raytracer::restoreState(QByteArray& data)
{
  QDataStream	stream(&data, QIODevice::ReadWrite);
  int		size;

  stream >> size;
  _thread->_raytracedPixels.resize(size);
  for (uint i = 0, l = _thread->_raytracedPixels.size(); i < l; i++)
    {
      stream >> size;
      _thread->_raytracedPixels[i].resize(size);
      for (int j = 0; j < size; j++)
	{
	  bool value;
	  stream >> value;
	  _thread->_raytracedPixels[i][j] = value;
	}
    }
  int nbThreads;
  stream >> nbThreads;
  _thread->_subThreads.resize(nbThreads);
  for (int i = 0; i < nbThreads; i++)
    {
      _thread->_subThreads[i] =
	new RaytracerSubThread(_thread,
			       i * 1.0 / nbThreads,
			       (i + 1) * 1.0 / nbThreads);
      stream >> (double&)_thread->_subThreads[i]->_currentProgress;
      stream >> (int&)_thread->_subThreads[i]->_currentPixel;
      stream >> (int&)_thread->_subThreads[i]->_currentPixelInLine;
      stream >> (int&)_thread->_subThreads[i]->_currentLine;
    }
  if (nbThreads > 0)
    _thread->_isRestored = true;
}

bool Raytracer::isPixelRaytraced(int x, int y)
{
  QMutexLocker	lock(&_mutex);
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
  // vector<Object*>	objects = _scene->getObjects();
  // int			nbObject = objects.size();

  // for (int i = 0; i < nbObject ; i++)
  //   {
  //     vector<ObjectPrimitive*>	primitives = objects[i]->getPrimitives();
  //     int			nbPrimitives = primitives.size();

  //     for (int j = 0 ; j < 1 ; j++)
  //     	cout << primitives[j]->getPosition().getX() << " "
  //     	     << primitives[j]->getPosition().getY() << " "
  //     	     << primitives[j]->getPosition().getZ() << "\n";
  //   }
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

double	Raytracer::getProgress(void) const
{
  return (_thread->getProgress());
}

const Camera&		Raytracer::getCurrentCamera(void)
{
  return (_scene->getCamera(_config->getCurrentCamera()));
}

void		Raytracer::renderingLoop(double& progress,
					 RaytracerSubThread* thread)
{
  Point			pixelToRender = getPixelToRender(thread);

  _interface->pixelHasStartedRendering(pixelToRender._x, pixelToRender._y);
  _thread->setRaytracedPixel(pixelToRender._x, pixelToRender._y, true);
  pixelToRender._x += _config->getSection().x();
  pixelToRender._y += _config->getSection().y();

  _otherEyes = false;

  if (_config->_3DEnabled && _config->_3DMode == 2)
    _otherEyes = true;
  Color pixelColor = renderPixel(pixelToRender._x, pixelToRender._y);
  _otherEyes = false;

  if (_config->_3DEnabled && _config->_3DMode == 0)
    {
      _otherEyes = true;
      Color otherColor = renderPixel(pixelToRender._x, pixelToRender._y); 
      _otherEyes = false;
      pixelColor._r = otherColor._r;
    }
  
  progress = (double)(++thread->_currentPixel)
    / (_config->getSection().width() * _config->getSection().height());
  _interface->pixelHasBeenRendered(pixelToRender._x
				   - _config->getSection().x(),
				   pixelToRender._y
				   - _config->getSection().y(), pixelColor);
  _interface->renderingHasProgressed(_thread->getProgress());
}

Point	Raytracer::getPixelToRender(RaytracerSubThread* thread) const
{
  QMutexLocker		lock(&_mutex);
  int			width = _config->getSection().width();
  int			height = _config->getSection().height();

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
		  ray =
		    currentCamera.getRayWithSampling(subx /
						     _config->getWidth(),
						     suby /
						     _config->getHeight(),
						     0, _otherEyes,
						     _config->_eyesSpace);
		  pixelColor += throwRay(ray);
		}
	    }
	  else
	    {
	      ray = currentCamera.getRay(subx / _config->getWidth(),
					 suby / _config->getHeight(),
					 _otherEyes, _config->_eyesSpace);
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
      double maxDist = _config->getAmbientOcclusionMaxDist();
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
	  if (nearestObject != NULL && k < maxDist)
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
  if (diffCoeff <= 0)
    return (throwRay(ray));
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
}

Color		Raytracer::calcAmbiantLight(const Point& intersectPoint)
{
  if (!_config->isPhotonMappingEnabled())
    return (Color(0, 0, 0));
  int			mapSize = _photonMap->_map.size();
  Color			res(0, 0, 0);
  vector<Photon>	nearest;
  double		maxDist = 0;;
  double		aire;
  int			newSize;
  
  _photonMap->getNearestPhotons(nearest,
  				intersectPoint,
  				0.001010101 * mapSize + 30, 2);
  //getNearestPhoton(nearest, mapSize,
  //		   intersectPoint,
  //		   0.001010101 * mapSize + 30);
  newSize = nearest.size();
  for (int i = 0 ; i < newSize ; i++)
    {
      if (nearest[i]._dist > maxDist)
	maxDist = nearest[i]._dist;
      res += nearest[i]._color;
    }
  if (newSize > 0)
    {
      aire = M_PI * maxDist * maxDist;
      res /= aire * mapSize * 0.5;
    }
  return (res);
}

void	Raytracer::deleteKdTree()
{
  delete _kdTree;
}

