//
// ClusterClient.cpp for raytracer in /home/jochau_g//Desktop/raytracer-42/src
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Mon May 23 13:12:10 2011 gael jochaud-du-plessix
// Last update Sun May 29 16:10:39 2011 gael jochaud-du-plessix
//

#include "ClusterClient.hpp"

#include "ServerEntry.hpp"

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
  for (int i = 0, l = _servers.size(); i < l; i++)
    delete _servers[i];
}

RenderingInterface*	ClusterClient::getInterface(void)
{
  return (_interface);
}

QUrl&			ClusterClient::getCentralServerUrl(void)
{
  return (_centralServerUrl);
}

vector <ServerEntry*>	ClusterClient::getServers(void)
{
  return (_servers);
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
  if (status == ServerEntry::FREE)
    status = ServerEntry::WAITING_REQUEST;
  ServerEntry*	server = new ServerEntry(this, ip, port, status, progress);
  server->openConnection();
  _servers.push_back(server);
}

void		ClusterClient::updateServersList(QString ip, int port,
						 int status, int progress)
{
  QMutexLocker	lock(&_mutex);
  ServerEntry*	server = getServer(ip, port);
  if (server == NULL)
    {
      if (status == ServerEntry::FREE)
	addServer(ip, port, status, progress);
    }
  else
    {
      server->setStatus(status);
      server->setProgress(progress);
    }
}

void		ClusterClient::removeFromServersList(ServerEntry* entry,
						     bool destroy)
{
  for (int i = 0, l = _servers.size(); i < l; i++)
    {
      if (_servers[i] == entry)
	{
	  if (destroy)
	    delete _servers[i];
	  _servers.erase(_servers.begin() + i);
	}
    }
}
