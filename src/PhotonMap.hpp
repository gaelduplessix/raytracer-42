//
// PhotonMap.hpp for raytracer in /home/olivie_a//rendu/cpp/raytracer-42/src
// 
// Made by samuel olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  Tue May 17 13:36:45 2011 samuel olivier
// Last update Wed May 18 13:14:32 2011 samuel olivier
//

#ifndef _PHOTON_MAP_
#define _PHOTON_MAP_

#include <vector>

#include "Photon.hpp"
#include "Ray.hpp"

using namespace std;

class Raytracer;

class PhotonMap
{
public:
  PhotonMap(const vector<Photon>& map);
  PhotonMap(void);

  const vector<Photon>&	getMap(void);
  void			setMap(const vector<Photon>& map);
  void			throwRay(Raytracer *rt, Ray& ray,
				 const Color& currentColor);
  void			fillPhotonMap(Raytracer *rt);

private:
  vector<Photon> _map;
};

#endif
