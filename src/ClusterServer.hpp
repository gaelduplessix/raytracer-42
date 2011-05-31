//
// ClusterServer.hpp for raytracer in /home/jochau_g//Desktop/raytracer-42/src
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Mon May 23 13:05:47 2011 gael jochaud-du-plessix
// Last update Tue May 31 14:19:33 2011 gael jochaud-du-plessix
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
#include "RegisterServerThread.hpp"
#include "ServerEntry.hpp"
#include "Scene.hpp"
#include "RenderingConfiguration.hpp"
#include "Raytracer.hpp"

using namespace std;

class ClusterServer : public QObject, public RenderingInterface
{
  Q_OBJECT  
  
public:
  static const int	REQUEST_SESSION_DATA = 0;
  static const int	SEND_RAYTRACE_RESPONSE = 1;

  ClusterServer(RenderingInterface* interface, string url, int port);
  ~ClusterServer();

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

  bool		isConnectedToClient(void);
  bool		receiveSectionRequest(void);
  void		requestSessionData(void);
  bool          receiveSessionDatas(void);

  void		processSectionRequest(void);

  void		pixelHasBeenRendered(int x, int y, Color color);
  void		renderingHasFinished(void);

public slots:
  void		launchServer(void);
  void          newConnection(void);
  void          clientDisconnect(void);
  void          dataReceived(void);
  
private:
  RenderingInterface*	_interface;
  int			_port;
  QUrl			_centralServerUrl;
  RegisterServerThread*	_registerServerThread;
  QTcpServer*		_tcpServer;
  QTcpSocket*		_currentClientSocket;
  bool			_centralServerConnectionState;
  QMutex		_mutex;
  int			_status;
  int			_progress;
  int			_currentRequest;
  int			_currentSessionId;
  QRect			_currentSection;
  int			_currentPacketSize;
  Raytracer*		_raytracer;
  Scene*		_scene;
  RenderingConfiguration _renderingConf;
  bool			_readyToRaytrace;
  QImage*		_raytracedImage;
};

#endif
