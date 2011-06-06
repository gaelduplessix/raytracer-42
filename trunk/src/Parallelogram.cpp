//
// Parallelogram.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
//
// Made by loick michard
// Login   <michar_l@epitech.net>
//
// Started on  Fri Apr 29 10:41:20 2011 loick michard
// Last update Mon Jun  6 21:26:01 2011 samuel olivier
//

#include <cmath>
#include <vector>
#include "Raytracer.hpp"
#include "Parallelogram.hpp"
#include "EquationSolver.hpp"

Parallelogram::Parallelogram(void) : ObjectPrimitive(NULL, Point(0, 0, 0),
						     Rotation(0, 0, 0),
						     NULL),
				     _vertex1(Point(0, 0, 0)),
				     _vertex2(Point(0, 0, 0)),
				     _textureVertex1(Point(0, 0)),
				     _textureVertex2(Point(0, 1)),
				     _textureVertex3(Point(1, 0))
{
  _isLimited = true;  
}

Parallelogram::Parallelogram(Object*object,
			     const Point& absolutePosition,
			     const Point& vertex1,
			     const Point& vertex2,
			     Material* material,
			     const Point& textureVertex1,
			     const Point& textureVertex2,
			     const Point& textureVertex3) : 
  ObjectPrimitive(object, absolutePosition, Rotation(0, 0, 0), material),
  _vertex1(vertex1), _vertex2(vertex2), _textureVertex1(textureVertex1),
  _textureVertex2(textureVertex2), _textureVertex3(textureVertex3)
{
  setCachedValues();
  _isLimited = true;
}

void            Parallelogram::setCachedValues(void)
{
  _v1 = _vertex1 - _absolutePosition;
  _v2 = _vertex2 - _absolutePosition;
  _var1 = -_v1._z * _v2._x;
  _var2 = _v1._y * _v2._x;
  _var3 = _v1._z * _v2._y;
  _var4 = _v1._x * _v2._z;
  _var5 = _v1._x * _v2._y;
  _var6 = _v1._y * _v2._z;
  _var7 = _v2._x * _absolutePosition._z;
  _var8 = _absolutePosition._x * _v2._z;
  _var9 = _v2._y * _absolutePosition._z;
  _var10 = _v2._x * _absolutePosition._y;
  _var11 = _absolutePosition._y * _v2._z;
  _var12 = _absolutePosition._x * _v2._y;
  _var13 = _v1._z * _absolutePosition._y;
  _var14 = _v1._y * _absolutePosition._z;
  _var15 = _v1._x * _absolutePosition._y;
  _var16 = _v1._z * _absolutePosition._x;
  _var17 = _v1._x * _absolutePosition._z;
  _var18 = _v1._y * _absolutePosition._x;
  _var19 = _v1._z * _v2._y;
  _var20 = _v1._y * _v2._z;
  _var21 = _absolutePosition._x * _v1._z * _v2._y -
    _absolutePosition._x * _v1._y * _v2._z - _v1._x * _v2._y *
    _absolutePosition._z;
  _var22 = _v1._x * _v2._y;
  _var23 = _v1._x * _v2._z;
  _var24 = _v1._x * _absolutePosition._y * _v2._z - _v2._x * _v1._z *
    _absolutePosition._y;
  _var25 = _v2._x * _v1._y;
  _var26 = _v2._x * _v1._z;
  _var27 = _v2._x * _v1._y * _absolutePosition._z;
  _normal = Vector(_v1._y * _v2._z + _v2._y * - _v1._z,
                   _v1._z * _v2._x + _v2._z * - _v1._x,
                   _v1._x * _v2._y + _v2._x * - _v1._y);
  _normal.normalize();
  _textureV1 = _textureVertex2 - _textureVertex1;
  _textureV2 = _textureVertex3 - _textureVertex1;
  _textureV3 = _textureV1 + _textureV2;
  _vertex3 = _absolutePosition + _v1 + _v2;
}

void		Parallelogram::setVertex1(const Point& vertex1)
{
  _vertex1 = vertex1;
  this->setCachedValues();
}

