//
// SceneObject.cpp for  in /home/laplan_m/Src/Epitech/Projects/C++/raytracer-42
//
// Made by melvin laplanche
// Login   <laplan_m@epitech.net>
//
// Started on  Wed May 11 17:09:06 2011 melvin laplanche
// Last update Tue May 31 00:52:49 2011 melvin laplanche
//

#include "Scene.hpp"

bool			Scene::_parseCommonElement(QDomNode	    n,
						   ObjectPrimitive* prime,
						   bool&	    position,
						   bool&	    rotation)
{
  if (n.nodeName() == "position")
  {
    if (position)
      this->_putWarning(QObject::tr("An element has several position, "
				    "the first defined will be used"), n);
    else
    {
      prime->setPosition(_parsePosition(n, "position"));
      position = true;
    }
  }
  else if (n.nodeName() == "rotation")
  {
    if (rotation)
      this->_putWarning(QObject::tr("An element has several rotation, "
				    "the first defined will be used"), n);
    else
    {
      prime->setRotation(_parseRotation(n));
      rotation = true;
    }
  }
  else
    return false;
  return true;
}

EquationPrimitive*		Scene::_parseEquation(QDomNode n,
						      QString  material,
						      Object*  obj)
{
  Material*			mat = this->_getMaterialByName(material);
  bool				position = false;
  Point				positionValue;
  bool				rotation = false;
  Rotation			rotationValue;
  string			equationValue;
  bool				equation = false;
  EquationPrimitive		*ret;
  QDomNode			equationNode;

  while (n.isNull() == false && this->_hasError == false)
  {
    if (n.isComment() == false)
    {
      if (n.hasChildNodes() == false || n.isElement() == false)
      {
	this->_putError(QObject::tr("Every primitive children must be "
				    "an element"), n);
	return NULL;
      }
      if (n.nodeName() == "position")
      {
	if (position)
	  this->_putWarning(QObject::tr("An equation has several position, "
					"the first defined will be used"), n);
	else
	{
	  positionValue = _parsePosition(n, "position");
	  position = true;
	}
      }
      else if (n.nodeName() == "rotation")
      {
	if (rotation)
	  this->_putWarning(QObject::tr("An equation has several rotation, "
					"the first defined will be used"), n);
	else
	{
	  rotationValue = _parseRotation(n);
	  rotation = true;
	}
      }
      else if (n.nodeName() == "equation")
      {
	if (equation)
	  this->_putWarning(QObject::tr("An equation has several equation, "
					"the first defined will be used"), n);
	else
	{
	  equationNode = n;
	  if (this->_checkContentIsSingleText(n, "equation"))
	    equationValue = n.toElement().text().toStdString();
	  equation = true;
	}
      }
      else
	this->_putWarning(QObject::tr("Unknown element %1").arg(n.nodeName()),
			  n);
    }
    n = n.nextSibling();
  }
  if (!equation || !position || !rotation)
  {
    this->_putError(QObject::tr("A equation must have a position, a rotation "
				"and an equation"), n);
    return NULL;
  }
  try
  {
    cerr << "equation try" << endl;
    ret =  new EquationPrimitive(equationValue, obj,
				 positionValue, rotationValue, mat);
    cerr << "equation try over" << endl;
  }
  catch (int error)
  {
    cerr << "equation catch" << endl;
    this->_putError(QObject::tr("The equation is not valid"), equationNode);
    ret = NULL;
  }
  return ret;
}

