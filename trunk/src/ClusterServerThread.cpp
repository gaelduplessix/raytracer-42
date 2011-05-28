//
// ClusterServerThread.cpp for raytracer in /home/jochau_g//Desktop/raytracer-42/src
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Mon May 23 19:02:17 2011 gael jochaud-du-plessix
// Last update Sat May 28 21:37:43 2011 gael jochaud-du-plessix
//

#include "ClusterServerThread.hpp"
#include "ClusterServer.hpp"
#include "ServerEntry.hpp"

#include <sstream>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>

ClusterServerThread::ClusterServerThread(ClusterServer* clusterServer,
					 int type):
  _type(type),_clusterServer(clusterServer), _networkManager(0),
  _timer(NULL), _tcpServer(NULL), _stopReportConnectionError(false)
{
}

ClusterServerThread::~ClusterServerThread()
{
  exit();
  wait();
  if (_timer)
    delete _timer;
  if (_tcpServer)
    delete _tcpServer;
  _clusterServer->unlockCentralServerConnection();
}

void	ClusterServerThread::run(void)
{
  if (_type == ClusterServerThread::CENTRAL_REGISTER)
    {
      _timer = new QTimer();
      connect(_timer, SIGNAL(timeout()), this,
  	      SLOT(registerToCentralServer()));
      _timer->setInterval(1000);
      _timer->start();
    }
  else if (_type == ClusterServerThread::CLIENT_LISTENER)
    {
      _tcpServer = new QTcpServer();
      connect(_tcpServer, SIGNAL(newConnection()), this,
	      SLOT(newConnection()));
      if (_tcpServer->listen(QHostAddress::Any, _clusterServer->getPort()))
	{
	  _clusterServer->setPort(_tcpServer->serverPort());
	  _clusterServer->waitCentralServerConnection();
	  if (!_clusterServer->getCentralServerConnectionState())
	    return ;
	  _clusterServer->getInterface()
	    ->logServerConsoleMessage("<span style=\"color:green\">Success: "
				      "server ready, waiting for connection."
				      "</span>");
	}
      else
	{
	  _clusterServer->getInterface()
	    ->logServerConsoleMessage("<span style=\"color:red\">Error: "
				      "cannot create tcp server.</span>");
	}
    }
  exec();
}

void		ClusterServerThread::registerToCentralServer(void)
{
  _networkManager = new QNetworkAccessManager();
  connect(_networkManager, SIGNAL(finished(QNetworkReply*)), this,
	  SLOT(readCentralServerResponse(QNetworkReply*)));
  QUrl		postVars;
  ostringstream	value;
  postVars.addQueryItem("action", "logServer");
  value << _clusterServer->getPort();
  postVars.addQueryItem("serverPort", value.str().c_str());
  value.str("");
  value << ServerEntry::FREE;
  postVars.addQueryItem("serverStatus", value.str().c_str());
  value.str("");
  value << _clusterServer->getProgress();
  postVars.addQueryItem("serverProgress", value.str().c_str());
  QByteArray	postData(postVars.encodedQuery());
  _networkManager->post(QNetworkRequest(_clusterServer->getCentralServerUrl()),
			postData);
}

void	ClusterServerThread::readCentralServerResponse(QNetworkReply* reply)
{
  bool	stat = false;

  if (reply->error() != QNetworkReply::NoError)
    stat = false;
  else
    {
      QString	response(reply->readAll());
      if (response == "0")
	{
	  _stopReportConnectionError = false;
	  stat = true;
	}
      else
	stat = false;
    }
  _clusterServer->setCentralServerConnectionState(stat);
  if (!stat && !_stopReportConnectionError)
    {
      _clusterServer->getInterface()
	->logServerConsoleMessage("<span style=\"color:red\">Error: "
				  "central server connection failed</span>");
      _stopReportConnectionError = true;
    }
  _clusterServer->unlockCentralServerConnection();
  sender()->deleteLater();
}

void	ClusterServerThread::newConnection()
{
  _currentClientSocket = _tcpServer->nextPendingConnection();
  _clusterServer->getInterface()
    ->logServerConsoleMessage("<span>Info: "
			      "Connection etablished with client </span>"
			      + _currentClientSocket
			      ->peerAddress().toString().toStdString());
}