void		Parallelogram::setVertex2(const Point& vertex2)
{
  _vertex2 = vertex2;
  this->setCachedValues();
}

void		Parallelogram::setTextureVertex1(const Point& textureVertex1)
{
  _textureVertex1 = textureVertex1;
}

void		Parallelogram::setTextureVertex2(const Point& textureVertex2)
{
  _textureVertex2 = textureVertex2;
}

void		Parallelogram::setTextureVertex3(const Point& textureVertex3)
{
  _textureVertex3 = textureVertex3;
}

const Point&	Parallelogram::getTextureVertex1(void)
{
  return (_textureVertex1);
}

const Point&	Parallelogram::getTextureVertex2(void)
{
  return (_textureVertex1);
}

const Point&	Parallelogram::getTextureVertex3(void)
{
  return (_textureVertex3);
}

void            Parallelogram::getMappedCoords(const Point& intersectPoint,
					       double& x, double &y) const
{
  double        areaA =
    Triangle::calcArea(_absolutePosition, _vertex1, intersectPoint);
  double        areaB =
    Triangle::calcArea(_vertex1, _vertex3, intersectPoint);
  double        areaC =
    Triangle::calcArea(_vertex3, _vertex2, intersectPoint);
  double        areaD =
    Triangle::calcArea(_vertex2, _absolutePosition, intersectPoint);
  double        sum = areaA + areaB + areaC + areaD;
  sum *= 2;
  double        a = (areaB + areaC) / sum;
  double        b = (areaC + areaD) / sum;
  double        c = (areaD + areaA) / sum;
  double        d = (areaA + areaB) / sum;
  Point         texturePoint = _textureVertex1 +
    (b * _textureV1 + c * _textureV3 + d * _textureV2);

  x = texturePoint._x;
  y = -texturePoint._y;
  cout << x << " " << y << endl;
}

void
Parallelogram::addIntersectionWithRay(const Ray& ray,
				 vector<struct s_intersected_object>&
				 intersection) const
{
  double	D = _var1 * ray._vector._y + _var2 * ray._vector._z
    + ray._vector._x * _var3 + ray._vector._y * _var4
    - ray._vector._z * _var5 - ray._vector._x * _var6;
  double	u = -(-ray._vector._y * _var7 -
		      ray._vector._y * ray._point._x * _v2._z
		      + ray._vector._y * _v2._x * ray._point._z
		      + ray._vector._y * _var8 + ray._vector._x * _var9
		      - ray._vector._x * _v2._y * ray._point._z
		      + ray._vector._z * _var10 - _v2._x * ray._vector._z *
		      ray._point._y + ray._point._x * ray._vector._z * _v2._y +
		      ray._vector._x * ray._point._y * _v2._z
		      - ray._vector._x * _var11 - _var12 * ray._vector._z) / D;
  double	v = (-ray._vector._x * _var13 - ray._vector._x * _v1._y *
		     ray._point._z + ray._vector._x * _v1._z * ray._point._y
		     + ray._vector._x * _var14 + ray._vector._z * _var15 +
		     _v1._y * ray._vector._z * ray._point._x + ray._vector._y
		     * _var16 - ray._vector._z * _v1._x * ray._point._y
		     - ray._vector._y * _var17 - ray._vector._z * _var18
		     + ray._vector._y * _v1._x * ray._point._z - _v1._z *
		     ray._vector._y * ray._point._x) / D;
  double	t = (-ray._point._x * _var19 + ray._point._x * _var20
		     + _var21 + _var22 * ray._point._z - ray._point._y
		     * _var23 + _var24 - _var25 * ray._point._z + _var26
		     * ray._point._y + _var27) / D;
  if (u < 0 || t <= EPSILON || v < 0 || u > 1 || v > 1 || D == 0)
    return ;
  vector<double>       k;
  k.push_back(t);
  intersection.push_back((t_intersected_object){this, k});
}

