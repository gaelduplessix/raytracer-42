//
// Scene.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
//
// Made by loick michard
// Login   <michar_l@epitech.net>
//
// Started on  Wed Apr 27 18:24:15 2011 loick michard
// Last update Sun May 15 02:50:47 2011 melvin laplanche
//

#include "Scene.hpp"

Scene::Scene(vector<Camera*> cameras,
	     vector<Object*> objects,
	     vector<Light*> lights):
  _hasError(false), _parsingDone(true), _interface(NULL),
  _cameras(cameras), _objects(objects), _lights(lights)
{

}

Scene::Scene(vector<Camera*> cameras,
	     vector<Object*> objects,
	     vector<Light*> lights,
	     vector<Material*> materials):
  _hasError(false), _parsingDone(true), _interface(NULL),
  _cameras(cameras), _objects(objects), _lights(lights), _materials(materials)
{

}

Scene::Scene(void): _hasError(false), _parsingDone(false), _interface(NULL)
{

}

bool	Scene::isValid(void) const
{
  return (_hasError == false && _parsingDone);
}

const vector<Camera*>&	Scene::getCameras(void) const
{
  return (_cameras);
}

const vector<Object*>&	Scene::getObjects(void) const
{
  return (_objects);
}

const vector<Light*>&	Scene::getLights(void) const
{
  return (_lights);
}

const vector<Material*>& Scene::getMaterials(void) const
{
  return (_materials);
}

const Camera&		Scene::getCamera(int index) const
{
  return(*_cameras[index]);
}

const Object&		Scene::getObject(int index) const
{
  return(*_objects[index]);
}

const Light&		Scene::getLight(int index) const
{
  return(*_lights[index]);
}

const Material&		Scene::getMaterial(int index) const
{
  return(*_materials[index]);
}

int			Scene::getNbCameras(void) const
{
  return(_cameras.size());
}

int			Scene::getNbObjects(void) const
{
  return(_objects.size());
}

int			Scene::getNbLights(void) const
{
  return(_lights.size());
}

int			Scene::getNbMaterials(void) const
{
  return(_materials.size());
}

void			Scene::_putError(string		msg,
					 QDomNode	n)
{
  stringstream	ss;

  if (n.lineNumber() != -1)
    ss << msg << " at line " << n.lineNumber() << endl;
  else
    ss << msg << endl;
  if (this->_interface != NULL)
    this->_interface->sendErrorMessage(ss.str());
  else
    cerr << "Parse error: " << ss.str();
  this->_hasError = true;
}

void			Scene::_putError(string		msg)
{
  if (this->_interface != NULL)
    this->_interface->sendErrorMessage(msg + "\n");
  else
    cerr << "Parse error: " << msg << endl;
  this->_hasError = true;
}

void			Scene::_putSuccess(string		msg)
{
  if (this->_interface != NULL)
    this->_interface->sendSuccessMessage(msg + "\n");
  else
    cerr << "Success: " << msg << endl;
}

void			Scene::_putInfo(string		msg)
{
  if (this->_interface != NULL)
    this->_interface->sendMessage(msg + "\n");
  else
    cout << "Info: " << msg << endl;
}

void			Scene::_putWarning(string	msg,
					   QDomNode	n)
{
  stringstream	ss;

  if (n.lineNumber() != -1)
    ss << msg << " at line " << n.lineNumber() << endl;
  else
    ss << msg << endl;
  if (this->_interface != NULL)
    this->_interface->sendWarningMessage(ss.str());
  else
    cerr << "Warning: " << ss.str();
}

bool			Scene::_checkContentIsSingleText(QDomNode	n,
							 string		obj)
{
  if (n.isElement() == false || n.hasChildNodes() == false
      || n.childNodes().count() != 1 || n.firstChild().isText() == false)
  {
    this->_putError("A " + obj + " must be an element with a text value", n);
    return false;
  }
  return true;
}

Point			Scene::_parsePosition(QDomNode	n,
					      string name)
{
  QStringList	values;
  bool		test[3] = {false, false, false};
  Point		p;

  if (this->_checkContentIsSingleText(n, name))
  {
    values = n.toElement().text().remove(QChar(' ')).split(",");
    if (values.count() == 3)
      p = Point(values[0].toDouble(&test[0]),
		values[1].toDouble(&test[1]),
		values[2].toDouble(&test[2]));
    if (!test[0] || !test[1] || !test[2])
      this->_putError("A " + name + " must have 3 integers values separated "
		      "with comma", n);
  }
  else
    p = Point(0, 0, 0);
  return p;
}

