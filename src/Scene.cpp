//
// Scene.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
//
// Made by loick michard
// Login   <michar_l@epitech.net>
//
// Started on  Wed Apr 27 18:24:15 2011 loick michard
// Last update Thu May 12 00:04:48 2011 melvin laplanche
//

#include "Scene.hpp"

Scene::Scene(vector<Camera*> cameras,
	     vector<Object*> objects,
	     vector<Light*> lights):
  _cameras(cameras), _objects(objects), _lights(lights)
{

}

Scene::Scene(vector<Camera*> cameras,
	     vector<Object*> objects,
	     vector<Light*> lights,
	     vector<Material*> materials):
  _cameras(cameras), _objects(objects), _lights(lights), _materials(materials)
{

}

Scene::Scene(void) { }

Scene::Scene(string filename)
{
  this->loadFromFile(filename);
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
  if (n.lineNumber() != -1)
    cerr << "Parse error: " << msg << " at line " << n.lineNumber() << endl;
  else
    cerr << "Parse error: " << msg << endl;
  exit(1);
}

void			Scene::_putWarning(string	msg,
					   QDomNode	n)
{
  if (n.lineNumber() != -1)
    cerr << "Warning: " << msg << " at line " << n.lineNumber() << endl;
  else
    cerr << "Warning: " << msg << endl;
}

void			Scene::_checkContentIsSingleText(QDomNode	n,
							 string		obj)
{
  if (n.isElement() == false || n.hasChildNodes() == false
      || n.childNodes().count() != 1 || n.firstChild().isText() == false)
    this->_putError("A " + obj + " must be an element with a text value", n);
}

Point			Scene::_parsePosition(QDomNode	n,
					      string name)
{
  QStringList	values;
  bool		test[3] = {false, false, false};
  Point		p;

  this->_checkContentIsSingleText(n, name);
  values = n.toElement().text().remove(QChar(' ')).split(",");
  if (values.count() == 3)
    p = {values[0].toDouble(&test[0]),
	 values[1].toDouble(&test[1]),
	 values[2].toDouble(&test[2])};
  if (!test[0] || !test[1] || !test[2])
    this->_putError("A " + name + " must have 3 integers values separated "
		    "with comma", n);
  return p;
}

Rotation		Scene::_parseRotation(QDomNode	n)
{
  QStringList		values;
  bool			test[3] = {false, false, false};
  Rotation		r;
  bool			radian = true;

  this->_checkContentIsSingleText(n, "rotation");
  if (n.hasAttributes() == false || n.attributes().contains("type") == false)
    this->_putWarning("Rotation type not specified, assuming radian", n);
  else
  {
    QString	AttrValue = n.attributes().namedItem("type").nodeValue();
    if ( AttrValue == "degree")
      radian = false;
    else if (AttrValue != "radian")
      this->_putError("Rotation type " + AttrValue.toStdString() +
		      " does not exists", n);
  }
  values = n.toElement().text().remove(QChar(' ')).split(",");
  if (values.count() == 3)
    r = {values[0].toDouble(&test[0]) * ((radian) ? (1) : (M_PI / 180)),
	 values[1].toDouble(&test[1]) * ((radian) ? (1) : (M_PI / 180)),
	 values[2].toDouble(&test[2]) * ((radian) ? (1) : (M_PI / 180))};
  if (!test[0] || !test[1] || !test[2])
    this->_putError("A rotation must have 3 integers values "
		    "separated with comma", n);
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
  double		value;
  bool			test = false;
  stringstream		ss;

  this->_checkContentIsSingleText(n, name);
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
  return value;
}

bool			Scene::_parseBoolean(QDomNode	n,
					     string	name)
{
  string		value;

  this->_checkContentIsSingleText(n, name);
  value = n.toElement().text().toStdString();
  if (value == "false")
    return false;
  else if (value == "true")
    return true;
  this->_putError(name + " must be a boolean", n);
}

int			Scene::_parseInt(QDomNode	n,
					 int		min,
					 int		max,
					 string		name)
{
  int			value;
  bool			test = false;
  stringstream		ss;

  this->_checkContentIsSingleText(n, name);
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
  return value;
}

