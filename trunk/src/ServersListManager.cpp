//
// ServersListManager.cpp for raytracer in /home/jochau_g//Desktop/raytracer-42/src
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Fri May 27 00:55:33 2011 gael jochaud-du-plessix
// Last update Tue May 31 20:16:52 2011 gael jochaud-du-plessix
//

#include <sstream>
#include <QNetworkReply>

#include "ServersListManager.hpp"
#include "ClusterClient.hpp"
#include "ServerEntry.hpp"

ServersListManager::ServersListManager(ClusterClient* clusterClient):
  _clusterClient(clusterClient), _networkManager(NULL), _timer(NULL),
  _stopReportConnectionError(false), _stopReportConnectionSuccess(false)
{  
}

ServersListManager::~ServersListManager()
{
  exit();
  wait();
  if (_networkManager)
    delete _networkManager;
  if (_timer)
    delete _timer;
}

void	ServersListManager::run()
{
  _timer = new QTimer();
  connect(_timer, SIGNAL(timeout()), this,
	  SLOT(updateServersListFromCentralServer()));
  _timer->setInterval(500);
  _timer->start();
  exec();
}

void	ServersListManager::updateServersListFromCentralServer()
{
  _networkManager = new QNetworkAccessManager();
  connect(_networkManager, SIGNAL(finished(QNetworkReply*)),
	  this, SLOT(receiveServersList(QNetworkReply*)));
  QUrl          postVars;
  ostringstream value;
  postVars.addQueryItem("action", "getServers");
  QByteArray    postData(postVars.encodedQuery());
  _networkManager->post(QNetworkRequest(_clusterClient->getCentralServerUrl()),
                        postData);
}

void	ServersListManager::receiveServersList(QNetworkReply* reply)
{
  if (reply->error() != QNetworkReply::NoError)
    {
      if (_stopReportConnectionError)
	return ;
      _stopReportConnectionError = true;
      _clusterClient->getInterface()
	->sendErrorMessage(tr("Cannot connect to cluster").toStdString());
    }
  else
    {
      _stopReportConnectionError = false;
      if (!_stopReportConnectionSuccess)
	_clusterClient->getInterface()
	  ->sendSuccessMessage(tr("Connected to cluster").toStdString());
      _stopReportConnectionSuccess = true;
      QString		response = reply->readAll();
      QStringList	servers = response.split("\n",
						 QString::SkipEmptyParts);
      for (int i = 0, l = servers.size(); i < l; i++)
	{
	  QStringList	serverInfos = servers[i].split("---");
	  if (serverInfos.size() >= 4)
	    {
	      _clusterClient->updateServersList(serverInfos[0],
						atoi(serverInfos[1]
						     .toStdString().c_str()),
						atoi(serverInfos[2]
						     .toStdString().c_str()),
						atoi(serverInfos[3]
						     .toStdString().c_str())
						);
	    }
	}
    }
}