Rotation		Scene::_parseRotation(QDomNode	n)
{
  QStringList		values;
  bool			test[3] = {false, false, false};
  Rotation		r;
  bool			radian = true;

  if (this->_checkContentIsSingleText(n, "rotation"))
  {
    if (n.hasAttributes() == false || n.attributes().contains("type") == false)
      this->_putWarning("Rotation type not specified, assuming radian", n);
    else
    {
      QString	AttrValue = n.attributes().namedItem("type").nodeValue();
      if ( AttrValue == "degree")
	radian = false;
      else if (AttrValue != "radian")
      {
	r = Rotation(0, 0, 0);
	this->_putError("Rotation type " + AttrValue.toStdString() +
			" does not exists", n);
      }
    }
    if (this->_hasError == false)
    {
      values = n.toElement().text().remove(QChar(' ')).split(",");
      if (values.count() == 3)
	r = Rotation(values[0].toDouble(&test[0]) * ((radian) ? (1)
						     : (M_PI / 180)),
		     values[1].toDouble(&test[1]) * ((radian) ? (1)
						     : (M_PI / 180)),
		     values[2].toDouble(&test[2]) * ((radian) ? (1)
						     : (M_PI / 180)));
      if (!test[0] || !test[1] || !test[2])
	this->_putError("A rotation must have 3 integers values "
			"separated with comma", n);
    }
  }
  else
    r = Rotation(0, 0, 0);
  return r;
}

bool			Scene::_isInt(QString	str)
{
  bool	value;

  str.toInt(&value, 10);
  return value;
}

bool			Scene::_isHexa(QString	str)
{
  bool	value;

  str.toInt(&value, 16);
  return value;
}

bool			Scene::_isDouble(QString	str)
{
  bool	value;

  str.toDouble(&value);
  return value;
}

double			Scene::_parseDouble(QDomNode	n,
					    double	min,
					    double	max,
					    string	name)
{
  double		value = 0;
  bool			test = false;
  stringstream		ss;

  if (this->_checkContentIsSingleText(n, name))
  {
    value = n.toElement().text().toDouble(&test);
    if (test == false)
      this->_putError(name + " must be a double", n);
    if (min != max)
    {
      if (value < min || value > max)
      {
	ss << name << " range is " << min << " <= x <= " << max;
	this->_putError(ss.str(), n);
      }
    }
  }
  return value;
}

bool			Scene::_parseBoolean(QDomNode	n,
					     string	name)
{
  string		value;

  if (this->_checkContentIsSingleText(n, name))
  {
    value = n.toElement().text().toStdString();
    if (value == "false")
      return false;
    else if (value == "true")
      return true;
    this->_putError(name + " must be a boolean", n);
  }
  return false;
}

int			Scene::_parseInt(QDomNode	n,
					 int		min,
					 int		max,
					 string		name)
{
  int			value = 0;
  bool			test = false;
  stringstream		ss;

  if (this->_checkContentIsSingleText(n, name))
  {
    value = n.toElement().text().toInt(&test);
    if (test == false)
      this->_putError(name + " must be an integer", n);
    if (min != max)
    {
      if (value < min || value > max)
      {
	ss << name << " range is " << min << " <= x <= " << max;
	this->_putError(ss.str(), n);
      }
    }
  }
  return value;
}

QRgb			Scene::_parseColor(QDomNode	n)
{
  QColor		color;
  QString		value;
  int			a = 255;
  int			r = 0;
  int			g = 0;
  int			b = 0;

  if (this->_checkContentIsSingleText(n, "color"))
  {
    value = n.toElement().text().remove(QChar(' '));
    if (value.contains(',') == false && (value.length() == 6))
    {
      if (this->_isHexa(value.mid(0, 2)) == false
	  || this->_isHexa(value.mid(2, 2)) == false
	  || this->_isHexa(value.mid(4, 2)) == false)
      {
	this->_putError("Wrong color value", n);
	r = g = b = 0;
      }
      else
      {
	r = value.mid(0, 2).toInt(NULL, 16);
	g = value.mid(2, 2).toInt(NULL, 16);
	b = value.mid(4, 2).toInt(NULL, 16);
      }
    }
    else if (value.contains(',') == false && (value.length() == 8))
    {
      if (this->_isHexa(value.mid(0, 2)) == false
	  || this->_isHexa(value.mid(2, 2)) == false
	  || this->_isHexa(value.mid(4, 2)) == false
	  || this->_isHexa(value.mid(6, 2)) == false)
      {
	r = g = b = 0;
	this->_putError("Wrong color value", n);
      }
      else
      {
	a = value.mid(0, 2).toInt(NULL, 16);
	r = value.mid(2, 2).toInt(NULL, 16);
	g = value.mid(4, 2).toInt(NULL, 16);
	b = value.mid(6, 2).toInt(NULL, 16);
      }
    }
    else if (value.contains(','))
    {
      QStringList		values = value.split(",");
      if (values.count() == 3 || values.count() == 4)
      {
	if (this->_isInt(values[0]) == false
	    || this->_isInt(values[1]) == false
	    || this->_isInt(values[2]) == false
	    || (values.count() != 3 && this->_isInt(values[3]) == false))
	{
	  r = g = b = 0;
	  this->_putError("Wrong color value", n);
	}
	r = values[0].toInt(NULL, 10);
	g = values[1].toInt(NULL, 10);
	b = values[2].toInt(NULL, 10);
	if (value.count() == 4)
	  a = values[2].toInt(NULL, 10);
      }
      else
      {
	r = g = b = 0;
	this->_putError("Wrong color value", n);
      }
    }
    else
    {
      r = g = b = 0;
      this->_putError("Wrong color value", n);
    }
  }
  else
    r = g = b = 0;
  if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255
      || a < 0 || a > 255)
  {
    this->_putError("Wrong color range (0 <= x <= 255 (FF))", n);
    r = g = b = a = -1;
  }
  color.setRgb(r, g, b, a);
  return (a != -1) ? color.rgba() : color.rgb();
}

