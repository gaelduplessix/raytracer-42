//
// Ressources.hpp for raytracer in /home/olivie_a//rendu/cpp/raytracer-42/src
// 
// Made by samuel olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  Mon May 23 16:03:25 2011 samuel olivier
// Last update Sat May 28 21:13:30 2011 samuel olivier
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
  Ressources(void);

public:
  static Ressources*	getInstance(void)
  {
    if (!_instance)
      return (new Ressources);
    return (_instance);
  }

  string	toStr(void);

  const vector<Ressource>&	getRessources(void);
  void		setRessources(const vector<Ressource>& ressources);

  void		createRessources(const Scene* scene,
				 const RenderingConfiguration* conf);
  void		createRessources(const string stringClass);

  const string&	getTmpRessourceDir(void);

  void		createRessourcesInTemporaryDir(void);
  static const string&	getNewPathName(const string& previous);

  bool		isInCluster(void);
  void		isInCluster(bool value);

  friend class	boost::serialization::access;
  template	<class Archive>
  void		serialize(Archive& ar, unsigned int version);

private:
  static Ressources*	_instance;
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