void			Scene::_parseSett(QDomNode n,
					  QString  material)
{
  Material*			mat = this->_getMaterialByName(material);
  bool				position = false;
  Point				positionValue;
  bool				rotation = false;
  Rotation			rotationValue(0,0,0);
  bool				solidValue = false;
  bool				solid = false;
  Point				widthValue;
  bool				width = false;
  Point				heightValue;
  bool				height = false;
  Point				depthValue;
  bool				depth = false;

  while (n.isNull() == false && this->_hasError == false)
  {
    if (n.isComment() == false)
    {
      if (n.hasChildNodes() == false || n.isElement() == false)
      {
	this->_putError(QObject::tr("Every primitive children must be an "
				    "element"), n);
	return ;
      }
      if (n.nodeName() == "position")
      {
	if (position)
	  this->_putWarning(QObject::tr("An parallelepipede has several"
					" position, the first defined will "
					"be used"), n);
	else
	{
	  positionValue = _parsePosition(n, "position");
	  position = true;
	}
      }
      else if (n.nodeName() == "width")
      {
	if (width)
	  this->_putWarning(QObject::tr("An parallelepipede has several "
					"width, "
					"the first defined will be used"), n);
	else
	{
	  widthValue = _parsePosition(n, "width");
	  width = true;
	}
      }
      else if (n.nodeName() == "depth")
      {
	if (depth)
	  this->_putWarning(QObject::tr("An parallelepipede has several "
					"depth, "
					"the first defined will be used"), n);
	else
	{
	  depthValue = _parsePosition(n, "depth");
	  depth = true;
	}
      }
      else if (n.nodeName() == "height")
      {
	if (height)
	  this->_putWarning(QObject::tr("An parallelepipede has several "
					"height, "
					"the first defined will be used"), n);
	else
	{
	  heightValue = _parsePosition(n, "height");
	  height = true;
	}
      }
      else if (n.nodeName() == "rotation")
      {
	if (rotation)
	  this->_putWarning(QObject::tr("An parallelepipede has several "
					"rotation, "
					"the first defined will be used"), n);
	else
	{
	  rotationValue = _parseRotation(n);
	  rotation = true;
	}
      }
      else if (n.nodeName() == "solid")
      {
	if (solid)
	  this->_putWarning(QObject::tr("An parallelepipede has several "
					"equation, "
					"the first defined will be used"), n);
	else
	{
	  solidValue = this->_parseBoolean(n, "solid");
	  solid = true;
	}
      }
      else
	this->_putWarning(QObject::tr("Unknown element %1").arg(n.nodeName()),
			  n);
    }
    n = n.nextSibling();
  }
  if (!position || !solid || !width || !height || !depth)
    this->_putError(QObject::tr("A parallelepipede must have a position, a "
				"width, a height, a depth, "
				"and an solid value"), n);
  else
    this->_objects.push_back(new Sett(positionValue, solidValue, widthValue,
				      heightValue, depthValue, mat,
				      rotationValue));
}

Sphere*			Scene::_parseSphere(QDomNode	n,
					    QString	material,
					    Object*	obj)
{
  bool				position = false;
  bool				rotation = false;
  bool				radius = false;
  Sphere			*sphere = new Sphere();

  while (n.isNull() == false && this->_hasError == false)
  {
    if (n.isComment() == false)
    {
      if (n.hasChildNodes() == false || n.isElement() == false)
      {
	this->_putError(QObject::tr("Every primitive children must be an "
				    "element"), n);
	return NULL;
      }
      if (this->_parseCommonElement(n, sphere, position, rotation) == false)
      {
	if (n.nodeName() == "radius")
	{
	  if (radius)
	    this->_putWarning(QObject::tr("A sphere has several radius, "
					  "the first defined will be used"),
			      n);
	  else
	  {
	    sphere->setRadius(_parseDouble(n, 0, 0, "radius"));
	    radius = true;
	  }
	}
	else
	  this->_putWarning(QObject::tr("Unknown element %1")
			    .arg(n.nodeName()),
			    n);
      }
    }
    n = n.nextSibling();
  }
  if (!radius || !position || !rotation)
  {
    this->_putError(QObject::tr("A sphere must have a position, "
				"rotation and a radius"), n);
    return NULL;
  }
  sphere->setMaterial(_getMaterialByName(material));
  sphere->setObject(obj);
  return sphere;
}

CubeTroue*			Scene::_parseCubeTroue(QDomNode	n,
						       QString	material,
						       Object*	obj)
{
  bool				position = false;
  bool				rotation = false;
  bool				coeff = false;
  CubeTroue			*cube = new CubeTroue();

  while (n.isNull() == false && this->_hasError == false)
  {
    if (n.isComment() == false)
    {
      if (n.hasChildNodes() == false || n.isElement() == false)
      {
	this->_putError(QObject::tr("Every primitive children must be "
				    "an element"), n);
	return NULL;
      }
      if (this->_parseCommonElement(n, cube, position, rotation) == false)
      {
	if (n.nodeName() == "coeff")
	{
	  if (coeff)
	    this->_putWarning(QObject::tr("A cube has several coeff, "
					  "the first defined will be used"),
			      n);
	  else
	  {
	    cube->setCoeff(_parseDouble(n, 0, 0, "coeff"));
	    coeff = true;
	  }
	}
	else
	  this->_putWarning(QObject::tr("Unknown element %1")
			    .arg(n.nodeName()),
			    n);
      }
    }
    n = n.nextSibling();
  }
  if (!position || !rotation || !coeff)
  {
    this->_putError(QObject::tr("A cube must have a position, rotation "
				"and a coeff"), n);
    return NULL;
  }
  cube->setMaterial(_getMaterialByName(material));
  cube->setObject(obj);
  return cube;
}

