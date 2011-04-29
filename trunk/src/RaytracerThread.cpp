//
// RaytracerThread.cpp for raytracer in /home/jochau_g//data/dev/c/raytracer/raytracer-42
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Fri Apr 29 12:07:49 2011 gael jochaud-du-plessix
// Last update Fri Apr 29 14:45:18 2011 samuel olivier
//

#include "Raytracer.hpp"
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

const vector<t_intersected_object>&
RaytracerThread::getIntersectingObjects(Ray ray)
{
  int				nb_object;
  int				i = -1;
  vector<t_intersected_object>	*intersections;
  const vector<Object*>&	objects = _raytracer->getScene()->getObjects();
  t_intersected_object		tmp;
  int				j;

  intersections = new vector<t_intersected_object>;
  nb_object = objects.size();
  while (++i < nb_object)
    {
      const vector<ObjectPrimitive*>&	primitives = objects[i]->getPrimitives();
      int				nb_primitive;
      nb_primitive = primitives.size();
      j = -1;
      while (++j < nb_primitive)
	{
	  tmp.primitive = primitives[j];
	  tmp.k = tmp.primitive->intersectWithRay(ray);
	  if (tmp.k.size() > 0)
	    intersections->push_back(tmp);
	}
    }
  return (*intersections);
}

const ObjectPrimitive*	RaytracerThread::
getNearestObject(const vector<t_intersected_object>& intersections,
		 double *res)
{
  const ObjectPrimitive	*object;
  int			nbObject;

  object = NULL;
  *res = (res) ? -1 : NULL;
  nbObject = intersections.size();
  if (nbObject > 0)
    {
      for (int i = 0 ; i < nbObject ; i++)
	{
	  int	nbK = intersections[i].k.size();

	  for (int j = 0 ; j < nbK ; j++)
	    if (res && (*res < 0 || intersections[i].k[j] < *res))
	      {
		*res = intersections[i].k[j];
		object = intersections[i].primitive;
	      }
	}
    }
  return (object);
}
