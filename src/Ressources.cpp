//
// Ressources.cpp for raytracer in /home/olivie_a//rendu/cpp/raytracer-42
// 
// Made by samuel olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  Mon May 23 16:15:05 2011 samuel olivier
// Last update Mon May 23 18:04:49 2011 samuel olivier
//

#include "Ressources.hpp"

Ressources::Ressources(const vector<pair<string, Ressource> >& ressources)
{
  _ressources = ressources;
}

Ressources::Ressources(const Scene* scene, const RenderingConfiguration* conf)
{
  const vector<Object*>&	objects = scene->getObjects();
  int				nbObject = objects.size();
  CubeMap*			cubeMap = conf->getCubeMap();

  for (int i = 0 ; i < nbObject ; i++)
    {
      int			nbPrimitive = objects[i]->_primitives.size();
      for (int j = 0 ; j < nbPrimitive ; j++)
	{
	  const Material&	mat =
	    objects[i]->_primitives[j]->getMaterial();
	  if (mat._texture)
	    _ressources.push_back(make_pair(mat._texture->getName(),
					    *mat._texture));
	  if (mat._limitTexture)
	    _ressources.push_back(make_pair(mat._limitTexture->getName(),
					    *mat._limitTexture));
	  if (mat._heightmap)
	    _ressources.push_back(make_pair(mat._heightmap->getName(),
					    *mat._heightmap));
	}
    }
  if (cubeMap)
    _ressources.push_back(make_pair(cubeMap->getName(),
				    *cubeMap));    
}

void	Ressources::addRessource(const string& name,
				 const Ressource& ressource)
{
  _ressources.push_back(make_pair(name, ressource));
}

const vector<pair<string, Ressource> >&	Ressources::getRessources(void)
{
  return (_ressources);
}