Triangle*			Scene::_parseTriangle(QDomNode	n,
						      QString	material,
						      Object*	obj)
{
  bool				position = false;
  bool				rotation = false;
  bool				vert1 = false;
  bool				vert2 = false;
  bool				textVert1 = false;
  bool				textVert2 = false;
  bool				textVert3 = false;
  Triangle			*triangle = new Triangle();

  while (n.isNull() == false && this->_hasError == false)
  {
    if (n.isComment() == false)
    {
      if (n.hasChildNodes() == false || n.isElement() == false)
      {
	this->_putError(QObject::tr("Every primitive children must be "
				    "an element"), n);
	return NULL;
      }
      if (this->_parseCommonElement(n, triangle, position, rotation) == false)
      {
	if (n.nodeName() == "vector1" || n.nodeName() == "point2")
	{
	  if (vert1)
	    this->_putWarning(QObject::tr("A triangle has several "
					  "vector1/point2, "
					  "the first defined will be used"),
			      n);
	  else if (n.nodeName() == "vector1" && position == false)
	    this->_putWarning(QObject::tr("A position must be defined before"
					  "you can define a vector1"),
			      n);
	  else
	  {
	    if (n.nodeName() == "vector1")
	      triangle->setVertex1(_parsePosition(n, "vector1") +
				   triangle->getPosition());
	    else
	      triangle->setVertex1(_parsePosition(n, "point2"));
	    vert1 = true;
	  }
	}
	else if (n.nodeName() == "vector2" || n.nodeName() == "point3")
	{
	  if (vert2)
	    this->_putWarning(QObject::tr("A triangle has several "
					  "vector2/point3, "
					  "the first defined will be used"),
			      n);
	  else if (n.nodeName() == "vector2" && position == false)
	    this->_putWarning(QObject::tr("A position must be defined before"
					  "you can define a vector2"),
			      n);
	  else
	  {
	    if (n.nodeName() == "vector2")
	      triangle->setVertex2(_parsePosition(n, "vector2") +
				   triangle->getPosition());
	    else
	      triangle->setVertex2(_parsePosition(n, "point3"));
	    vert2 = true;
	  }
	}
	else if (n.nodeName() == "textureVertex1")
	{
	  if (textVert1)
	    this->_putWarning(QObject::tr("An element has several "
					  "textureVertex1, "
					  "the first defined will be used"),
			      n);
	  else
	  {
	    triangle->setTextureVertex1(_parsePosition(n, "textureVertex1"));
	    textVert1 = true;
	  }
	}
	else if (n.nodeName() == "textureVertex2")
	{
	  if (textVert2)
	    this->_putWarning(QObject::tr("An element has several "
					  "textureVertex2, "
					  "the first defined will be used"),
			      n);
	  else
	  {
	    triangle->setTextureVertex2(_parsePosition(n, "textureVertex2"));
	    textVert2 = true;
	  }
	}
	else if (n.nodeName() == "textureVertex3")
	{
	  if (textVert3)
	    this->_putWarning(QObject::tr("An element has several "
					  "textureVertex3, "
					  "the first defined will be used"),
			      n);
	  else
	  {
	    triangle->setTextureVertex3(_parsePosition(n, "textureVertex3"));
	    textVert3 = true;
	  }
	}
	else
	  this->_putWarning(QObject::tr("Unknown element %1").
			    arg(n.nodeName()),
			    n);
      }
    }
    n = n.nextSibling();
  }
  if (!position || !vert1 || !vert2)
  {
    this->_putError(QObject::tr("A triangle must have a position,"
				" a vertex1 and a vertext2"), n);
    return NULL;
  }
  triangle->setMaterial(_getMaterialByName(material));
  triangle->setObject(obj);
  triangle->setCachedValues();
  return triangle;
}

