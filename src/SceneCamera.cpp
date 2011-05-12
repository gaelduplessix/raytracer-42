//
// SceneCamera.cpp for  in /home/laplan_m/Src/Epitech/Projects/C++/raytracer-42
//
// Made by melvin laplanche
// Login   <laplan_m@epitech.net>
//
// Started on  Wed May 11 18:56:38 2011 melvin laplanche
// Last update Thu May 12 00:06:50 2011 melvin laplanche
//

#include "Scene.hpp"

void			Scene::_parseCameraCinema(QDomNode n)
{
  CinemaCamera	*cam = new CinemaCamera();
  QDomNode	firstChild = n;
  bool		position = false;
  bool		rotation = false;

  while (n.isNull() == false)
  {
    if (n.hasChildNodes() == false || n.isElement() == false)
      this->_putError("Every cinema camera children must be an element", n);
    if (n.nodeName() == "position")
    {
      if (position)
	this->_putWarning("An cinema camera has several position, "
			  "the first defined will be used", n);
      else
      {
	cam->setPosition(this->_parsePosition(n, "position"));
	position = true;
      }
    }
    else if (n.nodeName() == "rotation")
    {
      if (rotation)
	this->_putWarning("An cinema camera has several rotation, "
			  "the first defined will be used", n);
      else
      {
	cam->setRotation(this->_parseRotation(n));
	rotation = true;
      }
    }
    else
      this->_putError(n.nodeName().toStdString() + " is not a valid element",
		      n);
    n = n.nextSibling();
  }
  if (position == false)
    this->_putError("A camera must have at least a position",
		    firstChild.parentNode());
  this->_cameras.push_back(cam);
}

void			Scene::_parseCamera(QDomNode n)
{
  QDomNamedNodeMap	nodeMap;

  while (n.isNull() == false)
  {
    if (n.nodeName() != "camera" || n.isElement() == false)
      this->_putError("A cameras child cannot be empty and must be a "
			"camera element", n);
    if (n.hasChildNodes() == false)
      this->_putError("A camera element cannot be empty", n);
    if (n.hasAttributes() == false|| n.attributes().contains("type") == false)
      this->_putError("The camera attributes are missing", n);
    if (n.attributes().namedItem("type").nodeValue() == "cinema")
      this->_parseCameraCinema(n.firstChild());
    else
      this->_putError(n.attributes().namedItem("type").nodeValue()
		      .toStdString() + "is not a valid camera type", n);
    n = n.nextSibling();
  }
}

void			Scene::_parseCameras(QDomNode n)
{
  if (n.hasChildNodes() == false)
    this->_putError("A cameras element cannot be empty", n);
  this->_parseCamera(n.firstChild());
}
