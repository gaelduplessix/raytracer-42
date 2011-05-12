//
// RaytracerThread.cpp for raytracer in /home/jochau_g//data/dev/c/raytracer/raytracer-42
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Fri Apr 29 12:07:49 2011 gael jochaud-du-plessix
// Last update Thu May 12 15:41:46 2011 gael jochaud-du-plessix
//

#include "Raytracer.hpp"
#include "RaytracerThread.hpp"

RaytracerThread::RaytracerThread(Raytracer* raytracer):
  _raytracer(raytracer), _launched(false), _isInit(false), _progress(0)
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
  while (_launched && _progress < 1)
    _raytracer->renderingLoop(_progress);
  if (_progress >= 1 && _raytracer->getRenderingInterface())
    {
      _raytracer->getRenderingInterface()->renderingHasFinished();
      _isInit = false;
    }
  _launched = false;
}

void	RaytracerThread::stop(void)
{
  _launched = false;
  _isInit = false;
  _raytracer->getRenderingInterface()->renderingHasFinished();
}

void	RaytracerThread::pause(void)
{
  _launched = false;
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
  _progress = 0.f;
  _currentPixel = 0;
}

void	RaytracerThread::setRaytracedPixel(int x, int y, bool value)
{
  _raytracedPixels[x][y] = value;
}
