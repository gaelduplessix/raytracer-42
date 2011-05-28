//
// Ressources.hpp for raytracer in /home/olivie_a//rendu/cpp/raytracer-42/src
// 
// Made by samuel olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  Mon May 23 16:03:25 2011 samuel olivier
// Last update Sat May 28 10:53:12 2011 samuel olivier
//

#ifndef _RESSOURCES_
#define _RESSOURCES_

#include <vector>
#include <utility>
#include <string>
#include <QImage>
#include <boost/serialization/vector.hpp>

#include "Scene.hpp"
#include "RenderingConfiguration.hpp"
#include "Ressource.hpp"

using namespace std;

class Ressources
{
private:
  Ressources(const vector<Ressource>& ressources);
  Ressources(const Scene* scene, const RenderingConfiguration* conf);
  Ressources(const string stringClass);

public:
  static Ressources*	getInstance(const Scene* scene,
				    const RenderingConfiguration* conf)
  {
    if (!_instance)
      _instance = new Ressources(scene, conf);
    return (_instance);
  }
  static Ressources*	getInstance(const vector<Ressource>& ressources)
  {
    if (!_instance)
      _instance = new Ressources(ressources);
    return (_instance);
  }
  static Ressources*	getInstance(const string& stringClass)
  {
    if (!_instance)
      {
	_instance = new Ressources(stringClass);
      }
    return (_instance);
  }
  static Ressources*	getInstance(void)
  {
    return (_instance);
  }
  string	toStr(void);
  void		addRessource(const Ressource& ressource);
  const vector<Ressource>&	getRessources(void);

  void		createRessources(const Scene* scene,
				 const RenderingConfiguration* conf);

  const string&	getTmpRessourceDir(void);

  void		createRessourcesInTemporaryDir(void);
  const string&	getNewPathName(const string& previous);

  bool		isInCluster(void);
  void		isInCluster(bool value);

  friend class	boost::serialization::access;
  template	<class Archive>
  void		serialize(Archive& ar, unsigned int version);

private:
  vector<Ressource>	_ressources;
  string		_tmpRessourceDir;
  static Ressources*	_instance;
  bool			_inCluster;
};

// Ressources*	Ressources::_instance = NULL;

template	<class Archive>
void		Ressources::serialize(Archive& ar, unsigned int version)
{
  version = version;
  ar & _ressources;
}

#endif
