//
// ClusterClient.hpp for raytracer in /home/jochau_g//Desktop/raytracer-42/src
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Mon May 23 13:12:10 2011 gael jochaud-du-plessix
// Last update Thu May 26 18:18:35 2011 gael jochaud-du-plessix
//

#ifndef _CLUSTERCLIENT_HPP_
#define _CLUSTERCLIENT_HPP_

#include <string>
#include <vector>
#include <QUrl>

#include "RenderingInterface.hpp"
#include "ServerEntry.hpp"

using namespace std;

class ClusterClient
{
public:
  ClusterClient(RenderingInterface* interface, string url, int nbSubdibisions);

protected:
  RenderingInterface*	_interface;
  QUrl			_centralServerUrl;
  int			_nbSubdivisions;
  vector <ServerEntry*>	_servers;
};

#endif
