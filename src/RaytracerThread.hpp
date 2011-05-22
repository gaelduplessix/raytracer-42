//
// RaytracerThread.hpp for raytracer in /home/jochau_g//data/dev/c/raytracer/raytracer-42
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Fri Apr 29 12:03:41 2011 gael jochaud-du-plessix
// Last update Sat May 21 16:56:38 2011 gael jochaud-du-plessix
//

#ifndef _RAYTRACERTHREAD_HPP_
#define _RAYTRACERTHREAD_HPP_

#include <QThread>
#include <QImage>
#include <QMutex>
#include <vector>

#include "Ray.hpp"
#include "ObjectPrimitive.hpp"
#include "RaytracerSubThread.hpp"

using namespace std;

class Raytracer;

class	RaytracerThread : public QThread
{
public:
  RaytracerThread(Raytracer* raytracer);

  bool	isLaunched(void);
  bool	isInit(void);

  void	run(void);
  void	stop(void);
  void	pause(void);

  double	getProgress() const;

  void	initBeforeLaunching(void);
  void	setRaytracedPixel(int x, int y, bool value);
  bool	isRaytracedPixel(int x, int y);

private:
  vector<RaytracerSubThread*>	_subThreads;
  bool				_launched;
  bool				_isInit;
  QMutex			_mutex;

public:
  Raytracer*			_raytracer;
  vector< vector <bool> >	_raytracedPixels;
};

#endif
