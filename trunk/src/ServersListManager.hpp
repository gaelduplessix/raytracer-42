//
// ServersListManager.hpp for raytracer in /home/jochau_g//Desktop/raytracer-42/src
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Fri May 27 00:50:20 2011 gael jochaud-du-plessix
// Last update Fri May 27 12:15:22 2011 gael jochaud-du-plessix
//

#ifndef _SERVERSLISTMANAGER_HPP_
#define _SERVERSLISTMANAGER_HPP_

#include <QObject>
#include <QThread>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QTimer>
#include <QTcpSocket>

#include <string>

using namespace std;

class ClusterClient;

class ServersListManager : public QThread
{
Q_OBJECT

public:
  ServersListManager(ClusterClient* clusterServer);
  ~ServersListManager();

  void		run(void);

public slots:
  void		updateServersListFromCentralServer();
  void		receiveServersList(QNetworkReply*);

private:
  ClusterClient*		_clusterClient;
  QNetworkAccessManager*	_networkManager;
  QTimer*			_timer;
  bool				_stopReportConnectionError;
};

#endif
