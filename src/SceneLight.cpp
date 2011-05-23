//
// SceneLight.cpp for  in /home/laplan_m/Src/Epitech/Projects/C++/raytracer-42
//
// Made by melvin laplanche
// Login   <laplan_m@epitech.net>
//
// Started on  Wed May 11 17:09:42 2011 melvin laplanche
// Last update Mon May 23 13:10:31 2011 melvin laplanche
//

#include "Scene.hpp"

Spot*			Scene::_parseSpotLight(QDomNode	n)
{
  Spot*			light = new Spot();
  bool			position = false;
  bool			color = false;
  bool			intensity = false;
  bool			directLight = false;

  while (n.isNull() == false && this->_hasError == false)
  {
    if (n.isComment() == false)
    {
      if (n.hasChildNodes() == false || n.isElement() == false)
      {
	this->_putError(QObject::tr("Every light children must be an element"),
			n);
	return NULL;
      }
      if (n.nodeName() == "position")
      {
	if (position)
	  this->_putWarning(QObject::tr("A light has several position, "
					"the first defined will be used"), n);
	else
	{
	  light->setPosition(_parsePosition(n, "position"));
	  position = true;
	}
      }
      else if (n.nodeName() == "color")
      {
	if (color)
	  this->_putWarning(QObject::tr("A light has several color, "
					"the first defined will be used"), n);
	else
	{
	  light->setColor(_parseColor(n));
	  color = true;
	}
      }
      else if (n.nodeName() == "intensity")
      {
	if (intensity)
	  this->_putWarning(QObject::tr("A light has several intensity, "
					"the first defined will be used"), n);
	else
	{
	  light->setIntensity(_parseDouble(n, 0, 0, "intensity"));
	  intensity = true;
	}
      }
      else if (n.nodeName() == "directLight")
      {
	if (directLight)
	  this->_putWarning(QObject::tr("A light has several directLight, "
					"the first defined will be used"), n);
	else
	{
	  light->setDirectLightPow(_parseDouble(n, 0, 0, "directLight"));
	  directLight = true;
	}
      }
      else
      {
	this->_putError(QObject::tr("%1 is not a valid element")
			.arg(n.nodeName()), n);
	return NULL;
      }
    }
    n = n.nextSibling();
  }
  if (!position || !color || !intensity)
  {
    this->_putError(QObject::tr("A spot must have a position, a color, "
				"and an intensity"), n);
    return NULL;
  }
  return light;
}

ParallelLight*			Scene::_parseParallelLight(QDomNode	n)
{
  ParallelLight*	light = new ParallelLight();
  bool			direction = false;
  bool			color = false;
  bool			intensity = false;

  while (n.isNull() == false && this->_hasError == false)
  {
    if (n.isComment() == false)
    {
      if (n.hasChildNodes() == false || n.isElement() == false)
      {
	this->_putError(QObject::tr("Every light children must be an element"),
			n);
	return NULL;
      }
      if (n.nodeName() == "direction")
      {
	if (direction)
	  this->_putWarning(QObject::tr("A light has several direction, "
					"the first defined will be used"), n);
	else
	{
	  light->setPosition(_parsePosition(n, "direction"));
	  direction = true;
	}
      }
      else if (n.nodeName() == "color")
      {
	if (color)
	  this->_putWarning(QObject::tr("A light has several colors, "
					"the first defined will be used"), n);
	else
	{
	  light->setColor(_parseColor(n));
	  color = true;
	}
      }
      else if (n.nodeName() == "intensity")
      {
	if (intensity)
	  this->_putWarning(QObject::tr("A light has several intensity, "
					"the first defined will be used"), n);
	else
	{
	  light->setIntensity(_parseDouble(n, 0, 0, "intensity"));
	  intensity = true;
	}
      }
      else
	this->_putError(QObject::tr("%1 is not a valid element")
			.arg(n.nodeName()), n);
    }
    n = n.nextSibling();
  }
  if (!direction || !color || !intensity)
  {
    this->_putError(QObject::tr("A parallel light must have a direction, "
				"color, and an intensity"), n);
    return NULL;
  }
  return light;
}

SphericalLight*			Scene::_parseSphericalLight(QDomNode	n)
{
  SphericalLight*	light = new SphericalLight();
  bool			position = false;
  bool			color = false;
  bool			intensity = false;
  bool			size = false;
  bool			directLight = false;

  while (n.isNull() == false && this->_hasError == false)
  {
    if (n.isComment() == false)
    {
      if (n.hasChildNodes() == false || n.isElement() == false)
      {
	this->_putError(QObject::tr("Every light children must be an element"),
			n);
	return NULL;
      }
      if (n.nodeName() == "position")
      {
	if (position)
	  this->_putWarning(QObject::tr("A light has several position, "
				      "the first defined will be used"), n);
	else
	{
	  light->setPosition(_parsePosition(n, "position"));
	  position = true;
	}
      }
      else if (n.nodeName() == "color")
      {
	if (color)
	  this->_putWarning(QObject::tr("A light has several colors, "
					"the first defined will be used"), n);
	else
	{
	  light->setColor(_parseColor(n));
	  color = true;
	}
      }
      else if (n.nodeName() == "intensity")
      {
	if (intensity)
	  this->_putWarning(QObject::tr("A light has several intensity, "
					"the first defined will be used"), n);
	else
	{
	  light->setIntensity(_parseDouble(n, 0, 0, "intensity"));
	  intensity = true;
	}
      }
      else if (n.nodeName() == "size")
      {
	if (size)
	  this->_putWarning(QObject::tr("A light has several size, "
					"the first defined will be used"), n);
	else
	{
	  light->setSize(_parseDouble(n, 0, 0, "size"));
	  size = true;
	}
      }
      else if (n.nodeName() == "directLight")
      {
	if (directLight)
	  this->_putWarning(QObject::tr("A light has several directLight, "
					"the first defined will be used"), n);
	else
	{
	  light->setDirectLightPow(_parseDouble(n, 0, 0, "directLight"));
	  directLight = true;
	}
      }
      else
      {
	this->_putError(QObject::tr("%1 is not a valid element")
			.arg(n.nodeName()), n);
	return NULL;
      }
    }
    n = n.nextSibling();
  }
  if (!position || !color || !intensity || !size)
  {
    this->_putError(QObject::tr("A spherical light must have a position, "
				"a color, a size, and an intensity"), n);
    return NULL;
  }
  return light;
}

