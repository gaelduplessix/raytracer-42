//
// PhotonMap.hpp for raytracer in /home/olivie_a//rendu/cpp/raytracer-42/src
// 
// Made by samuel olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  Tue May 17 13:36:45 2011 samuel olivier
// Last update Tue May 17 18:24:12 2011 samuel olivier
//

#ifndef _PHOTON_MAP_
#define _PHOTON_MAP_

#include <vector>

#include "Photon.hpp"

using namespace std;

class Raytracer;

class PhotonMap
{
public:
  PhotonMap(const vector<Photon>& map);
  const vector<Photon>&	getMap(void);
  void			setMap(const vector<Photon>& map);
  void			throwRay(Raytracer *rt, const Point& position,
				 int sampling, const Color& currentColor);
  void			fillPhotonMap(Raytracer *rt);

private:
  vector<Photon> _map;
};

#endif
