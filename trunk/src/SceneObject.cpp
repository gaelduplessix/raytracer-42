//
// SceneObject.cpp for  in /home/laplan_m/Src/Epitech/Projects/C++/raytracer-42
//
// Made by melvin laplanche
// Login   <laplan_m@epitech.net>
//
// Started on  Wed May 11 17:09:06 2011 melvin laplanche
// Last update Thu May 12 17:10:30 2011 gael jochaud-du-plessix
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
      this->_putWarning("An element has several position, "
			"the first defined will be used", n);
    else
    {
      prime->setPosition(_parsePosition(n, "position"));
      position = true;
    }
  }
  else if (n.nodeName() == "rotation")
  {
    if (rotation)
      this->_putWarning("An element has several rotation, "
			"the first defined will be used", n);
    else
    {
      prime->setRotation(_parseRotation(n));
      rotation = true;
    }
  }
  return (false);
}

EquationPrimitive*		Scene::_parseEquation(QDomNode n,
						      QString  material,
						      Object*  obj)
{
  Material			mat;
  bool				position = false;
  Point				positionValue;
  bool				rotation = false;
  Rotation			rotationValue;
  string			equationValue;
  bool				equation = false;

  while (n.isNull() == false)
  {
    if (n.hasChildNodes() == false || n.isElement() == false)
      this->_putError("Every primitive children must be an element", n);
    if (n.nodeName() == "position")
    {
      if (position)
	this->_putWarning("An equation has several position, "
			  "the first defined will be used", n);
      else
      {
	positionValue = _parsePosition(n, "position");
	position = true;
      }
    }
    else if (n.nodeName() == "rotation")
    {
      if (rotation)
	this->_putWarning("An equation has several rotation, "
			  "the first defined will be used", n);
      else
      {
	rotationValue = _parseRotation(n);
	rotation = true;
      }
    }
    else if (n.nodeName() == "equation")
    {
      if (equation)
	this->_putWarning("An equation has several equation, "
			  "the first defined will be used", n);
      else
      {
	this->_checkContentIsSingleText(n, "equation");
	equationValue = n.toElement().text().toStdString();
	equation = true;
      }
    }
    else
      this->_putWarning("Unknown element " + n.nodeName().toStdString(), n);
    n = n.nextSibling();
  }
  if (!equation || !position || !rotation)
    this->_putError("A equation must have a position, a rotation "
		    "and an equation", n);
  return new EquationPrimitive(equationValue, obj,
			       positionValue, rotationValue, mat);
  (void)material;
}

Sphere*			Scene::_parseSphere(QDomNode	n,
					    QString	material,
					    Object*	obj)
{
  Material			mat;
  bool				position = false;
  bool				rotation = false;
  bool				radius = false;
  Sphere			*sphere = new Sphere();

  while (n.isNull() == false)
  {
    if (n.hasChildNodes() == false || n.isElement() == false)
      this->_putError("Every primitive children must be an element", n);
    if (this->_parseCommonElement(n, sphere, position, rotation) == false)
    {
      if (n.nodeName() == "radius")
      {
	if (radius)
	  this->_putWarning("A sphere has several radius, "
			    "the first defined will be used", n);
	else
	{
	  sphere->setRadius(_parseDouble(n, 0, 0, "radius"));
	  radius = true;
	}
      }
      else
	this->_putWarning("Unknown element " + n.nodeName().toStdString(), n);
    }
    n = n.nextSibling();
  }
  if (!radius || !position || !rotation)
    this->_putError("A sphere must have a position, rotation and a radius", n);
  sphere->setMaterial(_getMaterialByName(material));
  sphere->setObject(obj);
  return sphere;
}

