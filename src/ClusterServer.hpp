//
// ClusterServer.hpp for raytracer in /home/jochau_g//Desktop/raytracer-42/src
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Mon May 23 13:05:47 2011 gael jochaud-du-plessix
// Last update Wed May 25 21:30:09 2011 gael jochaud-du-plessix
//

#ifndef _CLUSTERSERVER_HPP_
#define _CLUSTERSERVER_HPP_

#include <QObject>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QMutex>
#include <QMutexLocker>
#include <QWaitCondition>
#include <string>

#include "RenderingInterface.hpp"
#include "ClusterServerThread.hpp"

using namespace std;

class ClusterServer : public QObject
{
  Q_OBJECT
  
  public:
  static const int	FREE = 0;
  static const int	BUSY = 1;
  
  ClusterServer(RenderingInterface* interface, string url, int port);
  ~ClusterServer();

public:
  QUrl			getCentralServerUrl(void);
  int			getPort(void);
  void			setPort(int port);
  RenderingInterface*	getInterface(void);
  bool			getCentralServerConnectionState(void);
  void			setCentralServerConnectionState(bool state);

  void			waitCentralServerConnection(void);
  void			unlockCentralServerConnection(void);
  
private:
  RenderingInterface*	_interface;
  int			_port;
  QUrl			_centralServerUrl;
  ClusterServerThread*	_registerServerThread;
  ClusterServerThread*	_clientListenerThread;
  bool			_centralServerConnectionState;
  QMutex		_mutex;
  QWaitCondition	_centralServerConnectionLock;
};

#endif
