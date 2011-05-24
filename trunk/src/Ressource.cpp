//
// Ressource.cpp for raytracer in /home/olivie_a//rendu/cpp/raytracer-42
// 
// Made by samuel olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  Mon May 23 16:22:27 2011 samuel olivier
// Last update Mon May 23 17:49:23 2011 samuel olivier
//

#include "Ressource.hpp"

const string&	Ressource::getName(void)
{
  return (_name);
}

void		Ressource::setName(const string& name)
{
  _name = name;
}
