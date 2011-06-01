//
// SceneCamera.cpp for  in /home/laplan_m/Src/Epitech/Projects/C++/raytracer-42
//
// Made by melvin laplanche
// Login   <laplan_m@epitech.net>
//
// Started on  Wed May 11 18:56:38 2011 melvin laplanche
// Last update Wed Jun  1 19:03:25 2011 loick michard
//

#include "Scene.hpp"

bool			Scene::_cameraExists(string name)
{
  int	nb_cam = this->_cameras.size();

  for (int i = 0; i < nb_cam; ++i)
    if (this->_cameras[i]->getName() == name)
      return true;
  return false;
}


void			Scene::_parseCameraCinema(QDomNode	n,
						  QString	name)
{
  CinemaCamera	*cam = new CinemaCamera();
  QDomNode	firstChild = n;
  bool		position = false;
  bool		rotation = false;
  bool		focalLength = false;
  bool		apertureSize = false;
  bool		focus = false;
  bool		target = false;

  cam->setName(name.toStdString());
  while (n.isNull() == false && this->_hasError == false)
  {
    if (n.isComment() == false)
    {
      if (n.hasChildNodes() == false || n.isElement() == false)
      {
	this->_putError(QObject::tr("Every cinema camera children must "
				    "be an element"), n);
	return ;
      }
      if (n.nodeName() == "position")
      {
	if (position)
	  this->_putWarning(QObject::tr("A cinema camera has several "
					"position, "
					"the first defined will be used"), n);
	else
	{
	  cam->setPosition(this->_parsePosition(n, "position"));
	  position = true;
	}
      }
      else if (n.nodeName() == "target")
      {
	if (target)
	  this->_putWarning(QObject::tr("A cinema camera has several "
					"target, "
					"the first defined will be used"), n);
	else
	{
	  cam->setTarget(this->_parsePosition(n, "target"));
	  target = true;
	}
      }
      else if (n.nodeName() == "rotation")
      {
	if (rotation)
	  this->_putWarning(QObject::tr("A cinema camera has several "
					"rotation, "
					"the first defined will be used"), n);
	else
	{
	  cam->setRotation(this->_parseRotation(n));
	  rotation = true;
	}
      }
      else if (n.nodeName() == "focalLength")
      {
	if (focalLength)
	  this->_putWarning(QObject::tr("A cinema camera has several "
					"focalLength, "
					"the first defined will be used"),
			    n);
	else
	{
	  cam->setFocalLength(_parseDouble(n, 0, 0, "focalLength"));
	  focalLength = true;
	}
      }
      else if (n.nodeName() == "apertureSize")
      {
	if (apertureSize)
	  this->_putWarning(QObject::tr("A cinema camera has several "
					"apertureSize, "
					"the first defined will be used"),
			    n);
	else
	{
	  cam->setApertureSize(_parseDouble(n, 0, 0, "apertureSize"));
	  apertureSize = true;
	}
      }
      else if (n.nodeName() == "focus")
      {
	if (focus)
	  this->_putWarning(QObject::tr("A cinema camera has several "
					"focus, "
					"the first defined will be used"),
			    n);
	else
	{
	  cam->setFocus(_parseDouble(n, 0, 0, "focus"));
	  focus = true;
	}
      }
      else
	this->_putError(QObject::tr("%1 is not a valid element")
			.arg(n.nodeName()), n);
    }
    n = n.nextSibling();
  }
  if (this->_hasError == false && position == false)
  {
    this->_putError(QObject::tr("A camera must have at least a position"),
		    firstChild.parentNode());
    return ;
  }
  this->_cameras.push_back(cam);
}

void			Scene::_parseCamera(QDomNode n)
{
  QDomNamedNodeMap	nodeMap;
  QString		name;

  while (n.isNull() == false && this->_hasError == false)
  {
    if (n.isComment() == false)
    {
      if (n.nodeName() != "camera" || n.isElement() == false)
      {
	this->_putError(QObject::tr("A cameras child cannot be empty "
				    "and must be a camera element"), n);
	return ;
      }
      if (n.hasChildNodes() == false)
      {
	this->_putError(QObject::tr("A camera element cannot be empty"), n);
	return ;
      }
      if (n.hasAttributes() == false
	  || n.attributes().contains("type") == false
	  || n.attributes().contains("name") == false)
      {
	this->_putError(QObject::tr("One or several camera attributes "
				    "are missing (type, name)"), n);
	return ;
      }
      name = n.attributes().namedItem("name").nodeValue();
      if (this->_cameraExists(name.toStdString()))
      {
	this->_putError("The camera " + name + " already exists", n);
	return ;
      }
      if (n.attributes().namedItem("type").nodeValue() == "cinema")
	this->_parseCameraCinema(n.firstChild(), name);
      else
      {
	this->_putError(QObject::tr("%1 is not a valid camera type")
			.arg(n.attributes().namedItem("type").nodeValue()), n);
	return ;
      }
    }
    n = n.nextSibling();
  }
}

void			Scene::_parseCameras(QDomNode n)
{
  if (n.hasChildNodes() == false)
  {
    this->_putError(QObject::tr("A cameras element cannot be empty"), n);
    return ;
  }
  this->_parseCamera(n.firstChild());
}
