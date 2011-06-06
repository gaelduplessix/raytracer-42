//
// RaytracerSubThread.cpp for raytracer in /home/jochau_g//Desktop/raytracer-42/src
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Thu May 19 15:41:28 2011 gael jochaud-du-plessix
// Last update Mon Jun  6 18:18:01 2011 gael jochaud-du-plessix
//

#include "Raytracer.hpp"
#include "RaytracerThread.hpp"
#include "RaytracerSubThread.hpp"

RaytracerSubThread::RaytracerSubThread(RaytracerThread* mainThread,
				       double startProgress,
				       double endProgress):
  _currentPixel(0), _currentPixelInLine(-1), _currentLine(-1),
  _currentProgress(startProgress), _mainThread(mainThread),
  _startProgress(startProgress), _endProgress(endProgress),
  _launched(false)
{
  _currentPixel = _startProgress
    * (mainThread->_raytracer->getRenderingConfiguration()
       ->getSection().width()
       * mainThread->_raytracer->getRenderingConfiguration()
       ->getSection().height());
}

void		RaytracerSubThread::run(void)
{
  _launched = true;
  while (_launched && _currentProgress < _endProgress)
    _mainThread->_raytracer->renderingLoop(_currentProgress, this);
}

void		RaytracerSubThread::stop(void)
{
  _launched = false;
}

double		RaytracerSubThread::getProgress(void) const
{
  return ((_currentProgress - _startProgress)
	  / (_endProgress - _startProgress));
}
