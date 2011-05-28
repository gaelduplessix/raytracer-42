//
// ClusterServer.hpp for raytracer in /home/jochau_g//Desktop/raytracer-42/src
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Mon May 23 13:05:47 2011 gael jochaud-du-plessix
// Last update Sat May 28 21:42:01 2011 gael jochaud-du-plessix
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
#include "ServerEntry.hpp"

using namespace std;

class ClusterServer : public QObject
{
  Q_OBJECT
  
  public:  
  ClusterServer(RenderingInterface* interface, string url, int port);
  ~ClusterServer();

public:
  QUrl&			getCentralServerUrl(void);
  int			getPort(void);
  void			setPort(int port);
  int			getStatus(void);
  void			setStatus(int status);
  int			getProgress(void);
  void			setProgress(int progress);
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
  int			_status;
  int			_progress;
};

#endif
