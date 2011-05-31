//
// PhotonMap.cpp for raytracer in /home/olivie_a//rendu/cpp/raytracer-42
// 
// Made by samuel olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  Tue May 17 14:33:18 2011 samuel olivier
// Last update Tue May 31 23:17:50 2011 loick michard
//

#include <algorithm>
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
	  if (throwRay(rt, tmpRay, lights[i]->getColor(), false))
	    j++;
	}
    }
  for (int pathSize = rt->_refractivePath.size() ; pathSize > 0 ; pathSize--)
    rt->_refractivePath.pop();
  _root = generateKdTree(_map, xPlane);
}

bool		PhotonMap::throwRay(Raytracer *rt, Ray& ray,
				    const Color& currentColor, bool isAfter)
{
  ObjectPrimitive*	nearestObject = NULL;
  double		k = -1;

  if ((nearestObject = rt->getNearestObject(ray, k)) != NULL)
    {
      Photon		photon;
      bool		reflect = false;
      bool		refract = false;
      int		nbPossibilities = 2;
      int		randomValue;

      photon._position = ray._point + k * ray._vector;
      photon._vector = ray._vector;
      photon._color = (currentColor *
      		       nearestObject->getColor(photon._position)) / 255;
      if (isAfter)
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
      randomValue = rand() % (nbPossibilities + 5);
      if (randomValue == 0)
	return (false);
      if (randomValue == 1 || (randomValue == 2 && reflect))
      	{
      	  Ray	newRay(photon._position,
      		       nearestObject->getReflectedVector(photon._position,
      							 photon._vector));
      	  throwRay(rt, newRay, photon._color, (randomValue == 2 && reflect) ?
		   true : false);
      	}
      if (refract && ((!reflect && randomValue >= 2) || randomValue >= 3) &&
	  rt->getRenderingConfiguration()->isTransparencyEnabled() == true
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
	  throwRay(rt, newRay, photon._color, true);
	}
      return (true);
    }
  return (false);
}

bool		PhotonMap::comparePhotonX(Photon photon1, Photon photon2)
{
  return (photon1._position._x < photon2._position._x);
}

bool            PhotonMap::comparePhotonY(Photon photon1, Photon photon2)
{
  return (photon1._position._y < photon2._position._y);
}

bool            PhotonMap::comparePhotonZ(Photon photon1, Photon photon2)
{
  return (photon1._position._z < photon2._position._z);
}

PhotonMapNode*	PhotonMap::generateKdTree(vector<Photon> photons,
					  int _separatePlane)
{
  if (!photons.size())
    return (NULL);
  _separatePlane %= 3;
  if (_separatePlane == xPlane)
    sort(photons.begin(), photons.end(), PhotonMap::comparePhotonX);
  else if (_separatePlane == yPlane)
    sort(photons.begin(), photons.end(), PhotonMap::comparePhotonY);
 else if (_separatePlane == zPlane)
    sort(photons.begin(), photons.end(), PhotonMap::comparePhotonZ);
  
  PhotonMapNode	*node = new PhotonMapNode();
  node->plane = _separatePlane;
  node->medianPhoton = photons[photons.size() / 2];

  vector<Photon> left;
  vector<Photon> right;
  for (unsigned int i = 0; i < photons.size() / 2; i++)
    left.push_back(photons[i]);
  for (unsigned int i = photons.size() / 2 + 1; i < photons.size(); i++)
    right.push_back(photons[i]);

  node->leftChild = generateKdTree(left, _separatePlane + 1);
  node->rightChild = generateKdTree(right, _separatePlane + 1);
  return (node);
}

void    PhotonMap::getNodePhotons(vector<Photon*>& nearest,
				  const Point& intersectPoint,
				  double radius, PhotonMapNode *node)
{
  if (node)
    {
      node->medianPhoton._dist = 
	(node->medianPhoton._position._x - intersectPoint._x) *
	(node->medianPhoton._position._x - intersectPoint._x) +
	(node->medianPhoton._position._y - intersectPoint._y) *
	(node->medianPhoton._position._y - intersectPoint._y) +
	(node->medianPhoton._position._z - intersectPoint._z) *
	(node->medianPhoton._position._z - intersectPoint._z);
      if (node->medianPhoton._dist < 
	  radius * radius)
	{
	  nearest.push_back(&node->medianPhoton);
	  getNodePhotons(nearest, intersectPoint, 
			 radius, node->leftChild);
	  getNodePhotons(nearest, intersectPoint, 
			 radius, node->rightChild);
	}
      else
	{
	  if ((intersectPoint._x > node->medianPhoton._position._x
	       && node->plane == xPlane) ||
	      (intersectPoint._y > node->medianPhoton._position._y
	       && node->plane == yPlane) ||
	      (intersectPoint._z > node->medianPhoton._position._z
	       && node->plane == zPlane))
	    getNodePhotons(nearest, intersectPoint,
			   radius, node->rightChild);
	  else
	    getNodePhotons(nearest, intersectPoint,
			   radius, node->leftChild);
	}
      node->medianPhoton._dist = sqrt(node->medianPhoton._dist);
    }
}

bool	sortPhoton(Photon* p1, Photon* p2)
{
  return (p1->_dist < p2->_dist);
}

void	PhotonMap::getNearestPhotons(vector<Photon*>& nearest,
				     const Point& intersectPoint,
				     int n, double radius)
{
  getNodePhotons(nearest, intersectPoint, radius, _root);
  sort(nearest.begin(), nearest.end(), sortPhoton);
  if ((int)nearest.size() > n)
    nearest.resize(n);
}
