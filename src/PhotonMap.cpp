//
// PhotonMap.cpp for raytracer in /home/olivie_a//rendu/cpp/raytracer-42
// 
// Made by samuel olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  Tue May 17 14:33:18 2011 samuel olivier
// Last update Wed May 18 11:21:54 2011 samuel olivier
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
      Ray		tmpRay;

      for (int i = 0 ; i < nbLight ; i++)
	for (int j = 0 ; j < sampling ; j++)
	  {
	    lights[i]->getRandomRay(tmpRay);
	    throwRay(rt, tmpRay, lights[i]->getColor());
	  }
    }
}

void		PhotonMap::throwRay(Raytracer *rt, Ray& ray,
				    const Color& currentColor)
{
  ObjectPrimitive*	nearestObject = NULL;
  double		k = -1;
  Photon		photon;

  if ((nearestObject = rt->getNearestObject(ray, k)) != NULL)
    {
      photon._position = ray._point + k * ray._vector;
      photon._vector = ray._vector;
      photon._color = (currentColor *
		       nearestObject->getColor(photon._position)) / 255;
      _map.push_back(photon);
    }
}
