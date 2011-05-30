//
// ServerEntry.hpp for raytracer in /home/jochau_g//Desktop/raytracer-42/src
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Thu May 26 18:14:23 2011 gael jochaud-du-plessix
// Last update Mon May 30 15:23:23 2011 gael jochaud-du-plessix
//

#ifndef _SERVERENTRY_HPP_
#define _SERVERENTRY_HPP_

#include <QObject>
#include <QTcpSocket>
#include <QString>
#include <QRect>

#include "ClusterClient.hpp"

class ServerEntry : public QObject
{
Q_OBJECT

public:
  static const int      FREE = 0;
  static const int      WAITING_REQUEST = 1;
  static const int      PROCESSING_REQUEST = 2;
  static const int      DOWNLOADING_RESSOURCES = 3;
  static const int      PROCESSING_RESSOURCES = 4;
  static const int      RAYTRACING = 5;
  static const int      SENDING_RESPONSE = 6;

  static const int	REQUEST_SECTION = 0;
  static const int	SEND_SESSION_DATAS = 1;

  ServerEntry();
  ServerEntry(ClusterClient* clusterClient, QString ip, int port,
	      int status=0, int progress=0);
  ~ServerEntry();

  QString&	getIp(void);
  void		setIp(QString& ip);
  int		getPort(void);
  void		setPort(int port);
  int		getStatus(void);
  void		setStatus(int status);
  int		getProgress(void);
  void		setProgress(int progress);

  bool		isConnectionOpened(void);
  void		openConnection(void);

  bool		requestSection(QRect section);

public slots:
  void		onConnectionOpened(void);
  void		onConnectionClosed(void);
  void		onDataReceived(void);

private:
  ClusterClient*	_clusterClient;
  QString		_ip;
  int			_port;
  int			_status;
  int			_progress;
  QTcpSocket*		_socket;
  Point			_currentSection;
  int			_currentRequest;
};

#endif
