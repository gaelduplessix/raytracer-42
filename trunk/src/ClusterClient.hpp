//
// ClusterClient.hpp for raytracer in /home/jochau_g//Desktop/raytracer-42/src
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Mon May 23 13:12:10 2011 gael jochaud-du-plessix
// Last update Sun May 29 16:07:58 2011 gael jochaud-du-plessix
//

#ifndef _CLUSTERCLIENT_HPP_
#define _CLUSTERCLIENT_HPP_

#include <string>
#include <vector>
#include <QUrl>
#include <QMutexLocker>

#include "RenderingInterface.hpp"
#include "ServersListManager.hpp"

class ServerEntry;

using namespace std;

class ClusterClient
{
public:
  ClusterClient(RenderingInterface* interface, string url, int nbSubdibisions);
  ~ClusterClient();

  RenderingInterface*	getInterface();
  QUrl&			getCentralServerUrl();

  vector <ServerEntry*>	getServers(void);
  ServerEntry*	getServer(QString ip, int port);
  void		addServer(QString ip, int port, int status, int progress);
  void		updateServersList(QString ip, int port, int status,
				  int progress);
  void		removeFromServersList(ServerEntry* entry, bool destroy=false);

protected:
  RenderingInterface*	_interface;
  QUrl			_centralServerUrl;
  int			_nbSubdivisions;
  ServersListManager*	_serversListManager;
  vector <ServerEntry*>	_servers;
  int			_sessionId;
  QMutex		_mutex;
};

#endif
