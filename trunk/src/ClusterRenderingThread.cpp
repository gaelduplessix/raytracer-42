//
// ClusterRenderingThread.cpp for raytracer in /home/jochau_g//Desktop/raytracer-42/src
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Sun May 29 18:12:38 2011 gael jochaud-du-plessix
// Last update Tue May 31 19:54:07 2011 gael jochaud-du-plessix
//

#include "ClusterRenderingThread.hpp"

#include "ClusterClient.hpp"
#include "ServerEntry.hpp"

ClusterRenderingThread::ClusterRenderingThread(ClusterClient* clusterClient):
  _clusterClient(clusterClient), _stopRendering(false)
{  
}

void	ClusterRenderingThread::run(void)
{
  _stopRendering = false;
  while (!_stopRendering)
    {
      ServerEntry*	server = _clusterClient->getFreeServer();
      if (server)
	{
	  QRect section;
	  if (_clusterClient->getSectionToRaytrace(section))
	    server->requestSection(section);
	  else if (_clusterClient->getSectionToRaytrace(section, true))
	    server->requestSection(section);
	}
      usleep(100);
    }
}

void	ClusterRenderingThread::stopRendering(void)
{
  _stopRendering = true;
}
