//
// Triangle.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
//
// Made by loick michard
// Login   <michar_l@epitech.net>
//
// Started on  Fri Apr 29 10:41:20 2011 loick michard
// Last update Mon Oct  8 16:36:43 2012 samuel olivier
//

#include <cmath>
#include <vector>
#include "Raytracer.hpp"
#include "Triangle.hpp"
#include "EquationSolver.hpp"

Triangle::Triangle(Object*object,
		   const Point& absolutePosition,
		   Material* material,
		   const Point& vertex1,
		   const Point& vertex2,
		   const Point& textureVertex1,
		   const Point& textureVertex2,
		   const Point& textureVertex3)
  : ObjectPrimitive(object, absolutePosition, Rotation(0, 0, 0), material),
    _vertex1(vertex1), _vertex2(vertex2), _textureVertex1(textureVertex1),
    _textureVertex2(textureVertex2), _textureVertex3(textureVertex3),
    _normalSet(false)
{
  // cout << _vertex1._x << " " << _vertex1._y << " " << _vertex1._z << endl;
  setCachedValues();
  _isLimited = true;
}

Triangle::Triangle(void):
  ObjectPrimitive(NULL, Point(0, 0, 0), Rotation(0, 0, 0), NULL),
  _vertex1(Point(0, 0, 0)), _vertex2(Point(0, 0, 0)),
  _textureVertex1(Point(0, 0)), _textureVertex2(Point(0.5, 1)),
  _textureVertex3(Point(1, 0)), _normalSet(false)
{
  _isLimited = true;
  _textureVertex1._z = 0;
  _textureVertex2._z = 0;
  _textureVertex3._z = 0;
}

void		Triangle::setCachedValues(void)
{
  _textureVertex1._z = 0;
  _textureVertex2._z = 0;
  _textureVertex3._z = 0;
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
}

void		Triangle::setVertex1(const Point& vertex1)
{
  _vertex1 = vertex1;
}

void		Triangle::setVertex2(const Point& vertex2)
{
  _vertex2 = vertex2;
}

Point		Triangle::getVertex1(void)
{
  return (_vertex1);
}

Point		Triangle::getVertex2(void)
{
  return (_vertex2);
}

void		Triangle::setTextureVertex1(const Point& textureVertex1)
{
  _textureVertex1 = textureVertex1;
  _textureVertex1._z = 0;
}

void		Triangle::setTextureVertex2(const Point& textureVertex2)
{
  _textureVertex2 = textureVertex2;
  _textureVertex2._z = 0;
}

void		Triangle::setTextureVertex3(const Point& textureVertex3)
{
  _textureVertex3 = textureVertex3;
  _textureVertex3._z = 0;
}

const Point& 	Triangle::getTextureVertex1(void)
{
  return (_textureVertex1);
}

const Point& 	Triangle::getTextureVertex2(void)
{
  return (_textureVertex1);
}

const Point& 	Triangle::getTextureVertex3(void)
{
  return (_textureVertex3);
}

void		Triangle::setNormal(const Point& normal)
{
  _normal = normal;
}

double		Triangle::calcArea(const Point& vertex1,
				   const Point& vertex2,
				   const Point& vertex3)
{
  Vector	a = vertex1 - vertex2;
  Vector	b = vertex1 - vertex3;
  double	na = a.getNorm();
  double	nb = b.getNorm();
  double	cosA = (a * b) / (na * nb);

  cosA = acos(cosA);
  return (0.5 * na * nb * sin(cosA));
}

void		Triangle::getMappedCoords(const Point& intersectPoint,
					  double& x, double &y) const
{
  double	areaA = calcArea(_absolutePosition, _vertex1, intersectPoint);
  double	areaB = calcArea(_vertex1, _vertex2, intersectPoint);
  double	areaC = calcArea(_vertex2, _absolutePosition, intersectPoint);
  double	sum = areaA + areaB + areaC;
  double	b = areaC / sum;
  double	c = areaA / sum;
  double	a = areaB / sum;
  Point		texturePoint = _textureVertex1 +
    (b * _textureV1 + c * _textureV2) / (a + b + c);

  x = texturePoint._x;
  y = -texturePoint._y;
}

void
Triangle::addIntersectionWithRay(const Ray& ray,
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

  if (u < 0 || t <= EPSILON || v < 0 || u + v > 1 || D == 0)
    return ;
  vector<double>       k;
  k.push_back(t);
  intersection.push_back((t_intersected_object){this, k});
}

void                  Triangle::intersectWithRay(const Ray& ray,
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

  if (u < 0 || t <= EPSILON || v < 0 || u + v > 1 || D == 0)
    return ;
  if (t < res || res < 0)
    {
      res = t;
      primitive = (ObjectPrimitive*)this;
    }
}

Vector		Triangle::getNormalVector(const Point& intersectPoint,
					const Vector& viewVector) const
{
  if (_normalSet == false)
    {
      double	cosA = viewVector * _normal;

      cosA = cosA / (viewVector.getNorm());
      if (cosA <= 0)
	return (_normal * -1);
      return (_normal);
      (void)intersectPoint;
    }
  else
    {
      double
	aT = calcArea(_absolutePosition, _vertex1, _vertex2),
	aB = calcArea(intersectPoint, _absolutePosition, _vertex1),
	aC = calcArea(intersectPoint, _vertex2, _vertex1),
	aA = aT - aB - aC;
      double
	c1 = aA / aT,
	c2 = aB / aT,
	c3 = aC / aT;
      Vector	normal = _normal0 * c3 + _normal1 * c1 + _normal2 * c2;
      normal.normalize();
      return (normal);
    }
}

