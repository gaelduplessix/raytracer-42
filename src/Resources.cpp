//
// Resources.cpp for raytracer in /home/olivie_a//rendu/cpp/raytracer-42
// 
// Made by samuel olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  Mon May 23 16:15:05 2011 samuel olivier
// Last update Mon May 30 21:42:26 2011 samuel olivier
//

#include <QDir>
#include <QFile>
#include <fstream>
#include <sstream>
#include "Resources.hpp"

Resources*     Resources::_instance = NULL;

Resources::Resources(void) : _resources(), _tmpResourceDir(""),
			       _inCluster(false)
{

}

const vector<Resource>&	Resources::getResources(void)
{
  return (_resources);
}

void		Resources::setResources(const vector<Resource>& resources)
{
  _resources = resources;
}

void		Resources::createResources(const string stringClass)
{
  istringstream	ifs;

  ifs.str(stringClass);
  boost::archive::text_iarchive ia(ifs);
  ia >> *this;
}

void	Resources::createResources(const Scene* scene,
				     const RenderingConfiguration* conf)
{
  const vector<Object*>&	objects = scene->getObjects();
  int				nbObject = objects.size();

  for (int i = 0 ; i < nbObject ; i++)
    {
      int			nbPrimitive = objects[i]->_primitives.size();
      for (int j = 0 ; j < nbPrimitive ; j++)
  	{
  	  Material*	mat =
  	    objects[i]->_primitives[j]->getMaterial();
  	  if (mat->_texture)
  	    _resources.push_back(Resource(mat->_texture->getName()));
  	  if (mat->_limitTexture)
  	    _resources.push_back(Resource(mat->_limitTexture->getName()));
  	  if (mat->_heightmap)
  	    _resources.push_back(Resource(mat->_heightmap->getName()));
  	}
    }
  if (conf->getCubeMap())
    {
      string			cubeMapPath = conf->getCubeMap()->getName();
      _resources.push_back(Resource(cubeMapPath + "/posy.jpg"));
      _resources.push_back(Resource(cubeMapPath + "/posx.jpg"));
      _resources.push_back(Resource(cubeMapPath + "/posz.jpg"));
      _resources.push_back(Resource(cubeMapPath + "/negy.jpg"));
      _resources.push_back(Resource(cubeMapPath + "/negx.jpg"));
      _resources.push_back(Resource(cubeMapPath + "/negz.jpg"));
    }
}

const string&	Resources::getTmpResourceDir(void)
{
  if (_tmpResourceDir.size() == 0)
    _tmpResourceDir = QDir::tempPath().toStdString();
  return (_tmpResourceDir);
}

string		Resources::toStr(void)
{
  std::ostringstream ofs;
  boost::archive::text_oarchive oa(ofs);

  oa << *this;
  return (ofs.str());
  
}

const string&	Resources::getNewPathName(const string& previous)
{
  if (!_instance || _instance->isInCluster())
    return (previous);
  vector<Resource>	resources = _instance->getResources();
  int				j = resources.size();

  for (int i = 0 ; i < j ; i++)
    if (resources[i].getPathName() == previous)
      return (resources[i].getNewPathName());
  return (previous);
}

void		Resources::createResourcesInTemporaryDir(void)
{
  string	newName;
  ofstream	file;
  int		j = _resources.size();

  getTmpResourceDir();
  for (int i = 0 ; i < j ; i++)
    {
      ostringstream	tmpRand;
      tmpRand << rand();
      newName = tmpRand.str();
      file.open((_tmpResourceDir + "/" + newName).c_str());
      file << _resources[i].getFileContent();
      file.close();
      _resources[i].setNewPathName(newName);
    }
}

bool		Resources::isInCluster(void)
{
  return (_inCluster);
}

void		Resources::isInCluster(bool value)
{
  _inCluster = value;
}

void		Resources::removeResourcesFiles(void)
{
  int		l = _resources.size();

  for (int i = 0 ; i < l ; i++)
    if (!QFile::remove(QString(_resources[i].getNewPathName().c_str())))
      cerr << "Could not remove temporary file '" <<
	_resources[i].getNewPathName() << "'.\n";
}