CubeTroue*			Scene::_parseCubeTroue(QDomNode	n,
						       QString	material,
						       Object*	obj)
{
  Material			mat;
  bool				position = false;
  bool				rotation = false;
  bool				coeff = false;
  CubeTroue			*cube = new CubeTroue();

  while (n.isNull() == false)
  {
    if (n.hasChildNodes() == false || n.isElement() == false)
      this->_putError("Every primitive children must be an element", n);
    if (this->_parseCommonElement(n, cube, position, rotation) == false)
    {
      if (n.nodeName() == "coeff")
      {
	if (coeff)
	  this->_putWarning("A cube has several coeff, "
			    "the first defined will be used", n);
	else
	{
	  cube->setCoeff(_parseDouble(n, 0, 0, "coeff"));
	  coeff = true;
	}
      }
      else
	this->_putWarning("Unknown element " + n.nodeName().toStdString(), n);
    }
    n = n.nextSibling();
  }
  if (!position || !rotation || !coeff)
    this->_putError("A cube must have a position, rotation and a coeff", n);
  cube->setMaterial(_getMaterialByName(material));
  cube->setObject(obj);
  return cube;
}

Triangle*			Scene::_parseTriangle(QDomNode	n,
						      QString	material,
						      Object*	obj)
{
  Material			mat;
  bool				position = false;
  bool				rotation = false;
  bool				vert1 = false;
  bool				vert2 = false;
  Triangle			*triangle = new Triangle();

  while (n.isNull() == false)
  {
    if (n.hasChildNodes() == false || n.isElement() == false)
      this->_putError("Every primitive children must be an element", n);
    if (this->_parseCommonElement(n, triangle, position, rotation) == false)
    {
      if (n.nodeName() == "vertex1")
      {
	if (vert1)
	  this->_putWarning("A triangle has several vertex1, "
			    "the first defined will be used", n);
	else
	{
	  triangle->setVertex1(_parsePosition(n, "vertex1"));
	  vert1 = true;
	}
      }
      else if (n.nodeName() == "vertex2")
      {
	if (vert2)
	  this->_putWarning("A triangle has several vertex2, "
			    "the first defined will be used", n);
	else
	{
	  triangle->setVertex2(_parsePosition(n, "vertex2"));
	  vert2 = true;
	}
      }
      else
	this->_putWarning("Unknown element " + n.nodeName().toStdString(), n);
    }
    n = n.nextSibling();
  }
  if (!position || !rotation || !vert1 || !vert2)
    this->_putError("A triangle must have a position, a rotation, a vertex1 "
		    "and a vertext2", n);
  triangle->setMaterial(_getMaterialByName(material));
  triangle->setObject(obj);
  return triangle;
}

Cone*			Scene::_parseCone(QDomNode	n,
					  QString	material,
					  Object*	obj)
{
  Material			mat;
  bool				position = false;
  bool				rotation = false;
  bool				min = false;
  bool				max = false;
  bool				radius = false;
  Cone				*cone = new Cone();

  while (n.isNull() == false)
  {
    if (n.hasChildNodes() == false || n.isElement() == false)
      this->_putError("Every primitive children must be an element", n);
    if (this->_parseCommonElement(n, cone, position, rotation) == false)
    {
      if (n.nodeName() == "radius")
      {
	if (radius)
	  this->_putWarning("A cone has several radius, "
			    "the first defined will be used", n);
	else
	{
	  cone->setAngle(_parseDouble(n, 0, 0, "angle"));
	  radius = true;
	}
      }
      else if (n.nodeName() == "limitMin")
      {
	if (min)
	  this->_putWarning("A cone has several limitMin, "
			    "the first defined will be used", n);
	else
	{
	  cone->setLimitMin(_parseDouble(n, 0, 0, "limitMin"));
	  min = true;
	}
      }
      else if (n.nodeName() == "limitMax")
      {
	if (max)
	  this->_putWarning("A cone has several limitMax, "
			    "the first defined will be used", n);
	else
	{
	  cone->setLimitMax(_parseDouble(n, 0, 0, "limitMax"));
	  max = true;
	}
      }
      else
	this->_putWarning("Unknown element " + n.nodeName().toStdString(), n);
    }
    n = n.nextSibling();
  }
  if (!position || !rotation || !radius)
    this->_putError("A cone must have a position, a rotation, and a radius",
		    n);
  cone->setMaterial(_getMaterialByName(material));
  cone->setObject(obj);
  return cone;
}

