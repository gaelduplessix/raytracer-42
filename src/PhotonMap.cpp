//
// PhotonMap.cpp for raytracer in /home/olivie_a//rendu/cpp/raytracer-42
// 
// Made by samuel olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  Tue May 17 14:33:18 2011 samuel olivier
// Last update Mon May 30 17:37:35 2011 samuel olivier
//

#include "PhotonMap.hpp"
#include "Raytracer.hpp"

PhotonMap::PhotonMap(const vector<Photon>& map) : _map(map)
{

}

PhotonMap::PhotonMap(void)
{

}

void			PhotonMap::fillPhotonMap(Raytracer *rt)
{
  vector<Light*>	lights = rt->getScene()->getLights();
  int			nbLight = lights.size();
  int			sampling = rt->getRenderingConfiguration()
    ->getPhotonMappingSampling();
  Ray			tmpRay;

  for (int i = 0 ; i < nbLight ; i++)
    {
      int j = 0;

      while (j < sampling)
	{
	  lights[i]->getRandomRay(tmpRay);
	  if (throwRay(rt, tmpRay, lights[i]->getColor()))
	    j++;
	}
    }
  for (int pathSize = rt->_refractivePath.size() ; pathSize > 0 ; pathSize--)
    rt->_refractivePath.pop();
}

bool		PhotonMap::throwRay(Raytracer *rt, Ray& ray,
				    const Color& currentColor)
{
  ObjectPrimitive*	nearestObject = NULL;
  double		k = -1;

  if ((nearestObject = rt->getNearestObject(ray, k)) != NULL)
    {
      Photon		photon;
      bool		reflect = false;
      bool		refract = false;
      int		nbPossibilities = 1;
      int		randomValue;

      photon._position = ray._point + k * ray._vector;
      photon._vector = ray._vector;
      photon._color = (currentColor *
      		       nearestObject->getColor(photon._position)) / 255;
      _map.push_back(photon);
      if (rt->getRenderingConfiguration()->isReflectionEnabled() == true
      	  && nearestObject->getMaterial()->getReflectionCoeff() > 0)
      	{
      	  reflect = true;
      	  nbPossibilities++;
      	}
      if (rt->getRenderingConfiguration()->isTransparencyEnabled() == true
      	  && nearestObject->getMaterial()->getTransmissionCoeff() > 0)
      	{
      	  refract = true;
      	  nbPossibilities++;
      	}
      randomValue = rand() % nbPossibilities;
      if (randomValue == 0 || (randomValue == 1 && reflect))
      	{
      	  Ray	newRay(photon._position,
      		       nearestObject->getReflectedVector(photon._position,
      							 photon._vector));
      	  throwRay(rt, newRay, photon._color);
      	}
      if (rt->getRenderingConfiguration()->isTransparencyEnabled() == true
	  && nearestObject->getMaterial()->getTransmissionCoeff() > 0)
	{
	  if (rt->_refractivePath.size() > 0)
	    ray._refractiveIndex =
	      rt->_refractivePath.top()->getMaterial()->getRefractionIndex();
	  else
	    ray._refractiveIndex = 1;
	  Ray	newRay= nearestObject->getRefractedRay(photon._position, ray,
						       rt->_refractivePath);
	  ObjectPrimitive*      tmp = NULL;
	  double                useless = -1;
	  Object*               tmpObject;

	  tmpObject = nearestObject->getObject();
	  if (tmpObject != NULL && tmpObject->isSolid() == true)
	    tmpObject->intersectWithRay(newRay,
					tmp, useless);
	  else
	    nearestObject->intersectWithRay(newRay, tmp, useless);
	  if (tmp != NULL)
	    rt->_refractivePath.push(tmp);
	  else
	    {
	      newRay._vector = ray._vector;
	      newRay._refractiveIndex = ray._refractiveIndex;
	    }
	  throwRay(rt, newRay, photon._color);
	}
      return (true);
    }
  return (false);
}
