//
// ClusterServer.cpp for raytracer in /home/jochau_g//Desktop/raytracer-42/src
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Mon May 23 13:05:47 2011 gael jochaud-du-plessix
// Last update Sun May 29 14:54:26 2011 gael jochaud-du-plessix
//

#include "ClusterServer.hpp"

#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>

ClusterServer::ClusterServer(RenderingInterface* interface, string url,
			     int port):
  _interface(interface), _port(port), _centralServerUrl(url.c_str()),
  _centralServerConnectionState(false), _status(ServerEntry::FREE),
  _progress(0)
{
  getInterface()
    ->logServerConsoleMessage("<span>Info: "
			      "connecting to central server...</span>");
  _registerServerThread =
    new ClusterServerThread(this, ClusterServerThread::CENTRAL_REGISTER);
  _clientListenerThread =
    new ClusterServerThread(this, ClusterServerThread::CLIENT_LISTENER);
  _registerServerThread->start();
  _clientListenerThread->start();
}

ClusterServer::~ClusterServer()
{
  if (_registerServerThread)
    delete _registerServerThread;
  if (_clientListenerThread)
    delete _clientListenerThread;
}

int        ClusterServer::getPort(void)
{
  QMutexLocker	lock(&_mutex);
  return (_port);
}

void        ClusterServer::setPort(int port)
{
  QMutexLocker	lock(&_mutex);
  _port = port;
}

int	ClusterServer::getStatus(void)
{
  return (_status);
}

void	ClusterServer::setStatus(int status)
{
  _status = status;
}

int	ClusterServer::getProgress(void)
{
  return (_progress);
}

void	ClusterServer::setProgress(int progress)
{
  _progress = progress;
}

QUrl&        ClusterServer::getCentralServerUrl(void)
{
  return (_centralServerUrl);
}

RenderingInterface*	ClusterServer::getInterface(void)
{
  return (_interface);
}

bool	ClusterServer::getCentralServerConnectionState(void)

{ 
  QMutexLocker	lock(&_mutex);
  return (_centralServerConnectionState);
}

void	ClusterServer::setCentralServerConnectionState(bool state)
{
  QMutexLocker	lock(&_mutex);
  _centralServerConnectionState = state;
}

void	ClusterServer::waitCentralServerConnection(void)
{
  _centralServerConnectionLock.wait(&_mutex);
}

void	ClusterServer::unlockCentralServerConnection(void)
{
  _centralServerConnectionLock.wakeAll();
}
