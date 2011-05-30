//
// Resource.cpp for raytracer in /home/olivie_a//rendu/cpp/raytracer-42/src
// 
// Made by samuel olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  Fri May 27 14:59:01 2011 samuel olivier
// Last update Mon May 30 21:41:43 2011 samuel olivier
//

#include <iostream>
#include <fstream>

#include "Resource.hpp"

Resource::Resource(const string& pathName,
		     const string& fileContent,
		     const string& newPathName) : _pathName(pathName),
						  _fileContent(fileContent),
						  _newPathName(newPathName)
{

}

Resource::Resource(const string& pathName,
		     const string& newPathName) : _pathName(pathName)
{
  ifstream	file(pathName.c_str(), ios_base::binary);
  file.seekg (0, ios::end);
  int		length = file.tellg();
  file.seekg (0, ios::beg);
  char*		buffer;

  buffer = new char[length];
  file.read(buffer, length);
  _fileContent = string(buffer, length);
  file.close();
  delete buffer;
  _newPathName = newPathName;
}

Resource::Resource(void) : _pathName(""),
			     _fileContent(""),
			     _newPathName("")
{

}

Resource::~Resource()
{

}

const string&	Resource::getNewPathName(void)
{
  return (_newPathName);
}

const string&	Resource::getPathName(void)
{
  return (_pathName);
}

const string&	Resource::getFileContent(void)
{
  return (_fileContent);
}

void	Resource::setNewPathName(const string& newPathName)
{
  _newPathName = newPathName;
}

void	Resource::setPathName(const string& pathName)
{
  _pathName = pathName;
}

void	Resource::setFileContent(const string& fileContent)
{
  _fileContent = fileContent;
}
