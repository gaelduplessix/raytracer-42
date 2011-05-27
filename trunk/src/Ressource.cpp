//
// Ressource.cpp for raytracer in /home/olivie_a//rendu/cpp/raytracer-42/src
// 
// Made by samuel olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  Fri May 27 14:59:01 2011 samuel olivier
// Last update Fri May 27 15:18:25 2011 samuel olivier
//

#include <iostream>
#include <fstream>

#include "Ressource.hpp"

Ressource::Ressource(const string& pathName,
		     const string& fileContent,
		     const string& newPathName) : _pathName(pathName),
						  _fileContent(fileContent),
						  _newPathName(newPathName)
{

}

Ressource::Ressource(const string& pathName,
		     const string& newPathName) : _pathName(pathName)
{
  ifstream	file(pathName.c_str(), ios_base::binary);
  file >> _fileContent;
  file.close();
  _newPathName = newPathName;
}

Ressource::Ressource(void) : _pathName(""),
			     _fileContent(""),
			     _newPathName("")
{

}

Ressource::~Ressource()
{

}

const string&	Ressource::getNewPathName(void)
{
  return (_newPathName);
}

const string&	Ressource::getPathName(void)
{
  return (_pathName);
}

const string&	Ressource::getFileContent(void)
{
  return (_fileContent);
}

void	Ressource::setNewPathName(const string& newPathName)
{
  _newPathName = newPathName;
}

void	Ressource::setPathName(const string& pathName)
{
  _pathName = pathName;
}

void	Ressource::setFileContent(const string& fileContent)
{
  _fileContent = fileContent;
}