Parallelogram*			Scene::_parseParallelogram(QDomNode n,
							   QString  material,
							   Object*  obj)
{
  bool				p1 = false;
  bool				rotation = false;
  bool				p2 = false;
  bool				p3 = false;
  bool				textVert1 = false;
  bool				textVert2 = false;
  bool				textVert3 = false;
  Parallelogram			*para = new Parallelogram();

  while (n.isNull() == false && this->_hasError == false)
  {
    if (n.isComment() == false)
    {
      if (n.hasChildNodes() == false || n.isElement() == false)
      {
	this->_putError(QObject::tr("Every primitive children must be "
				    "an element"), n);
	return NULL;
      }
      if (this->_parseCommonElement(n, para, p1, rotation) == false)
      {
	if (n.nodeName() == "point2" || n.nodeName() == "vector1")
	{
	  if (p2)
	    this->_putWarning(QObject::tr("A parallelogram has several "
					  "point2/vertor1, "
					  "the first defined will be used"),
			      n);
	  else if (n.nodeName() == "vector1" && p1 == false)
	    this->_putError(QObject::tr("Before defining a vector1, you must "
					"define a position"), n);
	  else
	  {
	    if (n.nodeName() == "point2")
	      para->setVertex1(_parsePosition(n, "point2"));
	    else
	      para->setVertex1(_parsePosition(n, "vector1")
			       + para->getPosition());
	    p2 = true;
	  }
	}
	else if (n.nodeName() == "point3" || n.nodeName() == "vector2")
	{
	  if (p3)
	    this->_putWarning(QObject::tr("A parallelogram has several "
					  "point3/vertor2, "
					  "the first defined will be used"),
			      n);
	  else if (n.nodeName() == "vector2" && p1 == false)
	    this->_putError(QObject::tr("Before defining a vector2, you must "
					"define a position"), n);
	  else
	  {
	    if (n.nodeName() == "point3")
	      para->setVertex2(_parsePosition(n, "point3"));
	    else
	      para->setVertex2(_parsePosition(n, "vector2")
			       + para->getPosition());
	    p3 = true;
	  }
	}
	else if (n.nodeName() == "textureVertex1")
	{
	  if (textVert1)
	    this->_putWarning(QObject::tr("An element has several "
					  "textureVertex1, "
					  "the first defined will be used"),
			      n);
	  else
	  {
	    para->setTextureVertex1(_parsePosition(n, "textureVertex1"));
	    textVert1 = true;
	  }
	}
	else if (n.nodeName() == "textureVertex2")
	{
	  if (textVert2)
	    this->_putWarning(QObject::tr("An element has several "
					  "textureVertex2, "
					  "the first defined will be used"),
			      n);
	  else
	  {
	    para->setTextureVertex2(_parsePosition(n, "textureVertex2"));
	    textVert2 = true;
	  }
	}
	else if (n.nodeName() == "textureVertex3")
	{
	  if (textVert3)
	    this->_putWarning(QObject::tr("An element has several "
					  "textureVertex3, "
					  "the first defined will be used"),
			      n);
	  else
	  {
	    para->setTextureVertex3(_parsePosition(n, "textureVertex3"));
	    textVert3 = true;
	  }
	}
	else
	  this->_putWarning(QObject::tr("Unknown element %1")
			    .arg(n.nodeName()),
			    n);
      }
    }
    n = n.nextSibling();
  }
  if (!p1 || !p2 || !p3)
  {
    this->_putError(QObject::tr("A parallelogram must have a position, "
				"a vertex1 and a vertext2"), n);
    return NULL;
  }
  para->setMaterial(_getMaterialByName(material));
  para->setObject(obj);
  para->setCachedValues();
  return para;
}