string			Scene::_parseFile(QDomNode	n,
					  string	obj)
{
  QString		value;

  if (this->_checkContentIsSingleText(n, obj))
  {
    value = n.toElement().text();
    if (QFileInfo(value).exists() == false)
      this->_putError("The file " + value.toStdString() + " does not exists",
		      n);
  }
  else
    value = "empty";
  return (value.toStdString());
}

void		Scene::loadFromFile(string		filename,
				    RenderingInterface*	interface)
{
  bool		has_cameras = false;
  bool		has_materials = false;
  bool		has_objects = false;
  bool		has_lights = false;
  QDomDocument	document;

  this->_hasError = false;
  this->_parsingDone = false;
  this->_interface = interface;
  this->_interface->sendMessage("Start parsing " + filename);
  document = this->_loadFromFile_checkAndGetFile(filename);
  if (this->_hasError == false)
  {
    QDomElement	docElem = document.documentElement();
    QDomNode	node = docElem.firstChild();

    while (node.isNull() == false && this->_hasError == false)
    {
      if (this->_loadFromFile_validFirstDepth(node))
	this->_dispatcher(node, has_cameras, has_materials,
			  has_objects, has_lights);
      node = node.nextSibling();
    }
    if (this->_hasError == false)
    {
      if (has_cameras == false)
	this->_putError("A scene must have a camera.");
    }
  }
  this->_parsingDone = true;
  if (this->isValid())
    this->_putSuccess("Parsing finished");
  else
    this->_putError("Parsing exited abnormally");
}

void			Scene::_dispatcher(QDomNode	node,
					   bool&	has_cameras,
					   bool&	has_materials,
					   bool&	has_objects,
					   bool&	has_lights)
{
  if (node.nodeName() == "cameras")
  {
    if (has_cameras)
      this->_putWarning("Several cameras elements found. Dude, that's dirty!",
			node);
    this->_parseCameras(node);
    has_cameras = true;
  }
  else if (node.nodeName() == "materials")
  {
    if (has_materials)
      this->_putWarning("Several materials elements found."
			"Dude, that's dirty!", node);
    this->_parseMaterials(node);
    has_materials = true;
  }
  else if (node.nodeName() == "objects")
  {
    if (has_objects)
      this->_putWarning("Several objects elements found."
			"Dude, that's dirty!", node);
    this->_parseObjects(node);
    has_objects = true;
  }
  else if (node.nodeName() == "lights")
  {
    if (has_lights)
      this->_putWarning("Several lights elements found."
			"Dude, that's dirty!", node);
    this->_parseLights(node);
    has_lights = true;
  }
}

bool			Scene::_loadFromFile_validFirstDepth(QDomNode n)
{
  if (n.nodeName() != "cameras"
      && n.nodeName() != "materials"
      && n.nodeName() != "lights"
      && n.nodeName() != "objects")
    this->_putError(n.nodeName().toStdString() + " isn't a valid name.", n);
  if (n.hasChildNodes() == false)
    this->_putError(n.nodeName().toStdString() + " has no childs.", n);
  return (this->_hasError == false);
}

QDomDocument		Scene::_loadFromFile_checkAndGetFile(string filename)
{
  stringstream	ss;
  QFile		file(filename.c_str());
  QDomDocument	document("scene");
  int		errorLine;
  int		errorCol;
  QString	errorMsg;

  if (file.open(QIODevice::ReadOnly))
  {
    if (document.setContent(&file, &errorMsg, &errorLine, &errorCol) == false)
    {
      ss << errorMsg.toStdString() << " at line " << errorLine << ".";
      this->_putError(ss.str());
    }
    file.close();
  }
  else
    this->_putError("The file \"" + filename + "\" doesn't exists or " +
		    "is not readable.");
  return document;
}