QRgb			Scene::_parseColor(QDomNode	n)
{
  QColor		color;
  QString		value;
  int			a = 255;
  int			r;
  int			g;
  int			b;

  this->_checkContentIsSingleText(n, "color");
  value = n.toElement().text().remove(QChar(' '));
  if (value.contains(',') == false && (value.length() == 6))
  {
    if (this->_isHexa(value.mid(0, 2)) == false
	|| this->_isHexa(value.mid(2, 2)) == false
	|| this->_isHexa(value.mid(4, 2)) == false)
      this->_putError("Wrong color value", n);
    r = value.mid(0, 2).toInt(NULL, 16);
    g = value.mid(2, 2).toInt(NULL, 16);
    b = value.mid(4, 2).toInt(NULL, 16);
  }
  else if (value.contains(',') == false && (value.length() == 8))
  {
    if (this->_isHexa(value.mid(0, 2)) == false
	|| this->_isHexa(value.mid(2, 2)) == false
	|| this->_isHexa(value.mid(4, 2)) == false
	|| this->_isHexa(value.mid(6, 2)) == false)
      this->_putError("Wrong color value", n);
    a = value.mid(0, 2).toInt(NULL, 16);
    r = value.mid(2, 2).toInt(NULL, 16);
    g = value.mid(4, 2).toInt(NULL, 16);
    b = value.mid(6, 2).toInt(NULL, 16);
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
      this->_putError("Wrong color value", n);
      r = values[0].toInt(NULL, 10);
      g = values[1].toInt(NULL, 10);
      b = values[2].toInt(NULL, 10);
      if (value.count() == 4)
	a = values[2].toInt(NULL, 10);
    }
    else
      this->_putError("Wrong color value", n);
  }
  else
    this->_putError("Wrong color value", n);
  if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255
      || a < 0 || a > 255)
    this->_putError("Wrong color range (0 <= x <= 255 (FF))", n);
  color.setRgb(r, g, b, a);
  return (a != -1) ? color.rgba() : color.rgb();
}

void			Scene::_parseNormalDef(QDomNode	n,
					       Material	*mat)
{
  QString		value;
  QString		attrValue;

  if (n.hasAttributes() == false || n.attributes().contains("type") == false)
    this->_putError("normalDeformation type not specified", n);
  this->_checkContentIsSingleText(n, "normalDeformation");
  attrValue = n.attributes().namedItem("type").nodeValue();
  value = n.toElement().text();
  if (this->_isInt(value) == false)
    this->_putError("normalDeformation value must be an integer", n);
  if (this->_isInt(attrValue) == false)
    this->_putError("normalDeformation type must be an integer", n);
  mat->setNormalDeformation(attrValue.toInt(NULL, 10), value.toInt(NULL, 10));
}

string			Scene::_parseFile(QDomNode	n,
					  string	obj)
{
  QString		value;

  this->_checkContentIsSingleText(n, obj);
  value = n.toElement().text();
  if (QFileInfo(value).exists() == false)
    this->_putError("The file " + value.toStdString() + " does not exists", n);
  return (value.toStdString());
}

void		Scene::loadFromFile(string filename)
{
  bool		has_cameras = false;
  bool		has_materials = false;
  bool		has_objects = false;
  bool		has_lights = false;
  QDomDocument	document = this->_loadFromFile_checkAndGetFile(filename);
  QDomElement	docElem = document.documentElement();
  QDomNode	node = docElem.firstChild();

  while (node.isNull() == false)
  {
    this->_loadFromFile_validFirstDepth(node);
    this->_dispatcher(node, has_cameras, has_materials,
		      has_objects, has_lights);
    node = node.nextSibling();
  }
  cout << "D: Parser out" << endl;
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

void			Scene::_loadFromFile_validFirstDepth(QDomNode n)
{
  if (n.nodeName() != "cameras"
      && n.nodeName() != "materials"
      && n.nodeName() != "lights"
      && n.nodeName() != "objects")
    this->_putError(n.nodeName().toStdString() + " isn't a valid name.", n);
  if (n.hasChildNodes() == false)
    this->_putError(n.nodeName().toStdString() + " has no childs.", n);
}

QDomDocument		Scene::_loadFromFile_checkAndGetFile(string filename)
{
  QFile		file(filename.c_str());
  QDomDocument	document("scene");
  int		errorLine;
  int		errorCol;
  QString	errorMsg;

  if (file.open(QIODevice::ReadOnly) == false)
  {
    cerr << "Error: The file \"" << filename << "\" doesn't exists or " <<
	     "is not readable" << endl;
    exit(1);
  }
  if (document.setContent(&file, &errorMsg, &errorLine, &errorCol) == false)
  {
    file.close();
    cerr << "Error: " << errorMsg.toStdString() << " at line " << errorLine
	 << "." << endl;
    exit(1);
  }
  file.close();
  return document;
}
