//
// RaytracerThread.cpp for raytracer in /home/jochau_g//data/dev/c/raytracer/raytracer-42
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Fri Apr 29 12:07:49 2011 gael jochaud-du-plessix
// Last update Fri Apr 29 12:37:23 2011 gael jochaud-du-plessix
//

#include "RaytracerThread.hpp"

RaytracerThread::RaytracerThread(const Raytracer* raytracer):
  _raytracer(raytracer), _launched(false)
{
  
}

RaytracerThread::~RaytracerThread()
{
  
}

#include <iostream>

void	RaytracerThread::run(void)
{
  _launched = true;
  while (_launched)
    {
      std::cout << "running..." << std::endl;
      sleep(1);
    }
  std::cout << "stoped." << std::endl;
}

void	RaytracerThread::stop(void)
{
  _launched = false;
}