void	Parallelogram::intersectWithRay(const Ray& ray,
					ObjectPrimitive*& primitive,
					double &res) const
{
  double	D = _var1 * ray._vector._y + _var2 * ray._vector._z
    + ray._vector._x * _var3 + ray._vector._y * _var4
    - ray._vector._z * _var5 - ray._vector._x * _var6;
  double	u = -(-ray._vector._y * _var7 -
		      ray._vector._y * ray._point._x * _v2._z
		      + ray._vector._y * _v2._x * ray._point._z
		      + ray._vector._y * _var8 + ray._vector._x * _var9
		      - ray._vector._x * _v2._y * ray._point._z
		      + ray._vector._z * _var10 - _v2._x * ray._vector._z *
		      ray._point._y + ray._point._x * ray._vector._z * _v2._y +
		      ray._vector._x * ray._point._y * _v2._z
		      - ray._vector._x * _var11 - _var12 * ray._vector._z) / D;
  double	v = (-ray._vector._x * _var13 - ray._vector._x * _v1._y *
		     ray._point._z + ray._vector._x * _v1._z * ray._point._y
		     + ray._vector._x * _var14 + ray._vector._z * _var15 +
		     _v1._y * ray._vector._z * ray._point._x + ray._vector._y
		     * _var16 - ray._vector._z * _v1._x * ray._point._y
		     - ray._vector._y * _var17 - ray._vector._z * _var18
		     + ray._vector._y * _v1._x * ray._point._z - _v1._z *
		     ray._vector._y * ray._point._x) / D;
  double	t = (-ray._point._x * _var19 + ray._point._x * _var20
		     + _var21 + _var22 * ray._point._z - ray._point._y
		     * _var23 + _var24 - _var25 * ray._point._z + _var26
		     * ray._point._y + _var27) / D;
  if (u < 0 || t <= EPSILON || v < 0 || u > 1 || v > 1 || D == 0)
    return ;
  if (t < res || res < 0)
    {
      res = t;
      primitive = (ObjectPrimitive*)this;
    }
}

Vector		Parallelogram::getNormalVector(const Point& intersectPoint,
					       const Vector& viewVector) const
{
  double	cosA = viewVector * _normal;

  cosA = cosA / (viewVector.getNorm());
  if (cosA <= 0)
    return (_normal * -1);
  return (_normal);
  (void)intersectPoint;
}

bool		Parallelogram::isInBoundingBox(BoundingBox& box) const
{
  Point         maxBox = box.getMaxPoint();
  Point         minBox = box.getMinPoint();
  Point max = getMax();
  Point min = getMin();

  if ((max._x > maxBox._x && min._x > maxBox._x) ||
      (max._x < minBox._x && min._x < minBox._x) ||
      (max._y > maxBox._y && min._y > maxBox._y) ||
      (max._y < minBox._y && min._y < minBox._y) ||
      (max._z > maxBox._z && min._z > maxBox._z) ||
      (max._z < minBox._z && min._z < minBox._z))
    return (false);
  return (true);
}

#ifndef MAX
#define MAX(x, y) ((x) > (y)) ? (x) : (y)
#endif
#ifndef MIN
#define MIN(x, y) ((x) < (y)) ? (x) : (y)
#endif

Point           Parallelogram::getMax(void) const
{
  Point		_vertex3 = _absolutePosition + _v1 + _v2;
  return (Point(MAX(MAX(MAX(_vertex1._x, _vertex2._x),
			_absolutePosition._x), _vertex3._x),
		MAX(MAX(MAX(_vertex1._y, _vertex2._y),
			_absolutePosition._y), _vertex3._y),
		MAX(MAX(MAX(_vertex1._z, _vertex2._z),
			_absolutePosition._z), _vertex3._z)));
}

Point           Parallelogram::getMin(void) const
{
  Point         _vertex3 = _absolutePosition + _v1 + _v2;
  return (Point(MIN(MIN(MIN(_vertex1._x, _vertex2._x),
                        _absolutePosition._x), _vertex3._x),
                MIN(MIN(MIN(_vertex1._y, _vertex2._y),
                        _absolutePosition._y), _vertex3._y),
                MIN(MIN(MIN(_vertex1._z, _vertex2._z),
                        _absolutePosition._z), _vertex3._z)));
}
