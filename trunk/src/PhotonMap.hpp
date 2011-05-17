//
// PhotonMap.hpp for raytracer in /home/olivie_a//rendu/cpp/raytracer-42/src
// 
// Made by samuel olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  Tue May 17 13:36:45 2011 samuel olivier
// Last update Tue May 17 14:44:24 2011 samuel olivier
//

#ifndef _PHOTON_MAP_
#define _PHOTON_MAP_

#include <vector>

#include "Photon.hpp"

using namespace std;

class PhotonMap
{
public:
  PhotonMap(const vector<Photon>& map);
  const vector<Photon>&	getMap(void);
  void			setMap(const vector<Photon>& map);

private:
  vector<Photon> _map;
};

#endif
