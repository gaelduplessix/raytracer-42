//
// ClusterRenderingThread.hpp for raytracer in /home/jochau_g//Desktop/raytracer-42/src
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Sun May 29 18:09:22 2011 gael jochaud-du-plessix
// Last update Sun May 29 18:25:29 2011 gael jochaud-du-plessix
//

#ifndef _CLUSTERRENDERINGTHREAD_HPP_
#define _CLUSTERRENDERINGTHREAD_HPP_

#include <QThread>

class ClusterClient;

class ClusterRenderingThread : public QThread
{
public:
  ClusterRenderingThread(ClusterClient* clusterClient);

  void	run(void);

protected:
  ClusterClient*	_clusterClient;
  bool			_stopRendering;
};

#endif
