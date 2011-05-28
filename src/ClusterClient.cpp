//
// ClusterClient.cpp for raytracer in /home/jochau_g//Desktop/raytracer-42/src
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Mon May 23 13:12:10 2011 gael jochaud-du-plessix
// Last update Sat May 28 21:48:38 2011 gael jochaud-du-plessix
//

#include "ClusterClient.hpp"

ClusterClient::ClusterClient(RenderingInterface* interface,
			     string url, int nbSubdibisions):
  _interface(interface), _centralServerUrl(url.c_str()),
  _nbSubdivisions(nbSubdibisions), _servers(0), _sessionId(0)
{
  _serversListManager = new ServersListManager(this);
  _serversListManager->start();
}

ClusterClient::~ClusterClient()
{
  if (_serversListManager)
    delete _serversListManager;
}

RenderingInterface*	ClusterClient::getInterface(void)
{
  return (_interface);
}

QUrl&			ClusterClient::getCentralServerUrl(void)
{
  return (_centralServerUrl);
}

ServerEntry*	ClusterClient::getServer(QString ip, int port)
{
  for (int i = 0, l = _servers.size(); i < l; i++)
    {
      if (_servers[i]->getIp() == ip
	  && _servers[i]->getPort() == port)
	return (_servers[i]);
    }
  return (NULL);
}

void	ClusterClient::addServer(QString ip, int port, int status,
				 int progress)
{
  ServerEntry*	server = new ServerEntry(ip, port, status, progress);
  _servers.push_back(server);
}

void		ClusterClient::updateServersList(QString ip, int port,
						 int status, int progress)
{
  QMutexLocker	lock(&_mutex);
  ServerEntry*	server = getServer(ip, port);
  if (server == NULL)
    addServer(ip, port, status, progress);
  else
    {
      server->setStatus(status);
      server->setProgress(progress);
    }
}
