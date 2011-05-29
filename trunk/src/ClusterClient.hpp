//
// ClusterClient.hpp for raytracer in /home/jochau_g//Desktop/raytracer-42/src
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Mon May 23 13:12:10 2011 gael jochaud-du-plessix
// Last update Sun May 29 12:48:51 2011 loick michard
//

#ifndef _CLUSTERCLIENT_HPP_
#define _CLUSTERCLIENT_HPP_

#include <string>
#include <vector>
#include <QUrl>
#include <QMutexLocker>

#include "RenderingInterface.hpp"
#include "ServersListManager.hpp"
#include "ServerEntry.hpp"

using namespace std;

class ClusterClient
{
public:
  ClusterClient(RenderingInterface* interface, string url, int nbSubdibisions);
  ~ClusterClient();

  RenderingInterface*	getInterface();
  QUrl&			getCentralServerUrl();

  ServerEntry*	getServer(QString ip, int port);
  void		addServer(QString ip, int port, int status, int progress);
  void		updateServersList(QString ip, int port, int status,
				  int progress);

  vector <ServerEntry*>	_servers;
protected:
  RenderingInterface*	_interface;
  QUrl			_centralServerUrl;
  int			_nbSubdivisions;
  ServersListManager*	_serversListManager;
  int			_sessionId;
  QMutex		_mutex;
};

#endif