#ifndef MAX
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#endif
#ifndef MIN
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#endif

bool		Triangle::isInBoundingBox(BoundingBox& box) const
{
  Point		maxBox = box.getMaxPoint();
  Point		minBox = box.getMinPoint();
  double	maxX = MAX(MAX(_vertex1._x, _vertex2._x),
			   _absolutePosition._x);
  double        maxY = MAX(MAX(_vertex1._y, _vertex2._y),
                           _absolutePosition._y);
  double        maxZ = MAX(MAX(_vertex1._z, _vertex2._z),
                           _absolutePosition._z);
  double        minX = MIN(MIN(_vertex1._x, _vertex2._x),
                           _absolutePosition._x);
  double        minY = MIN(MIN(_vertex1._y, _vertex2._y),
                           _absolutePosition._y);
  double        minZ = MIN(MIN(_vertex1._z, _vertex2._z),
                           _absolutePosition._z);

  Point		box1(minX, minY, minZ);
  Point		box2(maxX, maxY, maxZ);

  // Point		boxVertexes[8] =
  //   {
  //     Point(minBox._x, minBox._y, minBox._z),
  //     Point(minBox._x, minBox._y, maxBox._z),
  //     Point(minBox._x, maxBox._y, minBox._z),
  //     Point(minBox._x, maxBox._y, maxBox._z),
  //     Point(maxBox._x, minBox._y, minBox._z),
  //     Point(maxBox._x, minBox._y, maxBox._z),
  //     Point(maxBox._x, maxBox._y, minBox._z),
  //     Point(maxBox._x, maxBox._y, maxBox._z),
  //   };
  // Point	c((minBox._x + maxBox._x) / 2,
  // 	  (minBox._y + maxBox._y) / 2,
  // 	  (minBox._z + maxBox._z) / 2);
  // Point v0 = _absolutePosition - c,
  //   v1 = _vertex1 - c,
  //   v2 = _vertex2 - c;
  // Vector u = v1 - v0;
  // Vector v = v2 - v0;
  // c = Point();
  // Vector e[3] =
  //   {
  //     Vector(1, 0, 0),
  //     Vector(0, 1, 0),
  //     Vector(0, 0, 1),
  //   };
  // Vector f[3] =
  //   {
  //     v1 - v0,
  //     v2 - v1,
  //     v0 - v2,
  //   };
  // Vector axes[13] =
  //   {
  //     e[0],
  //     e[1],
  //     e[2],
  //     u^v,
  //     Vector(),
  //     Vector(),
  //     Vector(),
  //     Vector(),
  //     Vector(),
  //     Vector(),
  //     Vector(),
  //     Vector(),
  //     Vector(),
  //   };
  
  // for (int i = 0; i < 3; ++i)
  //   for (int j = 0; j < 3; ++j)
  //     axes[4 + i * 3 + j] = e[i]^f[j];
  // for (int i = 0; i < 13; ++i)
  //   {
  //     Vector	axe = axes[i];
  //     axe.normalize();
  //     double	min1 = axe * boxVertexes[0],
  // 	max1 = min1,
  // 	min2 = axe * v0,
  // 	max2 = min2;
  //     for (int j = 1; j < 8; ++j)
  // 	{
  // 	  double p = axe * boxVertexes[j];

  // 	  if (p < min1)
  // 	    min1 = p;
  // 	  else if (p > max1)
  // 	    max1 = p;
  // 	}
  //     double p = axe * v1;
  //     if (p < min2)
  // 	min2 = p;
  //     else if (p > max2)
  // 	max2 = p;
  //     p = axe * v2;
  //     if (p < min2)
  // 	min2 = p;
  //     else if (p > max2)
  // 	max2 = p;
  //     if (min1 > max2 || max1 < min2)
  // 	return (false);
  //   }
  // return (true);

  if(box1._x <= maxBox._x && box2._x >= minBox._x &&
     box1._y <= maxBox._y && box2._y >= minBox._y &&
     box1._z <= maxBox._z && box2._z >= minBox._z)
    return (true);
  return (false);
}

Point		Triangle::getMax(void) const
{
  return (Point(MAX(MAX(_vertex1._x, _vertex2._x),
		    _absolutePosition._x),
		MAX(MAX(_vertex1._y, _vertex2._y),
		    _absolutePosition._y),
		MAX(MAX(_vertex1._z, _vertex2._z),
		    _absolutePosition._z)));
}

Point           Triangle::getMin(void) const
{
  return (Point(MIN(MIN(_vertex1._x, _vertex2._x),
                    _absolutePosition._x),
                MIN(MIN(_vertex1._y, _vertex2._y),
                    _absolutePosition._y),
                MIN(MIN(_vertex1._z, _vertex2._z),
                    _absolutePosition._z)));
}

void		Triangle::setNormals(const Point& n0, const Point& n1,
				    const Point& n2)
{
  _normalSet = true;
  _normal0 = n0;
  _normal1 = n1;
  _normal2 = n2;
  _normal0.normalize();
  _normal1.normalize();
  _normal2.normalize();
}
