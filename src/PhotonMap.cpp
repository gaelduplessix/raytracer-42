//
// PhotonMap.cpp for raytracer in /home/olivie_a//rendu/cpp/raytracer-42
// 
// Made by samuel olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  Tue May 17 14:33:18 2011 samuel olivier
// Last update Tue May 17 18:25:38 2011 samuel olivier
//

#include "PhotonMap.hpp"
#include "Raytracer.hpp"

PhotonMap::PhotonMap(const vector<Photon>& map) : _map(map)
{

}

void		PhotonMap::fillPhotonMap(Raytracer *rt)
{
  if (rt->getRenderingConfiguration()->isPhotonMappingEnabled())
    {
      vector<Light*>	lights = rt->getScene()->getLights();
      int		nbLight = lights.size();
      int		sampling = rt->getRenderingConfiguration()
	->getPhotonMappingSampling();

      for (int i = 0 ; i < nbLight ; i++)
	throwRay(rt, lights[i]->getPosition(), sampling,
		 lights[i]->getColor());
    }
}

void		PhotonMap::throwRay(Raytracer *rt,
				    const Point& position,
				    int sampling, const Color& currentColor)
{
  Vector		tmpVector;
  Ray			tmpRay(position, Vector(0, 0, 0));
  ObjectPrimitive*	nearestObject;
  double		k;
  Photon		photon;

  for (int i = 0 ; i < sampling ; i++)
    {
      tmpVector.setVector(2 * ((double)rand() / RAND_MAX) - 1,
			  2 * ((double)rand() / RAND_MAX) - 1,
			  2 * ((double)rand() / RAND_MAX) - 1);
      tmpRay.setVector(tmpVector);
      if ((nearestObject = rt->getNearestObject(tmpRay, k)) != NULL)
	{
	  photon._position = position + k * tmpVector;
	  photon._vector = tmpVector;
	  photon._color = (currentColor *
			   nearestObject->getColor(photon._position)) / 255;
	  _map.push_back(photon);
	}
    }
}