Cone*			Scene::_parseCone(QDomNode	n,
					  QString	material,
					  Object*	obj)
{
  bool				position = false;
  bool				rotation = false;
  bool				min = false;
  bool				max = false;
  bool				radius = false;
  Cone				*cone = new Cone();

  while (n.isNull() == false && this->_hasError == false)
  {
    if (n.isComment() == false)
    {
      if (n.hasChildNodes() == false || n.isElement() == false)
      {
	this->_putError(QObject::tr("Every primitive children must be an "
				  "element"), n);
	return NULL;
      }
      if (this->_parseCommonElement(n, cone, position, rotation) == false)
      {
	if (n.nodeName() == "radius")
	{
	  if (radius)
	    this->_putWarning(QObject::tr("A cone has several radius, "
					  "the first defined will be used"),
			      n);
	  else
	  {
	    cone->setAngle(_parseDouble(n, 0, 0, "angle"));
	    radius = true;
	  }
	}
	else if (n.nodeName() == "limitMin")
	{
	  if (min)
	    this->_putWarning(QObject::tr("A cone has several limitMin, "
					  "the first defined will be used"),
			      n);
	  else
	  {
	    cone->setLimitMin(_parseDouble(n, 0, 0, "limitMin"));
	    min = true;
	  }
	}
	else if (n.nodeName() == "limitMax")
	{
	  if (max)
	    this->_putWarning(QObject::tr("A cone has several limitMax, "
					  "the first defined will be used"),
			      n);
	  else
	  {
	    cone->setLimitMax(_parseDouble(n, 0, 0, "limitMax"));
	    max = true;
	  }
	}
	else
	  this->_putWarning(QObject::tr("Unknown element %1")
			    .arg(n.nodeName()),
			    n);
      }
    }
    n = n.nextSibling();
  }
  if (!position || !rotation || !radius)
  {
    this->_putError(QObject::tr("A cone must have a position, a rotation, "
				"and a radius"), n);
    return NULL;
  }
  cone->setMaterial(_getMaterialByName(material));
  cone->setObject(obj);
  return cone;
}

Cylinder*			Scene::_parseCylinder(QDomNode	n,
						      QString	material,
						      Object*	obj)
{
  bool				position = false;
  bool				rotation = false;
  bool				min = false;
  bool				max = false;
  bool				radius = false;
  Cylinder			*cylinder = new Cylinder();

  while (n.isNull() == false && this->_hasError == false)
  {
    if (n.isComment() == false)
    {
      if (n.hasChildNodes() == false || n.isElement() == false)
      {
	this->_putError(QObject::tr("Every primitive children must be an "
				    "element"), n);
	return NULL;
      }
      if (this->_parseCommonElement(n, cylinder, position, rotation) == false)
      {
	if (n.nodeName() == "radius")
	{
	  if (radius)
	    this->_putWarning(QObject::tr("A cylinder has several radius, "
					  "the first defined will be used"),
			      n);
	  else
	  {
	    cylinder->setRadius(_parseDouble(n, 0, 0, "radius"));
	    radius = true;
	  }
	}
	else if (n.nodeName() == "limitMin")
	{
	  if (min)
	    this->_putWarning(QObject::tr("A cylinder has several limitMin, "
					  "the first defined will be used"),
			      n);
	  else
	  {
	    cylinder->setLimitMin(_parseDouble(n, 0, 0, "limitMin"));
	    min = true;
	  }
	}
	else if (n.nodeName() == "limitMax")
	{
	  if (max)
	  this->_putWarning(QObject::tr("A cylinder has several limitMax, "
					"the first defined will be used"), n);
	  else
	  {
	    cylinder->setLimitMax(_parseDouble(n, 0, 0, "limitMax"));
	    max = true;
	  }
	}
	else
	  this->_putWarning(QObject::tr("Unknown element %1")
			    .arg(n.nodeName()),
			    n);
      }
    }
    n = n.nextSibling();
  }
  if (!position || !rotation || !radius)
  {
    this->_putError(QObject::tr("A cylinder must have a position, a rotation, "
				"and a radius"), n);
    return NULL;
  }
  cylinder->setMaterial(_getMaterialByName(material));
  cylinder->setObject(obj);
  return cylinder;
}

