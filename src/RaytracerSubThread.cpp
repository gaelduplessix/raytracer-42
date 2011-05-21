//
// RaytracerSubThread.cpp for raytracer in /home/jochau_g//Desktop/raytracer-42/src
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Thu May 19 15:41:28 2011 gael jochaud-du-plessix
// Last update Thu May 19 19:49:05 2011 gael jochaud-du-plessix
//

#include "Raytracer.hpp"
#include "RaytracerThread.hpp"
#include "RaytracerSubThread.hpp"

RaytracerSubThread::RaytracerSubThread(RaytracerThread* mainThread,
				       double startProgress,
				       double endProgress):
  _currentPixel(0), _currentPixelInLine(-1), _currentLine(-1),
  _mainThread(mainThread), _startProgress(startProgress),
  _endProgress(endProgress), _currentProgress(startProgress), _launched(false)
{
  _currentPixel = _startProgress
    * (mainThread->_raytracer->getRenderingConfiguration()->getWidth()
       * mainThread->_raytracer->getRenderingConfiguration()->getHeight());
}

#include <stdio.h>

void		RaytracerSubThread::run(void)
{
  _launched = true;
  while (_launched && _currentProgress < _endProgress)
    {
      printf("a: %f : %f\n", _startProgress, _currentProgress);
      _mainThread->_raytracer->renderingLoop(_currentProgress, this);
      printf("b: %f : %f\n", _startProgress, _currentProgress);
    }
}

void		RaytracerSubThread::stop(void)
{
  _launched = false;
}
