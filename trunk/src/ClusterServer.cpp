//
// ClusterServer.cpp for raytracer in /home/jochau_g//Desktop/raytracer-42/src
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Mon May 23 13:05:47 2011 gael jochaud-du-plessix
// Last update Wed May 25 16:50:47 2011 gael jochaud-du-plessix
//

#include "ClusterServer.hpp"

#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>

#ifdef Q_OS_UNIX
#include <stdio.h>
#endif

ClusterServer::ClusterServer(string url, int port):
  _port(port), _centralServerUrl(url.c_str())
{
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
  return (_port);
}

QUrl        ClusterServer::getCentralServerUrl(void)
{
  return (_centralServerUrl);
}
