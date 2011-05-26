//
// ClusterClient.cpp for raytracer in /home/jochau_g//Desktop/raytracer-42/src
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Mon May 23 13:12:10 2011 gael jochaud-du-plessix
// Last update Thu May 26 17:51:46 2011 gael jochaud-du-plessix
//

#include "ClusterClient.hpp"

ClusterClient::ClusterClient(RenderingInterface* interface,
			     string url, int nbSubdibisions):
  _interface(interface), _centralServerUrl(url.c_str()),
  _nbSubdivisions(nbSubdibisions)
{
  
}