Plane*			Scene::_parsePlane(QDomNode	n,
					   QString	material,
					   Object*	obj)
{
  bool				position = false;
  bool				rotation = false;
  bool				x = false;
  bool				y = false;
  Plane				*plane = new Plane();

  while (n.isNull() == false && this->_hasError == false)
  {
    if (n.isComment() == false)
    {
      if (n.hasChildNodes() == false || n.isElement() == false)
      {
	this->_putError(QObject::tr("Every primitive children must be "
				    "an element"), n);
	return NULL;
      }
      if (this->_parseCommonElement(n, plane, position, rotation) == false)
      {
	if (n.nodeName() == "limitX")
	{
	  if (x)
	    this->_putWarning(QObject::tr("A plane has several limitX, "
					  "the first defined will be used"),
			      n);
	  else
	  {
	    plane->setLimitX(_parseDouble(n, 0, 0, "limitX"));
	    x = true;
	  }
	}
	else if (n.nodeName() == "limitY")
	{
	  if (y)
	    this->_putWarning(QObject::tr("A plane has several limitY, "
					  "the first defined will be used"),
			      n);
	  else
	  {
	    plane->setLimitY(_parseDouble(n, 0, 0, "limitY"));
	    y = true;
	  }
	}
	else
	  this->_putWarning(QObject::tr("Unknown element %1")
			    .arg(n.nodeName()),
			    n);
      }
    }
    n = n.nextSibling();
    }
  if (!position || !rotation)
  {
    this->_putError(QObject::tr("A plane must have a position and a rotation"),
		    n);
    return NULL;
  }
  plane->setMaterial(_getMaterialByName(material));
  plane->setObject(obj);
  return plane;
}

Torus*			Scene::_parseTorus(QDomNode	n,
					   QString	material,
					   Object*	obj)
{
  bool				position = false;
  bool				rotation = false;
  bool				minor = false;
  bool				major = false;
  Torus				*torus = new Torus();

  while (n.isNull() == false && this->_hasError == false)
  {
    if (n.isComment() == false)
    {
      if (n.hasChildNodes() == false || n.isElement() == false)
      {
	this->_putError(QObject::tr("Every primitive children must be "
				    "an element"), n);
	return NULL;
      }
      if (this->_parseCommonElement(n, torus, position, rotation) == false)
      {
	if (n.nodeName() == "minor")
	{
	  if (minor)
	    this->_putWarning(QObject::tr("A torus has several minor, "
					  "the first defined will be used"),
			      n);
	  else
	  {
	    torus->setr(_parseDouble(n, 0, 0, "minor"));
	    minor = true;
	  }
	}
	else if (n.nodeName() == "major")
	{
	  if (major)
	    this->_putWarning(QObject::tr("A torus has several major, "
					  "the first defined will be used"),
			      n);
	  else
	  {
	    torus->setR(_parseDouble(n, 0, 0, "major"));
	    major = true;
	  }
	}
	else
	  this->_putWarning(QObject::tr("Unknown element %1")
			    .arg(n.nodeName()),
			    n);
      }
    }
    n = n.nextSibling();
  }
  if (!minor || !major || !position || !rotation)
  {
    this->_putError(QObject::tr("A torus must have a position, rotation "
				"and a radius"), n);
    return NULL;
  }
  torus->setMaterial(_getMaterialByName(material));
  torus->setObject(obj);
  return torus;
}

void			Scene::_parsePrimitive(QDomNode n,
					       Object	*obj)
{
  QString			type;
  QString			material;

  while (n.isNull() == false && this->_hasError == false)
  {
    if (n.isComment() == false)
    {
      if (n.nodeName() != "primitive" || n.isElement() == false)
      {
	this->_putError(QObject::tr("A primitives child cannot be "
				    "empty and must be a "
				    "primitive element"), n);
	return ;
      }
      if (n.hasChildNodes() == false)
      {
	this->_putError(QObject::tr("A primitive element cannot be empty"), n);
	return ;
      }
      if (n.hasAttributes() == false
	  || n.attributes().contains("type") == false
	  || n.attributes().contains("material") == false)
      {
	this->_putError(QObject::tr("At least one of the primitive attributes "
				    "is missing"), n);
	return ;
      }
      material = n.attributes().namedItem("material").nodeValue();
      type = n.attributes().namedItem("type").nodeValue();
      if (this->_materialExists(material) == false)
      {
	this->_putError(QObject::tr("The material %1 doesnt exists  (you must "
				    "define a material before using it)")
			.arg(material), n);
	return ;
      }
      if (type == "sphere")
      obj->addPrimitive(this->_parseSphere(n.firstChild(), material, obj));
      else if (type == "torus")
	obj->addPrimitive(this->_parseTorus(n.firstChild(), material, obj));
      else if (type == "plane")
	obj->addPrimitive(this->_parsePlane(n.firstChild(), material, obj));
      else if (type == "cone")
	obj->addPrimitive(this->_parseCone(n.firstChild(), material, obj));
      else if (type == "cylinder")
	obj->addPrimitive(this->_parseCylinder(n.firstChild(), material, obj));
      else if (type == "cubeTroue")
	obj->addPrimitive(this->_parseCubeTroue(n.firstChild(), material,
						obj));
      else if (type == "triangle")
	obj->addPrimitive(this->_parseTriangle(n.firstChild(), material, obj));
      else if (type == "equation")
	obj->addPrimitive(this->_parseEquation(n.firstChild(), material, obj));
      else if (type == "parallelogram")
	obj->addPrimitive(this->_parseParallelogram(n.firstChild(),
						    material, obj));
      else
      {
	this->_putError(QObject::tr("%1 is not a valid primitive type")
			.arg(type), n);
	return ;
      }
    }
    n = n.nextSibling();
  }
}

