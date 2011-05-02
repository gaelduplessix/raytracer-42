//
// RaytracerThread.hpp for raytracer in /home/jochau_g//data/dev/c/raytracer/raytracer-42
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Fri Apr 29 12:03:41 2011 gael jochaud-du-plessix
// Last update Mon May  2 15:11:21 2011 gael jochaud-du-plessix
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
  void	setRaytracedPixel(int x, int y, bool value);

  vector< vector <bool> >	_raytracedPixels;
  double			_progress;
  int				_currentPixel;
private:
  Raytracer*			_raytracer;
  bool				_launched;
  bool				_isInit;
  QImage*			_image;  
};

#endif
