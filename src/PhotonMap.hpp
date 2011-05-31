//
// PhotonMap.hpp for raytracer in /home/olivie_a//rendu/cpp/raytracer-42/src
// 
// Made by samuel olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  Tue May 17 13:36:45 2011 samuel olivier
// Last update Tue May 31 23:01:46 2011 loick michard
//

#ifndef _PHOTON_MAP_
#define _PHOTON_MAP_

#include <vector>

#include "Photon.hpp"
#include "Ray.hpp"

using namespace std;

class Raytracer;

typedef struct  PhotonMapNode
{
  int				plane;
  Photon			medianPhoton;
  struct PhotonMapNode		*leftChild;
  struct PhotonMapNode		*rightChild;
}               PhotonMapNode;

class PhotonMap
{
  static const int xPlane = 0;
  static const int yPlane = 1;
  static const int zPlane = 2;

public:
  PhotonMap(const vector<Photon>& map);
  PhotonMap(void);

  vector<Photon>&	getMap(void);
  void			setMap(const vector<Photon>& map);
  bool			throwRay(Raytracer *rt, Ray& ray,
				 const Color& currentColor,
				 bool isAfter);
  void			fillPhotonMap(Raytracer *rt);
  static bool		comparePhotonX(Photon photon1, Photon photon2);
  static bool		comparePhotonY(Photon photon1, Photon photon2);
  static bool		comparePhotonZ(Photon photon1, Photon photon2);
  PhotonMapNode*	generateKdTree(vector<Photon> photons,
				       int _separatePlane);
  void			getNodePhotons(vector<Photon*>& nearest,
				       const Point& intersectPoint,
				       double radius, PhotonMapNode *node);
  void			getNearestPhotons(vector<Photon*>& nearest,
					  const Point& intersectPoint,
					  int n, double radius = 3);
  vector<Photon>	_map;
  PhotonMapNode		*_root;
};

#endif
