//
// Raytracer.hpp for raytracer in /home/michar_l//Raytracer
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Tue Apr 26 12:24:26 2011 loick michard
// Last update Mon Jun  6 22:17:29 2011 gael jochaud-du-plessix
// Last update Sat May 21 16:49:29 2011 gael jochaud-du-plessix
//

#ifndef _RAYTRACER_HPP_
#define _RAYTRACER_HPP_

#define EPSILON 1e-5

#include <QMutex>
#include <QMutexLocker>
#include <QByteArray>

#include <stack>
#include <vector>

#include "Scene.hpp"
#include "RenderingConfiguration.hpp"
#include "RenderingInterface.hpp"
#include "RaytracerThread.hpp"
#include "PhotonMap.hpp"
#include "KdTree.hpp"

typedef struct			s_intersected_object
{
  const ObjectPrimitive*        primitive;
  vector<double>                k;
}				t_intersected_object;

class	Raytracer
{
public:

  const static int	NO_SCENE_SPECIFIED = 0;
  const static int	NO_CONFIG_SPECIFIED = 1;
  const static int	NO_INTERFACE_SPECIFIED = 2;
  const static double	EPSILON_REFLECTION = 1e-2;
  const static double	EPSILON_REFRACTION = 1e-2;

  Raytracer();
  Raytracer(Scene* scene,
	    RenderingConfiguration* config,
	    RenderingInterface* interface, PhotonMap* photonMap);
  ~Raytracer();

  void setScene(Scene& scene);
  void setPhotonMap(PhotonMap& photonMap);
  void setRenderingConfiguration(RenderingConfiguration* config);
  void setRenderingInterface(RenderingInterface* interface);

  const Scene*			getScene(void) const;
  const PhotonMap*		getPhotonMap(void) const;
  const RenderingConfiguration*	getRenderingConfiguration(void) const;
  RenderingInterface*		getRenderingInterface(void) const;

  QByteArray	saveState(void);
  void		restoreState(QByteArray& data);

  bool	isPixelRaytraced(int x, int y);

  void launchRendering();
  void stopRendering();
  void pauseRendering();

  double	getProgress() const;

  Color		throwRay(Ray& ray);
  Color		renderPixel(double x, double y);
  void		renderingLoop(double& progress, RaytracerSubThread* thread);
  const Camera&	getCurrentCamera(void);
  Point		getPixelToRender(RaytracerSubThread* thread) const;

  void	getIntersectingObjects(const Ray& ray,
			       vector<t_intersected_object>&
			       intersection) const;
  ObjectPrimitive*
  getNearestObject(Ray& ray, double& res) const;

  void	calcLightForObject(const ObjectPrimitive& object,
			   const Point& intersectPoint,
			   const Vector& viewRay,
			   Color& directLight,
			   Color& specularLight) const;

  Color	calcAmbiantOcclusion(const ObjectPrimitive* nearestObject,
			     const Point& intersectPoint,
			     Ray& ray, double& coef);
  Color	calcDiffusedReflection(Ray& ray,
			       const ObjectPrimitive* nearestObject);
  Color	calcReflectedLight(const ObjectPrimitive* nearestObject,
			   const Point& intersectPoint,
			   Ray& ray);
  Color	calcTransmetedLight(const ObjectPrimitive* nearestObject,
			    const Point& intersectPoint,
			    Ray& ray);

  Color	calcDirectLight(Ray& ray);

  void	getNearestPhoton(vector<Photon*>& nearest, int size,
			 const Point& intersectPoint, int n);
  Color	calcAmbiantLight(const Point& intersectPoint);

  void	deleteKdTree();

  stack<ObjectPrimitive*>	_refractivePath;
  PhotonMap*			_photonMap;
  KdTree*			_kdTree;
  Scene*			_scene;
  RaytracerThread*		_thread;

private:
  RenderingConfiguration*	_config;
  RenderingInterface*		_interface;
  mutable QMutex		_mutex;
  bool				_otherEyes;
};

#endif