Cylinder*			Scene::_parseCylinder(QDomNode	n,
						      QString	material,
						      Object*	obj)
{
  Material			mat;
  bool				position = false;
  bool				rotation = false;
  bool				min = false;
  bool				max = false;
  bool				radius = false;
  Cylinder			*cylinder = new Cylinder();

  while (n.isNull() == false)
  {
    if (n.hasChildNodes() == false || n.isElement() == false)
      this->_putError("Every primitive children must be an element", n);
    if (this->_parseCommonElement(n, cylinder, position, rotation) == false)
    {
      if (n.nodeName() == "radius")
      {
	if (radius)
	  this->_putWarning("A cylinder has several radius, "
			    "the first defined will be used", n);
	else
	{
	  cylinder->setRadius(_parseDouble(n, 0, 0, "radius"));
	  radius = true;
	}
      }
      else if (n.nodeName() == "limitMin")
      {
	if (min)
	  this->_putWarning("A cylinder has several limitMin, "
			    "the first defined will be used", n);
	else
	{
	  cylinder->setLimitMin(_parseDouble(n, 0, 0, "limitMin"));
	  min = true;
	}
      }
      else if (n.nodeName() == "limitMax")
      {
	if (max)
	  this->_putWarning("A cylinder has several limitMax, "
			    "the first defined will be used", n);
	else
	{
	  cylinder->setLimitMax(_parseDouble(n, 0, 0, "limitMax"));
	  max = true;
	}
      }
      else
	this->_putWarning("Unknown element " + n.nodeName().toStdString(), n);
    }
    n = n.nextSibling();
  }
  if (!position || !rotation || !radius)
    this->_putError("A cylinder must have a position, a rotation, "
		    "and a radius", n);
  cylinder->setMaterial(_getMaterialByName(material));
  cylinder->setObject(obj);
  return cylinder;
}

Plane*			Scene::_parsePlane(QDomNode	n,
					   QString	material,
					   Object*	obj)
{
  Material			mat;
  bool				position = false;
  bool				rotation = false;
  bool				x = false;
  bool				y = false;
  Plane				*plane = new Plane();

  while (n.isNull() == false)
  {
    if (n.hasChildNodes() == false || n.isElement() == false)
      this->_putError("Every primitive children must be an element", n);
    if (this->_parseCommonElement(n, plane, position, rotation) == false)
    {
      if (n.nodeName() == "limitX")
      {
	if (x)
	  this->_putWarning("A plane has several limitX, "
			    "the first defined will be used", n);
	else
	{
	  plane->setLimitX(_parseDouble(n, 0, 0, "limitX"));
	  x = true;
	}
      }
      else if (n.nodeName() == "limitY")
      {
	if (y)
	  this->_putWarning("A plane has several limitY, "
			    "the first defined will be used", n);
	else
	{
	  plane->setLimitY(_parseDouble(n, 0, 0, "limitY"));
	  y = true;
	}
      }
      else
	this->_putWarning("Unknown element " + n.nodeName().toStdString(), n);
    }
    n = n.nextSibling();
  }
  if (!position || !rotation)
    this->_putError("A sphere must have a position and a rotation", n);
  plane->setMaterial(_getMaterialByName(material));
  plane->setObject(obj);
  return plane;
}

Torus*			Scene::_parseTorus(QDomNode	n,
					   QString	material,
					   Object*	obj)
{
  Material			mat;
  bool				position = false;
  bool				rotation = false;
  bool				minor = false;
  bool				major = false;
  Torus				*torus = new Torus();

  while (n.isNull() == false)
  {
    if (n.hasChildNodes() == false || n.isElement() == false)
      this->_putError("Every primitive children must be an element", n);
    if (this->_parseCommonElement(n, torus, position, rotation) == false)
    {
      if (n.nodeName() == "minor")
      {
	if (minor)
	  this->_putWarning("A torus has several minor, "
			    "the first defined will be used", n);
	else
	{
	  torus->setr(_parseDouble(n, 0, 0, "minor"));
	  minor = true;
	}
      }
      else if (n.nodeName() == "major")
      {
	if (major)
	  this->_putWarning("A torus has several major, "
			    "the first defined will be used", n);
	else
	{
	  torus->setR(_parseDouble(n, 0, 0, "major"));
	  major = true;
	}
      }
      else
	this->_putWarning("Unknown element " + n.nodeName().toStdString(), n);
    }
    n = n.nextSibling();
  }
  if (!minor || !major || !position || !rotation)
    this->_putError("A torus must have a position, rotation and a radius", n);
  torus->setMaterial(_getMaterialByName(material));
  torus->setObject(obj);
  return torus;
}

