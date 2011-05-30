//
// ClusterClient.cpp for raytracer in /home/jochau_g//Desktop/raytracer-42/src
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Mon May 23 13:12:10 2011 gael jochaud-du-plessix
// Last update Mon May 30 20:59:21 2011 gael jochaud-du-plessix
//

#include <unistd.h>
#include <time.h>
#include <cmath>

#include "ClusterClient.hpp"

#include "ServerEntry.hpp"

ClusterClient::ClusterClient(RenderingInterface* interface,
			     string url, int nbSubdibisions):
  _interface(interface), _centralServerUrl(url.c_str()),
  _nbSubdivisions(nbSubdibisions), _servers(0), _sessionId(-1),
  _imageSections(0), _renderingConfiguration(), _scene(NULL)
{
  srand(time(NULL));
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

int			ClusterClient::getSessionId()
{
  return (_sessionId);
}

RenderingConfiguration&		ClusterClient::getRenderingConfiguration()
{
  return (_renderingConfiguration);
}

Scene*	ClusterClient::getScene()
{
  return (_scene);
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
    server->setProgress(progress);
}

void		ClusterClient::removeFromServersList(ServerEntry* entry,
						     bool destroy)
{
  QMutexLocker	lock(&_mutex);
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

ServerEntry*	ClusterClient::getFreeServer(void)
{
  QMutexLocker	lock(&_mutex);
  for (int i = 0, l = _servers.size(); i < l; i++)
    {
      if (_servers[i]->getStatus() == ServerEntry::WAITING_REQUEST)
	return (_servers[i]);
    }
  return (NULL);
}

void	ClusterClient::launchRendering(RenderingConfiguration* config,
				       Scene* scene)
{
  if (_sessionId == -1)
    launchNewSession(config, scene);
  else
    relaunchSession();
}

void	ClusterClient::launchNewSession(RenderingConfiguration* config,
					Scene* scene)
{
  _sessionId = rand();
  _renderingConfiguration = *config;
  _scene = scene;
  if (_nbSubdivisions <= 0)
    _nbSubdivisions = (int) sqrt(_renderingConfiguration.getWidth());
  if ((_nbSubdivisions * _nbSubdivisions)
      > (_renderingConfiguration.getWidth()
	 * _renderingConfiguration.getHeight()))
    _nbSubdivisions = (int) sqrt(_renderingConfiguration.getWidth()
				 * _renderingConfiguration.getHeight());
  if (_nbSubdivisions <= 1)
    _nbSubdivisions = 1;
  _imageSections.resize(_nbSubdivisions);
  for (int i = 0; i < _nbSubdivisions; i++)
    {
      _imageSections[i].resize(_nbSubdivisions);
      for (int j = 0; j < _nbSubdivisions; j++)
	_imageSections[i][j] = ClusterClient::NOT_RAYTRACED;
    }
  ostringstream idStr;
  idStr << _sessionId;
  _interface->sendMessage(QObject::tr("Début d'une nouvelle session "
				      "de rendu (%1)")
			  .arg(QString(idStr.str().c_str())).toStdString());
  _renderingThread = new ClusterRenderingThread(this);
  _renderingThread->start();
}

void	ClusterClient::relaunchSession(void)
{  
}

bool	ClusterClient::getSectionToRaytrace(QRect& section)
{
  for (int i = 0; i < _nbSubdivisions; i++)
    {
      for (int j = 0; j < _nbSubdivisions; j++)
	{
	  if (_imageSections[i][j] == ClusterClient::NOT_RAYTRACED)
	    {
	      section.setX(_renderingConfiguration.getWidth()
			   * ((double)i / _nbSubdivisions));
	      section.setY(_renderingConfiguration.getHeight()
			   * ((double)j / _nbSubdivisions));
	      section.setWidth(_renderingConfiguration.getWidth()
			       / _nbSubdivisions);
	      section.setHeight(_renderingConfiguration.getHeight()
				/ _nbSubdivisions);
	      _imageSections[i][j] = ClusterClient::RAYTRACING;
	      return (true);
	    }
	}
    }
  return (false);
}