void			Scene::_parsePrimitives(QDomNode n,
						Object	*obj)
{
  if (n.hasChildNodes() == false)
    this->_putError(QObject::tr("A primitives element cannot be empty"), n);
  else
    this->_parsePrimitive(n.firstChild(), obj);
}

void			Scene::_parseObjectOptions(QDomNode	n)
{
  Object			*obj = new Object();
  bool				position = false;
  bool				rotation = false;
  bool				solid = false;
  bool				primitive = false;

  while (n.isNull() == false && this->_hasError == false)
  {
    if (n.isComment() == false)
    {
      if (n.hasChildNodes() == false || n.isElement() == false)
      {
	this->_putError(QObject::tr("Every object children must be an element")
			, n);
	return ;
      }
      if (n.nodeName() == "position")
      {
	if (position)
	  this->_putWarning(QObject::tr("An object has several position, "
					"the first defined will be used"), n);
	else
	{
	  obj->setPosition(_parsePosition(n, "position"));
	  position = true;
	}
      }
      else if (n.nodeName() == "solid")
      {
	if (solid)
	  this->_putWarning(QObject::tr("An object has several solid value, "
					"the first defined will be used"), n);
	else
	{
	  obj->setSolid(_parseBoolean(n, "solid"));
	  solid = true;
	}
      }
      else if (n.nodeName() == "rotation")
      {
	if (rotation)
	  this->_putWarning(QObject::tr("An object has several rotations, "
					"the first defined will be used"), n);
	else
	{
	  obj->setRotation(_parseRotation(n));
	  rotation = true;
	}
      }
      else if (n.nodeName() == "primitives")
      {
	this->_parsePrimitives(n, obj);
	primitive = true;
      }
      else
	this->_putError(QObject::tr("%1 is not a valid element")
			.arg(n.nodeName()), n);
    }
    n = n.nextSibling();
  }
  if (!primitive || !solid || !position || !rotation)
    this->_putError(QObject::tr("An object must have a position, rotation, "
				"solid, and a leat one primitive"), n);
  else
    this->_objects.push_back(obj);
}

