//
// ObjectPrimitive.hpp for raytracer in /home/jochau_g//dev/c/raytracer/raytracer-42
//
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
//
// Started on  Tue Apr 26 17:15:41 2011 gael jochaud-du-plessix
// Last update Sat May 21 19:29:53 2011 loick michard
//

#ifndef _OBJECTPRIMITIVE_HPP_
#define _OBJECTPRIMITIVE_HPP_

#include <vector>
#include <stack>
#include "Vector.hpp"
#include "Point.hpp"
#include "Rotation.hpp"
#include "Ray.hpp"
#include "Material.hpp"

using namespace std;

class Object;
class BoundingBox;
struct s_intersected_object;

class ObjectPrimitive
{
public:
  ObjectPrimitive(void);
  ObjectPrimitive(Object *object,
		  const Point& absolutePosition,
		  const Rotation& rotation,
		  const Material& material);

  Object*		getObject(void) const;
  const Point&		getPosition(void) const;
  const Rotation&	getRotation(void) const;
  const Material&	getMaterial(void) const;

  void		setObject(Object *object);
  void		setPosition(const Point& position);
  void		setRotation(const Rotation& rotation);
  void		setMaterial(const Material& material);

  bool		isLimited(void);
  Color		getColor(const Point& intersectPoint) const;
  virtual void 	getMappedCoords(const Point& intersectPoint,
				double& x, double &y) const = 0;

  virtual void	addIntersectionWithRay(const Ray& ray,
				       vector<struct s_intersected_object>&
				       intersection) const = 0;
  virtual void
  intersectWithRay(const Ray& ray, ObjectPrimitive*& primitive,
		   double &res) const = 0;

  Vector		getNormal(const Point& intersectPoint,
				  const Vector& viewVector) const;
  virtual Vector	getNormalVector(const Point& intersectPoint,
					const Vector& viewVector) const = 0;
  virtual bool		isInBoundingBox(BoundingBox& box) const = 0;

  Vector		getReflectedVector(const Point& intersectPoint,
					   const Vector& vector,
					   bool doNormalize=false) const;
  Ray		getRefractedRay(const Point& intersectPoint,
				const Ray& ray,
				stack<ObjectPrimitive*>& refractivePath) const;

  virtual Point	getMax(void) const;
  virtual Point	getMin(void) const;

protected:
  virtual Ray			getRayAtSimplePosition(const Ray& ray) const;
  Point		_absolutePosition;
  Rotation	_rotation;
  Material	_material;
  Object*	_object;
  bool		_isLimited;
};

#endif
