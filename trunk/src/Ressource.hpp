//
// Ressources.hpp for raytracer in /home/olivie_a//rendu/cpp/raytracer-42/src
// 
// Made by samuel olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  Mon May 23 16:03:25 2011 samuel olivier
// Last update Mon May 23 17:49:52 2011 samuel olivier
//

#ifndef _RESSOURCE_
#define _RESSOURCE_

#include <string>

using namespace std;

class Ressource
{
public:
  const string&	getName(void);
  void	setName(const string& name);

protected:
  string	_name;
};

#endif
