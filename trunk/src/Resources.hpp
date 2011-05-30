//
// Resources.hpp for raytracer in /home/olivie_a//rendu/cpp/raytracer-42/src
// 
// Made by samuel olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  Mon May 23 16:03:25 2011 samuel olivier
// Last update Mon May 30 19:31:25 2011 gael jochaud-du-plessix
//

#ifndef _RESOURCES_
#define _RESOURCES_

#include <vector>
#include <utility>
#include <string>
#include <QImage>
#include <boost/serialization/vector.hpp>

#include "Scene.hpp"
#include "RenderingConfiguration.hpp"
#include "Resource.hpp"

using namespace std;

class Resources
{
private:
  Resources(void);

public:
  string	toStr(void);

  const vector<Resource>&	getResources(void);
  void		setResources(const vector<Resource>& resources);

  void		createResources(const Scene* scene,
				 const RenderingConfiguration* conf);
  void		createResources(const string stringClass);

  const string&	getTmpResourceDir(void);

  void		createResourcesInTemporaryDir(void);
  static const string&	getNewPathName(const string& previous);

  bool		isInCluster(void);
  void		isInCluster(bool value);

  friend class	boost::serialization::access;
  template	<class Archive>
  void		serialize(Archive& ar, unsigned int version);

private:
  static Resources*	_instance;
  vector<Resource>	_resources;
  string		_tmpResourceDir;
  bool			_inCluster;

public:
  static Resources*	getInstance(void)
  {
    if (!_instance)
      _instance = new Resources();
    return (_instance);
  }
};

template	<class Archive>
void		Resources::serialize(Archive& ar, unsigned int version)
{
  version = version;
  ar & _resources;
}

#endif
