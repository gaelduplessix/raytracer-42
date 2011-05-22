//
// RaytracerThread.cpp for raytracer in /home/jochau_g//data/dev/c/raytracer/raytracer-42
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Fri Apr 29 12:07:49 2011 gael jochaud-du-plessix
// Last update Sat May 21 16:56:52 2011 gael jochaud-du-plessix
//

#include <QMutexLocker>

#include "Raytracer.hpp"
#include "RaytracerThread.hpp"
#include "RaytracerSubThread.hpp"

RaytracerThread::RaytracerThread(Raytracer* raytracer):
  _subThreads(), _launched(false), _isInit(false),
  _raytracer(raytracer)
{
}

bool  RaytracerThread::isLaunched(void)
{
  return (_launched);
}

bool  RaytracerThread::isInit(void)
{
  return (_isInit);
}

void		RaytracerThread::run(void)
{
  if (!_isInit)
    initBeforeLaunching();
  _launched = true;
  for (unsigned int i = 0; i < _subThreads.size(); i++)
    _subThreads[i]->start();
  for (unsigned int i = 0; i < _subThreads.size(); i++)
    _subThreads[i]->wait();  
  if (getProgress() >= 1 && _raytracer->getRenderingInterface())
    {
      _raytracer->getRenderingInterface()->renderingHasFinished();
      _isInit = false;
    }
  _launched = false;
}

void	RaytracerThread::stop(void)
{
  for (unsigned int i = 0; i < _subThreads.size(); i++)
    _subThreads[i]->stop();
  _launched = false;
  _isInit = false;
  _raytracer->getRenderingInterface()->renderingHasFinished();
}

void	RaytracerThread::pause(void)
{
  _launched = false;
  for (unsigned int i = 0; i < _subThreads.size(); i++)
    _subThreads[i]->stop();
}

double		RaytracerThread::getProgress(void) const
{
  double	progress = 0;

  for (unsigned int i = 0, l = _subThreads.size(); i < l; i++)
    progress += (1.0 / l) * _subThreads[i]->getProgress();
  return (progress);
}

void	RaytracerThread::initBeforeLaunching(void)
{
  int	width = _raytracer->getRenderingConfiguration()->getWidth();
  int	height = _raytracer->getRenderingConfiguration()->getHeight();

  _isInit = true;
  _raytracedPixels.resize(width);
  for (int i = 0; i < width; i++)
    {
      _raytracedPixels[i].resize(height);
      for (int j = 0; j < height; j++)
	_raytracedPixels[i][j] = false;
    }
  if (_raytracer->getRenderingConfiguration()->isPhotonMappingEnabled())
    {
      _raytracer->_photonMap = new PhotonMap;
      _raytracer->getRenderingInterface()->photonMappingHasBegun();
      _raytracer->_photonMap->fillPhotonMap(_raytracer);
      _raytracer->getRenderingInterface()->photonMappingHasFinished();
    }
  for (unsigned int i = 0; i < _subThreads.size(); i++)
    {
      if (_subThreads[i])
	delete _subThreads[i];
    }
  int nbThreads = _raytracer->getRenderingConfiguration()->getNbThreads();
  _subThreads.resize(nbThreads);
  for (int i = 0; i < nbThreads; i++)
    {
      _subThreads[i] = new RaytracerSubThread(this,
					      i * 1.0 / nbThreads,
					      (i + 1) * 1.0 / nbThreads);
    }
}

void	RaytracerThread::setRaytracedPixel(int x, int y, bool value)

{
  QMutexLocker	lock(&_mutex);
  _raytracedPixels[x][y] = value;
}

bool	RaytracerThread::isRaytracedPixel(int x, int y)
{
  QMutexLocker	lock(&_mutex);
  return (_raytracedPixels[x][y]);
}