ParallelogramLight*		Scene::_parseParallelogramLight(QDomNode n)
{
  ParallelogramLight*	light = new ParallelogramLight();
  bool			p1 = false;
  bool			p2 = false;
  bool			p3 = false;
  bool			color = false;
  bool			intensity = false;
  bool			directLight = false;

  while (n.isNull() == false && this->_hasError == false)
  {
    if (n.isComment() == false)
    {
      if (n.hasChildNodes() == false || n.isElement() == false)
      {
	this->_putError(QObject::tr("Every light children must be an element"),
			n);
	return NULL;
      }
      if (n.nodeName() == "point1")
      {
	if (p1)
	  this->_putWarning(QObject::tr("A light has several point/point1, "
					"the first defined will be used"), n);
	else
	{
	  light->setPosition(_parsePosition(n, "point1"));
	  p1 = true;
	}
      }
      else if (n.nodeName() == "point2")
      {
	if (p2)
	  this->_putWarning(QObject::tr("A light has several point2, "
					"the first defined will be used"), n);
	else
	{
	  light->setPoint2(_parsePosition(n, "point2"));
	  p2 = true;
	}
      }
      else if (n.nodeName() == "point3")
      {
	if (p3)
	  this->_putWarning(QObject::tr("A light has several point3, "
					"the first defined will be used"), n);
	else
	{
	  light->setPoint3(_parsePosition(n, "point3"));
	  p3 = true;
	}
      }
      else if (n.nodeName() == "color")
      {
	if (color)
	  this->_putWarning(QObject::tr("A light has several colors, "
					"the first defined will be used"), n);
	else
	{
	  light->setColor(_parseColor(n));
	  color = true;
	}
      }
      else if (n.nodeName() == "intensity")
      {
	if (intensity)
	  this->_putWarning(QObject::tr("A light has several intensity, "
					"the first defined will be used"), n);
	else
	{
	  light->setIntensity(_parseDouble(n, 0, 0, "intensity"));
	  intensity = true;
	}
      }
      else if (n.nodeName() == "directLight")
      {
	if (directLight)
	  this->_putWarning(QObject::tr("A light has several directLight, "
					"the first defined will be used"), n);
	else
	{
	  light->setDirectLightPow(_parseDouble(n, 0, 0, "directLight"));
	  directLight = true;
	}
      }
      else
      {
	this->_putError(QObject::tr("%1 is not a valid element")
			.arg(n.nodeName()), n);
	return NULL;
      }
    }
    n = n.nextSibling();
  }
  if (!p1 || !p2 || !p3 || !color || !intensity)
  {
    this->_putError(QObject::tr("A parallelogram light must have a point1, "
				"a point2, a point3, a color, and an "
				"intensity"), n);
    return NULL;
  }
  return light;
}

void			Scene::_parseLight(QDomNode n)
{
  QDomNamedNodeMap	nodeMap;
  QString		type;

  while (n.isNull() == false && this->_hasError == false)
  {
    if (n.isComment() == false)
    {
      if (n.nodeName() != "light" || n.isElement() == false)
      {
	this->_putError(QObject::tr("A lights child cannot be empty and must "
				    "be a light element"), n);
	return ;
      }
      if (n.hasChildNodes() == false)
      {
	this->_putError(QObject::tr("A light element cannot be empty"), n);
	return ;
      }
      if (n.hasAttributes() != false && n.attributes().contains("type"))
	type = n.attributes().namedItem("type").nodeValue();
      if ((n.hasAttributes() == false
	   || n.attributes().contains("type") == false))
      {
	this->_putError(QObject::tr("%1 is not a valide light type").arg(type)
			, n);
	return ;
      }
      else if (type == "spot")
	this->_lights.push_back(this->_parseSpotLight(n.firstChild()));
      else if (type == "parallel")
	this->_lights.push_back(this->_parseParallelLight(n.firstChild()));
      else if (type == "spherical")
	this->_lights.push_back(this->_parseSphericalLight(n.firstChild()));
      else if (type == "parallelogram")
	this->_lights.push_back(this->_parseParallelogramLight(n.firstChild()));
      else
      {
	this->_putError(QObject::tr("%1 is not a valide light type").arg(type),
			n);
	return ;
      }
    }
    n = n.nextSibling();
  }
}

void			Scene::_parseLights(QDomNode n)
{
  if (n.hasChildNodes() == false)
    this->_putError(QObject::tr("A lights element cannot be empty"), n);
  else
    this->_parseLight(n.firstChild());
}
