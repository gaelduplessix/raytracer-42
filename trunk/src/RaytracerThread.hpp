//
// RaytracerThread.hpp for raytracer in /home/jochau_g//data/dev/c/raytracer/raytracer-42
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Fri Apr 29 12:03:41 2011 gael jochaud-du-plessix
// Last update Fri Apr 29 16:09:31 2011 gael jochaud-du-plessix
//

#ifndef _RAYTRACERTHREAD_HPP_
#define _RAYTRACERTHREAD_HPP_

#include <QThread>
#include <QImage>
#include <vector>

#include "Ray.hpp"
#include "ObjectPrimitive.hpp"

using namespace std;

class Raytracer;

class	RaytracerThread : public QThread
{
public:
  RaytracerThread(Raytracer* raytracer);
  ~RaytracerThread();

  void	run(void);
  void	stop(void);
  void	pause(void);

  void	initBeforeLaunching(void);

private:
  Raytracer*			_raytracer;
  bool				_launched;
  bool				_isInit;
  double			_progress;
  QImage*			_image;
  vector< vector <bool> >	_raytracedPixels;
};

#endif
