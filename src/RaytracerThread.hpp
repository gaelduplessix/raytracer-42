//
// RaytracerThread.hpp for raytracer in /home/jochau_g//data/dev/c/raytracer/raytracer-42
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Fri Apr 29 12:03:41 2011 gael jochaud-du-plessix
// Last update Fri Apr 29 14:46:00 2011 samuel olivier
//

#ifndef _RAYTRACERTHREAD_HPP_
#define _RAYTRACERTHREAD_HPP_

#include <QThread>
#include <vector>

#include "Ray.hpp"
#include "ObjectPrimitive.hpp"

using namespace std;

class Raytracer;

typedef struct			s_intersected_object
{
  const ObjectPrimitive*	primitive;
  vector<double>		k;
}				t_intersected_object;

class	RaytracerThread : public QThread
{
public:
  RaytracerThread(const Raytracer* raytracer);
  ~RaytracerThread();

  void	run(void);
  void	stop(void);

  const	vector<t_intersected_object>&	getIntersectingObjects(Ray ray);
  const ObjectPrimitive*
  getNearestObject(const vector<t_intersected_object>&,
			 double *res);

private:
  const Raytracer*	_raytracer;
  bool			_launched;
};

#endif
