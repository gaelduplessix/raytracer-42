//
// Ressources.hpp for raytracer in /home/olivie_a//rendu/cpp/raytracer-42/src
// 
// Made by samuel olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  Mon May 23 16:03:25 2011 samuel olivier
// Last update Sat May 28 12:30:32 2011 samuel olivier
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
  Ressources(const vector<Ressource>& ressources, bool inCluster);
  Ressources(const Scene* scene, const RenderingConfiguration* conf,
	     bool inCluster);
  Ressources(const string stringClass, bool inCluster);

public:
  static Ressources*	getInstance(const Scene* scene,
				    const RenderingConfiguration* conf,
				    bool inCluster = false)
  {
    if (!_instance)
      _instance = new Ressources(scene, conf, inCluster);
    return (_instance);
  }
  static Ressources*	getInstance(const vector<Ressource>& ressources,
				    bool inCluster = false)
  {
    if (!_instance)
      _instance = new Ressources(ressources, inCluster);
    return (_instance);
  }
  static Ressources*	getInstance(const string& stringClass,
				    bool inCluster = false)
  {
    if (!_instance)
      {
	_instance = new Ressources(stringClass, inCluster);
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
  static const string&	getNewPathName(const string& previous);

  bool		isInCluster(void);
  void		isInCluster(bool value);

  friend class	boost::serialization::access;
  template	<class Archive>
  void		serialize(Archive& ar, unsigned int version);

  static Ressources*	_instance;
private:
  vector<Ressource>	_ressources;
  string		_tmpRessourceDir;
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
