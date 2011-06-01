//
// ClusterClient.hpp for raytracer in /home/jochau_g//Desktop/raytracer-42/src
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Mon May 23 13:12:10 2011 gael jochaud-du-plessix
// Last update Wed Jun  1 17:10:46 2011 loick michard
//

#ifndef _CLUSTERCLIENT_HPP_
#define _CLUSTERCLIENT_HPP_

#include <string>
#include <vector>
#include <QUrl>
#include <QMutexLocker>
#include <QRect>

#include "RenderingInterface.hpp"
#include "ServersListManager.hpp"
#include "RenderingConfiguration.hpp"
#include "Scene.hpp"
#include "ClusterRenderingThread.hpp"

class ServerEntry;

using namespace std;

class ClusterClient
{
public:
  enum ImageSection
    {
      NOT_RAYTRACED,
      RAYTRACING,
      RAYTRACED
    };
  
  ClusterClient(RenderingInterface* interface, string url, int nbSubdibisions,
		int interval);
  ClusterClient(RenderingInterface* interface, QByteArray& data,
		int interval);
  ~ClusterClient();

  RenderingInterface*		getInterface();
  QUrl&				getCentralServerUrl();
  int				getSessionId();
  RenderingConfiguration&	getRenderingConfiguration();
  Scene*			getScene();

  QByteArray			saveState(void);

  vector <ServerEntry*>	getServers(void);
  ServerEntry*	getServer(QString ip, int port);
  void		addServer(QString ip, int port, int status, int progress);
  void		updateServersList(QString ip, int port, int status,
				  int progress);
  void		removeFromServersList(ServerEntry* entry, bool destroy=false);
  ServerEntry*	getFreeServer(void);

  void		launchRendering(RenderingConfiguration* config, Scene* scene);
  void		launchNewSession(RenderingConfiguration* config, Scene* scene);
  void		relaunchSession(void);
  void		pauseRendering(void);
  void		stopRendering(void);

  bool		isRenderingFinished(bool raytracing=false);
  bool		getSectionToRaytrace(QRect& section, bool raytracing=false);
  void		processReceivedSection(QRect& section, QImage& image);

protected:
  RenderingInterface*			_interface;
  QUrl					_centralServerUrl;
  int					_nbSubdivisions;
  ServersListManager*			_serversListManager;
  vector <ServerEntry*>			_servers;
  int					_sessionId;
  vector< vector <ImageSection> >	_imageSections;
  RenderingConfiguration		_renderingConfiguration;
  Scene*				_scene;
  QMutex				_mutex;
  ClusterRenderingThread*		_renderingThread;
  bool					_restored;
};

#endif
