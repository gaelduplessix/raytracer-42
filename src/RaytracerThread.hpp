//
// RaytracerThread.hpp for raytracer in /home/jochau_g//data/dev/c/raytracer/raytracer-42
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Fri Apr 29 12:03:41 2011 gael jochaud-du-plessix
// Last update Fri Apr 29 12:37:16 2011 gael jochaud-du-plessix
//

#ifndef _RAYTRACERTHREAD_HPP_
#define _RAYTRACERTHREAD_HPP_

#include <QThread>

class Raytracer;

class	RaytracerThread : public QThread
{
public:
  RaytracerThread(const Raytracer* raytracer);
  ~RaytracerThread();

  void	run(void);
  void	stop(void);

private:
  const Raytracer*	_raytracer;
  bool			_launched;
};

#endif
