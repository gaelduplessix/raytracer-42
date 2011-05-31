//
// RegisterServerThread.cpp for raytracer in /home/jochau_g//Desktop/raytracer-42/src
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Mon May 30 17:45:20 2011 gael jochaud-du-plessix
// Last update Tue May 31 17:36:52 2011 gael jochaud-du-plessix
//

#include "RegisterServerThread.hpp"
#include "ClusterServer.hpp"
#include "ServerEntry.hpp"

#include <sstream>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>

RegisterServerThread::RegisterServerThread(ClusterServer* clusterServer):
  _clusterServer(clusterServer), _networkManager(0), _timer(NULL),
  _serverReady(false), _stopReportConnectionError(false)
{
}

RegisterServerThread::~RegisterServerThread()
{
  exit();
  wait();
  if (_timer)
    delete _timer;
}

void	RegisterServerThread::run(void)
{
  _timer = new QTimer();
  connect(_timer, SIGNAL(timeout()), this,
	  SLOT(registerToCentralServer()));
  _timer->setInterval(500);
  _timer->start();
  exec();
}

void		RegisterServerThread::registerToCentralServer(void)
{
  _networkManager = new QNetworkAccessManager();
  connect(_networkManager, SIGNAL(finished(QNetworkReply*)), this,
	  SLOT(readCentralServerResponse(QNetworkReply*)));
  QUrl		postVars;
  ostringstream	value;
  if (_clusterServer->getPort() > 0)
    {
      postVars.addQueryItem("action", "logServer");
      value << _clusterServer->getPort();
      postVars.addQueryItem("serverPort", value.str().c_str());
      value.str("");
      value << _clusterServer->getStatus();
      postVars.addQueryItem("serverStatus", value.str().c_str());
      value.str("");
      value << _clusterServer->getProgress();
      postVars.addQueryItem("serverProgress", value.str().c_str());
    }
  else
    postVars.addQueryItem("action", "serverLaunched");
  QByteArray	postData(postVars.encodedQuery());
  _networkManager->post(QNetworkRequest(_clusterServer->getCentralServerUrl()),
			postData);
}

void	RegisterServerThread::readCentralServerResponse(QNetworkReply* reply)
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
  if (!_serverReady)
    {
      _serverReady = true;
      emit launchServer();
    }
  sender()->deleteLater();
}
