//
// ClusterServerThread.cpp for raytracer in /home/jochau_g//Desktop/raytracer-42/src
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Mon May 23 19:02:17 2011 gael jochaud-du-plessix
// Last update Wed May 25 15:59:08 2011 gael jochaud-du-plessix
//

#include "ClusterServerThread.hpp"

#include "ClusterServer.hpp"

#include <sstream>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>


ClusterServerThread::ClusterServerThread(ClusterServer* clusterServer,
					 int type):
  _type(type),_clusterServer(clusterServer), _networkManager(0),
  _timer(NULL)
{
}
#include <iostream>
ClusterServerThread::~ClusterServerThread()
{
  exit();
  wait();
  if (_timer)
    delete (_timer);
}

void	ClusterServerThread::run(void)
{
  _timer = new QTimer();
  if (_type == ClusterServerThread::CENTRAL_REGISTER)
    {
      connect(_timer, SIGNAL(timeout()), this,
  	      SLOT(registerToCentralServer()));
      _timer->setInterval(1000);
      _timer->start();
    }
  else if (_type == ClusterServerThread::CLIENT_LISTENER)
    {
      
    }
  exec();
}

void		ClusterServerThread::registerToCentralServer(void)
{
  _networkManager = new QNetworkAccessManager();
  connect(_networkManager, SIGNAL(finished(QNetworkReply*)), this,
	  SLOT(readCentralServerResponse(QNetworkReply*)));
  QUrl		postVars;

  postVars.addQueryItem("action", "logServer");
  postVars.addQueryItem("serverPort", "4242");
  ostringstream	status;
  status << ClusterServer::FREE;
  postVars.addQueryItem("serverStatus", status.str().c_str());
  QByteArray	postData(postVars.encodedQuery());
  _networkManager->post(QNetworkRequest(_clusterServer->getCentralServerUrl()),
			postData);
}

void	ClusterServerThread::readCentralServerResponse(QNetworkReply* reply)
{
  if (reply->error() != QNetworkReply::NoError)
    {
      cout << "Error\n";
    }
  sender()->deleteLater();
}
