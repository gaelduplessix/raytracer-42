//
// RaytracerSubThread.hpp for raytracer in /home/jochau_g//Desktop/raytracer-42/src
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Thu May 19 15:21:07 2011 gael jochaud-du-plessix
// Last update Thu May 19 17:03:51 2011 gael jochaud-du-plessix
//

#ifndef _RAYTRACERSUBTHREAD_HPP_
#define _RAYTRACERSUBTHREAD_HPP_

#include <QThread>

class RaytracerThread;

class	RaytracerSubThread : public QThread
{
public:
  RaytracerSubThread(RaytracerThread* mainThread, double startProgress,
		     double endProgress);

  void	run(void);
  void	stop(void);

public:
  int			_currentPixel;
  int			_currentPixelInLine;
  int			_currentLine;

private:
  RaytracerThread*	_mainThread;
  double		_startProgress;
  double		_endProgress;
  double		_currentProgress;
  bool			_launched;
};

#endif