void			Scene::_parse3dsFile(QDomNode n)
{
  string		filename;
  bool			hasFilename = false;
  string		textDir;
  bool			hasTextDir = false;

  while (n.isNull() == false && this->_hasError == false)
  {
    if (n.isComment() == false)
    {
      if (n.hasChildNodes() == false || n.isElement() == false)
      {
	this->_putError(QObject::tr("Every a3ds children must "
				    "be an element"), n);
	return ;
      }
      if (n.nodeName() == "filename")
      {
	if (hasFilename)
	  this->_putWarning(QObject::tr("A a3ds has several filename, "
					"the first defined will be used"), n);
	else
	{
	  filename = _parseFile(n, "filename");
	  hasFilename = true;
	}
      }
      else if (n.nodeName() == "textureDir")
      {
	if (hasTextDir)
	  this->_putWarning(QObject::tr("A a3ds has several textureDir, "
					"the first defined will be used"), n);
	else
	{
	  textDir = _parseDir(n, "textureDir");
	  hasTextDir = true;
	}
      }
      else
	this->_putError(QObject::tr("%1 is not a valid element")
			.arg(n.nodeName()), n);
    }
    n = n.nextSibling();
  }
  if (!hasFilename)
    this->_putError(QObject::tr("An a3ds must have at leat a filename"), n);
  else if (this->_hasError == false)
  {
    A3DSParser	a3ds(filename, this->_interface);
    if (a3ds.hasError() == false)
    {
      this->_sceneFilenames.push_back(QString(filename.c_str()));
      const vector<A3DSLight*>		lights = a3ds.getLights();
      const vector<A3DSMaterial*>	materials = a3ds.getMaterials();
      const vector<A3DSMesh*>		meshes = a3ds.getMeshes();
      const char *color;

      if (meshes.size() < 1)
	this->_putError(QObject::tr("There is no meshes in %1")
			.arg(filename.c_str()));
      else
      {
	for (unsigned int i=0; i<materials.size(); i++)
	{
	  Material *mat = new Material(materials[i]->getName());
	  string textureName;

	  color = materials[i]->getAmbientColor();
	  mat->setColor(Color(color[0], color[1], color[2], color[3]));
	  if (materials[i]->getTextureName().empty() == false)
	  {
	    if (textDir.empty() == false)
	      textureName = textDir + "/" + materials[i]->getTextureName();
	    else
	      textureName = materials[i]->getTextureName();
	    if (QFileInfo(textureName.c_str()).exists() == false)
	    {
	      this->_putError(QObject::tr("texture %1 (a3ds) not found.")
			      .arg(textureName.c_str()));
	      delete mat;
	      return ;
	    }
	    mat->setTexture(new Texture(textureName));
	  }
	  else
	    mat->setTexture(NULL);
	  this->_materials.push_back(mat);
	}
	Object		*obj = new Object();
	for (unsigned int i=0; i<meshes.size(); i++)
	{
	  vector<Vector>	faces = meshes[i]->getFaces();
	  vector<Vector>	vertices = meshes[i]->getVertices();
	  map<string, vector<int> > matFaces = meshes[i]->getMaterialFaces();

	  for (unsigned int j=0; j<faces.size(); j++)
	  {
	    Triangle *triangle = new Triangle(obj,
					      vertices[faces[j].getX()],
					      _3dsgetFaceMat(j, matFaces),
					      vertices[faces[j].getY()],
					      vertices[faces[j].getZ()]);
	    obj->addPrimitive(triangle);
	  }
	}
	this->_objects.push_back(obj);
      }
    }
  }
}

Material*	Scene::_3dsgetFaceMat(int	j,
				      const map<string, vector<int> > &mat)
{
  for (map<string, vector<int> >::const_iterator it(mat.begin());
  it!=mat.end();
  it++)
  {
    for (unsigned int i=0; i<it->second.size(); i++)
    {
      if (it->second[i] == j)
	if (this->_materialExists(it->first.c_str()))
	  return this->_getMaterialByName(it->first.c_str());
    }
  }
  return NULL;
}

void			Scene::_parseObject(QDomNode n)
{
  QDomNamedNodeMap	nodeMap;
  QString		name;
  QString		material;

  while (n.isNull() == false && this->_hasError == false)
  {
    if (n.isComment() == false)
    {
      if ((n.nodeName() != "object"
	   && n.nodeName() != "parallelepipede"
	   && n.nodeName() != "a3ds")
	  || n.isElement() == false)
      {
	this->_putError(QObject::tr("An objects child cannot be empty and "
				    "must be an object element"), n);
	return ;
      }
      if (n.hasChildNodes() == false)
      {
	this->_putError(QObject::tr("An object element cannot be empty"), n);
	return;
      }
      if (n.nodeName() == "a3ds")
	this->_parse3dsFile(n.firstChild());
      else if (n.nodeName() == "parallelepipede")
      {
	if (n.hasAttributes() == false
	    || n.attributes().contains("material") == false)
	{
	  this->_putError(QObject::tr("The parallelepipede attributes "
				      "are missing"), n);
	  return ;
	}
	material = n.attributes().namedItem("material").nodeValue();
	if (this->_materialExists(material) == false)
	{
	  this->_putError(QObject::tr("The material %1 doesnt exists (you "
				      "must define a material before use it)")
			  .arg(material), n);
	  return ;
	}
	this->_parseSett(n.firstChild(), material);
      }
      else
	this->_parseObjectOptions(n.firstChild());
    }
    n = n.nextSibling();
  }
}

void			Scene::_parseObjects(QDomNode n)
{
  if (n.hasChildNodes() == false)
    this->_putError(QObject::tr("An objects element cannot be empty"), n);
  else
    this->_parseObject(n.firstChild());
}
