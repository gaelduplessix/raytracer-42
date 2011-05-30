//
// ClusterServer.cpp for raytracer in /home/jochau_g//Desktop/raytracer-42/src
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Mon May 23 13:05:47 2011 gael jochaud-du-plessix
// Last update Tue May 31 01:39:18 2011 gael jochaud-du-plessix
//

#include "ClusterServer.hpp"
#include "Resources.hpp"

#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>

ClusterServer::ClusterServer(RenderingInterface* interface, string url,
			     int port):
  _interface(interface), _port(port), _centralServerUrl(url.c_str()),
  _registerServerThread(NULL), _tcpServer(NULL), _currentClientSocket(NULL),
  _centralServerConnectionState(false), _status(ServerEntry::FREE),
  _progress(0), _currentRequest(-1), _currentSessionId(-1),
  _currentSection(-1, -1, -1, -1), _currentPacketSize(0), _scene(NULL),
  _renderingConf(), _readyToRaytrace(false)
{
  getInterface()
    ->logServerConsoleMessage("<span>Info: "
			      "connecting to central server...</span>");
  _registerServerThread = new RegisterServerThread(this);
  connect(_registerServerThread, SIGNAL(launchServer()),
	  this, SLOT(launchServer()));
  _registerServerThread->start();
  _scene = new Scene();
}

ClusterServer::~ClusterServer()
{
  if (_registerServerThread)
    delete _registerServerThread;
  if (_tcpServer)
    {
      _tcpServer->close();
      delete _tcpServer;
    }
  if (_scene)
    delete _scene;
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

void	ClusterServer::launchServer(void)
{
  if (_tcpServer)
    return ;
  _tcpServer = new QTcpServer();
  connect(_tcpServer, SIGNAL(newConnection()), this,
	  SLOT(newConnection()));
  if (_tcpServer->listen(QHostAddress::Any, getPort()))
    {
      setPort(_tcpServer->serverPort());
      if (!getCentralServerConnectionState())
	return ;
      ostringstream portStr;
      portStr << getPort();
      _interface
	->logServerConsoleMessage(tr("<span style=\"color:green\">Success:"
				     " server launched on port "
				     "<strong>%1</strong>, "
				     "waiting for connection.</span>")
				  .arg(QString(portStr.str().c_str()))
				  .toStdString());
    }
  else
    {
      _interface
	->logServerConsoleMessage("<span style=\"color:red\">Error: "
				  "cannot create tcp server.</span>");
    }  
}

void	ClusterServer::newConnection()
{
  _currentClientSocket = _tcpServer->nextPendingConnection();
  connect(_currentClientSocket, SIGNAL(disconnected()), this,
	  SLOT(clientDisconnect()));
  connect(_currentClientSocket, SIGNAL(readyRead()), this,
	  SLOT(dataReceived()));
  _interface
    ->logServerConsoleMessage(tr("<span>Info: Connection etablished "
				 "with client <strong>%1</strong></span>")
			      .arg(_currentClientSocket
				   ->peerAddress().toString()).toStdString());
  setStatus(ServerEntry::WAITING_REQUEST);
}

void	ClusterServer::clientDisconnect()
{
  _interface
    ->logServerConsoleMessage(tr("<span>Info: Client disconnected</span>")
			      .toStdString());
  setStatus(ServerEntry::FREE);
  _currentRequest = -1;
  _currentSessionId = -1;
  _currentSection = QRect(-1, -1, -1, -1);
  _currentPacketSize = 0;
}

bool	ClusterServer::isConnectedToClient(void)
{
  return (!(!_currentClientSocket
	    || _currentClientSocket->state()
	    != QAbstractSocket::ConnectedState));
}

void	ClusterServer::dataReceived(void)
{
  if (!isConnectedToClient())
    return ;
  QDataStream	stream(_currentClientSocket);
  if (_currentRequest == -1)
    {
      if (_currentClientSocket->bytesAvailable() < sizeof(int))
	return ;
      stream >> _currentRequest;
      setStatus(ServerEntry::PROCESSING_REQUEST);
    }
  if (_currentRequest == ServerEntry::REQUEST_SECTION)
    {
      if (receiveSectionRequest())
	_currentRequest = -1;
    }
  else if (_currentRequest == ServerEntry::SEND_SESSION_DATAS)
    {
      if (receiveSessionDatas())
	_currentRequest = -1;
    }
}

bool		ClusterServer::receiveSectionRequest(void)
{
  QDataStream	stream(_currentClientSocket);
  int		sessionId;
  if (_currentClientSocket->bytesAvailable() < sizeof(int))
    return (false);
  stream >> sessionId;
  if (_currentClientSocket->bytesAvailable() < sizeof(QRect))
    return (false);
  stream >> _currentSection;
  if (sessionId != _currentSessionId || !_readyToRaytrace)
    requestSessionData();
  return (true);
}

void		ClusterServer::requestSessionData(void)
{
  if (!isConnectedToClient())
    return ;
  QByteArray	packet;
  QDataStream	stream(&packet, QIODevice::WriteOnly);
  stream << (int)ClusterServer::REQUEST_SESSION_DATA;
  _currentClientSocket->write(packet);
}

bool		ClusterServer::receiveSessionDatas(void)
{
  QDataStream	stream(_currentClientSocket);

  if (_currentPacketSize == 0)
    {
      if (_currentClientSocket->bytesAvailable() < sizeof(int))
	return (false);
      stream >> _currentPacketSize;
    }
  if (_currentClientSocket->bytesAvailable() < _currentPacketSize)
    return (false);
  QByteArray	resourcesBytes;
  QByteArray	renderingConfBytes;
  QString	sceneFilename;
  stream >> resourcesBytes;
  stream >> renderingConfBytes;
  stream >> sceneFilename;
  Resources::getInstance()->createResources(resourcesBytes);
  Resources::getInstance()->createResourcesInTemporaryDir();
  _renderingConf = RenderingConfiguration(renderingConfBytes);
  if (_renderingConf._cubeMapPath != "")
    {
      _renderingConf.setCubeMap(new CubeMap(_renderingConf._cubeMapPath),
				_renderingConf._cubeMapPath);
    }
  _scene->loadFromFile(sceneFilename.toStdString(), _interface);
  cout << _scene->getObjects().size() << endl;
  _readyToRaytrace = true;
  return (true);
}
