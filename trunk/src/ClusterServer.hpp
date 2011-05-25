//
// ClusterServer.hpp for raytracer in /home/jochau_g//Desktop/raytracer-42/src
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Mon May 23 13:05:47 2011 gael jochaud-du-plessix
// Last update Wed May 25 14:43:35 2011 gael jochaud-du-plessix
//

#ifndef _CLUSTERSERVER_HPP_
#define _CLUSTERSERVER_HPP_

#include <QObject>
#include <QUrl>
#include <QNetworkAccessManager>
#include <string>

#include "ClusterServerThread.hpp"

using namespace std;

class ClusterServer : public QObject
{
  Q_OBJECT
  
  public:
  static const int	FREE = 0;
  static const int	BUSY = 1;
  
  ClusterServer(string url);
  ~ClusterServer();

public:
  QUrl		getCentralServerUrl(void);
  
private:
  QUrl			_centralServerUrl;
  ClusterServerThread*	_registerServerThread;
  ClusterServerThread*	_clientListenerThread;
};

#endif