void			Scene::_parsePrimitive(QDomNode n,
					       Object	*obj)
{
  QString			type;
  QString			material;

  while (n.isNull() == false)
  {
    if (n.nodeName() != "primitive" || n.isElement() == false)
      this->_putError("A primitives child cannot be empty and must be a "
		      "primitive element", n);
    if (n.hasChildNodes() == false)
      this->_putError("A primitive element cannot be empty", n);
    if (n.hasAttributes() == false
	|| n.attributes().contains("type") == false
	|| n.attributes().contains("material") == false)
      this->_putError("The primitive attributes are missing", n);
    material = n.attributes().namedItem("material").nodeValue();
    type = n.attributes().namedItem("type").nodeValue();
    this->_failIfMaterialNameDoesntExists(material, n);
    if (type == "sphere")
      obj->addPrimitive(this->_parseSphere(n.firstChild(), material, obj));
    else if (type == "torus")
      obj->addPrimitive(this->_parseTorus(n.firstChild(), material, obj));
    else if (type == "Plane")
      obj->addPrimitive(this->_parsePlane(n.firstChild(), material, obj));
    else if (type == "cone")
      obj->addPrimitive(this->_parseCone(n.firstChild(), material, obj));
    else if (type == "cylinder")
      obj->addPrimitive(this->_parseCylinder(n.firstChild(), material, obj));
    else if (type == "cubeTroue")
      obj->addPrimitive(this->_parseCubeTroue(n.firstChild(), material, obj));
    else if (type == "triangle")
      obj->addPrimitive(this->_parseTriangle(n.firstChild(), material, obj));
    else if (type == "equation")
      obj->addPrimitive(this->_parseEquation(n.firstChild(), material, obj));
    else
      this->_putError(type.toStdString() + " is not a valid primitive type",
		      n);
    n = n.nextSibling();
  }
}

void			Scene::_parsePrimitives(QDomNode n,
						Object	*obj)
{
  if (n.hasChildNodes() == false)
    this->_putError("A primitives element cannot be empty", n);
  this->_parsePrimitive(n.firstChild(), obj);
}

void			Scene::_parseObjectOptions(QDomNode	n)
{
  Object			*obj = new Object();
  bool				position = false;
  bool				rotation = false;
  bool				solid = false;
  bool				primitive = false;

  while (n.isNull() == false)
  {
    if (n.hasChildNodes() == false || n.isElement() == false)
      this->_putError("Every object children must be an element", n);
    if (n.nodeName() == "position")
    {
      if (position)
	this->_putWarning("An object has several position, "
			  "the first defined will be used", n);
      else
      {
	obj->setPosition(_parsePosition(n, "position"));
	position = true;
      }
    }
    else if (n.nodeName() == "solid")
    {
      if (solid)
	this->_putWarning("An object has several solid value, "
			  "the first defined will be used", n);
      else
      {
	obj->setSolid(_parseBoolean(n, "solid"));
	solid = true;
      }
    }
    else if (n.nodeName() == "rotation")
    {
      if (rotation)
	this->_putWarning("An object has several rotations, "
			  "the first defined will be used", n);
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
      this->_putError(n.nodeName().toStdString() + " is not a valid element",
		      n);
    n = n.nextSibling();
  }
  if (!primitive || !solid || !position || !rotation)
    this->_putError("An object must have a position, rotation, solid, "
		    "and a leat one primitive", n);
  this->_objects.push_back(obj);
}

void			Scene::_parseObject(QDomNode n)
{
  QDomNamedNodeMap	nodeMap;
  QString		name;

  while (n.isNull() == false)
  {
    if (n.nodeName() != "object" || n.isElement() == false)
      this->_putError("An objects child cannot be empty and must be an "
			"object element", n);
    if (n.hasChildNodes() == false)
      this->_putError("An object element cannot be empty", n);
    this->_parseObjectOptions(n.firstChild());
    n = n.nextSibling();
  }
}

void			Scene::_parseObjects(QDomNode n)
{
  if (n.hasChildNodes() == false)
    this->_putError("An objects element cannot be empty", n);
  this->_parseObject(n.firstChild());
}
