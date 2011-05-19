//
// RaytracerSubThread.cpp for raytracer in /home/jochau_g//Desktop/raytracer-42/src
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Thu May 19 15:41:28 2011 gael jochaud-du-plessix
// Last update Thu May 19 16:21:09 2011 gael jochaud-du-plessix
//

#include "RaytracerSubThread.hpp"

#include <iostream>

RaytracerSubThread::RaytracerSubThread(RaytracerThread* mainThread,
				       double startProgress,
				       double endProgress):
  _mainThread(mainThread), _startProgress(startProgress),
  _endProgress(endProgress), _currentProgress(0.0)
{
  //cout << _startProgress << " - " << _endProgress << endl;
}

void		RaytracerSubThread::run(void)
{
}
