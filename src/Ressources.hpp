//
// Ressources.hpp for raytracer in /home/olivie_a//rendu/cpp/raytracer-42/src
// 
// Made by samuel olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  Mon May 23 16:03:25 2011 samuel olivier
// Last update Mon May 23 17:32:20 2011 samuel olivier
//

#ifndef _RESSOURCES_
#define _RESSOURCES_

#include <vector>
#include <utility>
#include <string>

#include "Scene.hpp"
#include "RenderingConfiguration.hpp"
#include "Ressource.hpp"

using namespace std;

class Ressources
{
public:
  Ressources(const vector<pair<string, Ressource> >& ressources);
  Ressources(const Scene* scene, const RenderingConfiguration* conf);

  void	addRessource(const string& name, const Ressource& ressource);
  const vector<pair<string, Ressource> >&	getRessources(void);

private:
  vector<pair<string, Ressource> >	_ressources;
  
};

#endif
