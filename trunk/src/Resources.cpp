//
// Resources.cpp for raytracer in /home/olivie_a//rendu/cpp/raytracer-42
//
// Made by samuel olivier
// Login   <olivie_a@epitech.net>
//
// Started on  Mon May 23 16:15:05 2011 samuel olivier
// Last update Sat Jun  4 21:36:10 2011 loick michard
//

#include <QDir>
#include <QFile>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Resources.hpp"

Resources*     Resources::_instance = NULL;

Resources::Resources(void) : _resources(0), _tmpResourceDir(""),
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

void		Resources::createResources(const string& stringClass)
{
  istringstream	ifs;
  ifs.str(stringClass);
  boost::archive::text_iarchive ia(ifs);
  ia >> *this;
}

void		Resources::createResources(const QByteArray& bytes)
{
  createResources(string(bytes.data(), bytes.size()));
}

void	Resources::createResources(const Scene* scene,
				   const RenderingConfiguration* conf)
{
  while (_resources.size() > 0)
    _resources.pop_back();

  const vector<Material*>&	materials = scene->getMaterials();
  for (unsigned int i = 0; i < materials.size(); i++)
  	{
  	  Material*	mat = materials[i];
  	  if (mat != NULL && mat->_texture != NULL)
	    {
	      if (mat->_texture->_type == 0)
		_resources.push_back(Resource(mat->_texture->_name));
	    }
  	  if (mat != NULL && mat->_limitTexture != NULL)
	    {
	      if (mat->_limitTexture->_type == 0)
		_resources.push_back(Resource(mat->_limitTexture->_name));
	    }
  	  if (mat != NULL && mat->_heightmap != NULL)
	    {
	      if (mat->_heightmap->_type == 0)
		_resources.push_back(Resource(mat->_heightmap->_name));
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
  const vector<QString>&	filenames = scene->getSceneFilenames();
  int				nbFile = filenames.size();
  for (int i = 0 ; i < nbFile ; i++)
    _resources.push_back(Resource(filenames[i].toStdString()));
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

QByteArray	Resources::toByteArray(void)
{
  std::stringstream		ofs;
  boost::archive::text_oarchive oa(ofs);
  oa << *this;
  ofs.seekg (0, ios::end);
  int           length = ofs.tellg();
  ofs.seekg (0, ios::beg);
  char*         buffer;

  buffer = new char[length];
  ofs.read(buffer, length);
  QByteArray	res(buffer, length);
  delete[] buffer;
  return (res);
}

string	Resources::getNewPathName(const string& previous)
{
  if (!_instance || !_instance->isInCluster())
    {
      return (previous);
    }
  vector<Resource>	resources = _instance->getResources();
  int				j = resources.size();

  for (int i = 0 ; i < j ; i++)
    if (resources[i].getPathName() == previous)
      {
	return (_instance->getTmpResourceDir() + "/"
		+ resources[i].getNewPathName());
      }
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
      newName = "raytracer-42-resources_" + tmpRand.str();
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
    {
      if (_resources[i].getNewPathName() != ""
	  && !QFile::remove(QString((getTmpResourceDir() + "/" + _resources[i].getNewPathName()).c_str())))
	cerr << "Could not remove temporary file '" <<
	  _resources[i].getNewPathName() << "'.\n";
    }
}
