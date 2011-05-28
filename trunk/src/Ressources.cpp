//
// Ressources.cpp for raytracer in /home/olivie_a//rendu/cpp/raytracer-42
// 
// Made by samuel olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  Mon May 23 16:15:05 2011 samuel olivier
// Last update Sat May 28 21:17:55 2011 samuel olivier
//

#include <QDir>
#include <fstream>
#include <sstream>
#include "Ressources.hpp"

Ressources::Ressources(void) : _ressources(), _tmpRessourceDir(""),
			       _inCluster(false)
{

}

const vector<Ressource>&	Ressources::getRessources(void)
{
  return (_ressources);
}

void		Ressources::setRessources(const vector<Ressource>& ressources)
{
  _ressources = ressources;
}

void		Ressources::createRessources(const string stringClass)
{
  istringstream	ifs;

  ifs.str(stringClass);
  boost::archive::text_iarchive ia(ifs);
  ia >> *this;
}

void	Ressources::createRessources(const Scene* scene,
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
  	    _ressources.push_back(Ressource(mat->_texture->getName()));
  	  if (mat->_limitTexture)
  	    _ressources.push_back(Ressource(mat->_limitTexture->getName()));
  	  if (mat->_heightmap)
  	    _ressources.push_back(Ressource(mat->_heightmap->getName()));
  	}
    }
  if (conf->getCubeMap())
    {
      string			cubeMapPath = conf->getCubeMap()->getName();
      _ressources.push_back(Ressource(cubeMapPath + "/posy.jpg"));
      _ressources.push_back(Ressource(cubeMapPath + "/posx.jpg"));
      _ressources.push_back(Ressource(cubeMapPath + "/posz.jpg"));
      _ressources.push_back(Ressource(cubeMapPath + "/negy.jpg"));
      _ressources.push_back(Ressource(cubeMapPath + "/negx.jpg"));
      _ressources.push_back(Ressource(cubeMapPath + "/negz.jpg"));
    }
}

const string&	Ressources::getTmpRessourceDir(void)
{
  if (_tmpRessourceDir.size() == 0)
    _tmpRessourceDir = QDir::tempPath().toStdString();
  return (_tmpRessourceDir);
}

string		Ressources::toStr(void)
{
  std::ostringstream ofs;
  boost::archive::text_oarchive oa(ofs);

  oa << *this;
  return (ofs.str());
  
}

const string&	Ressources::getNewPathName(const string& previous)
{
  if (!_instance || _instance->isInCluster())
    return (previous);
  vector<Ressource>	ressources = _instance->getRessources();
  int				j = ressources.size();

  for (int i = 0 ; i < j ; i++)
    if (ressources[i].getPathName() == previous)
      return (ressources[i].getNewPathName());
  return (previous);
}

void		Ressources::createRessourcesInTemporaryDir(void)
{
  string	newName;
  ofstream	file;
  int		j = _ressources.size();

  getTmpRessourceDir();
  for (int i = 0 ; i < j ; i++)
    {
      ostringstream	tmpRand;
      tmpRand << rand();
      newName = tmpRand.str();
      file.open((_tmpRessourceDir + "/" + newName).c_str());
      file << _ressources[i].getFileContent();
      file.close();
      _ressources[i].setNewPathName(newName);
    }
}

bool		Ressources::isInCluster(void)
{
  return (_inCluster);
}

void		Ressources::isInCluster(bool value)
{
  _inCluster = value;
}
