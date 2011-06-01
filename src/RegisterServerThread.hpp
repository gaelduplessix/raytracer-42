//
// RegisterServerThread.hpp for raytracer in /home/jochau_g//Desktop/raytracer-42/src
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Mon May 30 17:44:54 2011 gael jochaud-du-plessix
// Last update Wed Jun  1 16:09:49 2011 loick michard
//

#ifndef _CLUSTERSERVERTHREAD_HPP_
#define _CLUSTERSERVERTHREAD_HPP_

#include <QObject>
#include <QThread>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QTimer>
#include <QTcpServer>
#include <QTcpSocket>
#include <QRect>

#include <string>

using namespace std;

class ClusterServer;

class RegisterServerThread : public QThread
{
Q_OBJECT

public:
  RegisterServerThread(ClusterServer* clusterServer, int interval);
  ~RegisterServerThread();

  void		run(void);

  bool		isConnectedToClient(void);

  void		receiveSectionRequest(void);
  void		requestSessionData(void);

signals:
  void		launchServer(void);

public slots:
  void		readCentralServerResponse(QNetworkReply* reply);
  void		registerToCentralServer(void);

private:
  ClusterServer*		_clusterServer;
  QNetworkAccessManager*	_networkManager;
  QTimer*			_timer;
  bool				_serverReady;
  bool				_stopReportConnectionError;
  int				_interval;
};

#endif
