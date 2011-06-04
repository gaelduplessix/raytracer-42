//
// SceneMaterial.cpp for  in /home/laplan_m/Src/Epitech/Projects/C++/raytracer-42
//
// Made by melvin laplanche
// Login   <laplan_m@epitech.net>
//
// Started on  Wed May 11 16:59:26 2011 melvin laplanche
// Last update Sat Jun  4 18:50:53 2011 melvin laplanche
//

#include "Scene.hpp"
#include "CheckerBoard.hpp"

void			Scene::_parseNormalDef(QDomNode	n,
					       Material	*mat)
{
  QString		value;
  QString		attrValue;

  if (n.hasAttributes() == false || n.attributes().contains("type") == false)
  {
    this->_putError(QObject::tr("normalDeformation type not specified"), n);
    return ;
  }
  else if (this->_checkContentIsSingleText(n, "normalDeformation"))
  {
    attrValue = n.attributes().namedItem("type").nodeValue();
    value = n.toElement().text();
    if (this->_isInt(value) == false)
    {
      this->_putError(QObject::tr("normalDeformation value must be an integer")
		      , n);
      return ;
    }
    if (this->_isInt(attrValue) == false)
    {
      this->_putError(QObject::tr("normalDeformation type must be an integer"),
		      n);
      return ;
    }
    mat->setNormalDeformation(attrValue.toInt(NULL, 10),
			      value.toInt(NULL, 10));
  }
}

bool			Scene::_materialExists(QString	name)
{
  int		nbMat = this->_materials.size();
  string	toFind = name.toStdString();

  for (int i = 0; i < nbMat; i++)
  {
    if (this->_materials[i]->getName() == toFind)
      return true;
  }
  return false;
}

Material*		Scene::_getMaterialByName(QString	name)
{
  int		nbMat = this->_materials.size();
  string	toFind = name.toStdString();

  for (int i = 0; i < nbMat; i++)
    if (this->_materials[i]->getName() == toFind)
      return _materials[i];
  return (NULL);
}

void			Scene::_parseMaterialOptions(QDomNode	n,
						     QString	name)
{
  Material	*mat = new Material(name.toStdString());
  bool		color = false;
  bool		texture = false;
  bool		limitTexture = false;
  bool		specular = false;
  bool		specularPow = false;
  bool		reflection = false;
  bool		transmission = false;
  bool		refractionIndex = false;
  bool		heightmap = false;
  bool		normalDef = false;
  bool		diffusedRef = false;

  while (n.isNull() == false && this->_hasError == false)
  {
    if (n.isComment() == false)
    {
      if (n.hasChildNodes() == false || n.isElement() == false)
      {
	this->_putError(QObject::tr("Every material children must "
				    "be an element"), n);
	return ;
      }
      if (n.nodeName() == "color")
      {
	if (color)
	  this->_putWarning(QObject::tr("A material has several colors, "
					"the first defined will be used"), n);
	else
	{
	  mat->setColor(this->_parseColor(n));
	  color = true;
	}
      }
      else if (n.nodeName() == "heightmap")
      {
	if (heightmap)
	  this->_putWarning(QObject::tr("A material has several heightmaps, "
					"the first defined will be used"), n);
	else
	{
	  mat->setHeightmap(this->_parseTexture(n, "heightmap"));
	  heightmap = true;
	}
      }
      else if (n.nodeName() == "texture")
      {
	if (texture)
	  this->_putWarning(QObject::tr("A material has several textures, "
					"the first defined will be used"), n);
	else
	{
	  mat->setTexture(this->_parseTexture(n, "texture"));
	  texture = true;
	}
      }
      else if (n.nodeName() == "limitTexture")
      {
	if (limitTexture)
	  this->_putWarning(QObject::tr("A material has several "
					"limitTextures, "
					"the first defined will be used"), n);
	else
	{
	  mat->setLimitTexture(this->_parseTexture(n, "limitTexture"));
	  limitTexture = true;
	}
      }
      else if (n.nodeName() == "specular")
      {
	if (specular)
	  this->_putWarning(QObject::tr("A material has several speculars, "
					"the first defined will be used"), n);
	else
	{
	  mat->setSpecularCoeff(this->_parseDouble(n, 0, 0, "specular"));
	  specular = true;
	}
      }
      else if (n.nodeName() == "specularPow")
      {
	if (specularPow)
	  this->_putWarning(QObject::tr("A material has several specularPows, "
					"the first defined will be used"), n);
	else
	{
	  mat->setSpecularPow(this->_parseDouble(n, 0, 0, "specularPow"));
	  specularPow = true;
	}
      }
      else if (n.nodeName() == "reflection")
      {
	if (reflection)
	  this->_putWarning(QObject::tr("A material has several reflections, "
					"the first defined will be used"), n);
	else
	{
	  mat->setReflectionCoeff(this->_parseDouble(n, 0, 0, "reflection"));
	  reflection = true;
	}
      }
      else if (n.nodeName() == "transmission")
      {
	if (transmission)
	  this->_putWarning(QObject::tr("A material has several "
					"transmissions, "
					"the first defined will be used"), n);
	else
	{
	  mat->setTransmissionCoeff(_parseDouble(n, 0, 0, "transmission"));
	  transmission = true;
	}
      }
      else if (n.nodeName() == "refractionIndex")
      {
	if (refractionIndex)
	  this->_putWarning(QObject::tr("A material has several "
					"refractionIndexs, the first defined "
					"will be used"), n);
	else
	{
	  mat->setRefractionIndex(_parseDouble(n, 0, 0, "refractionIndex"));
	  refractionIndex = true;
	}
      }
      else if (n.nodeName() == "diffusedReflection")
      {
	if (diffusedRef)
	  this->_putWarning(QObject::tr("A material has several "
					"diffusedReflections, "
					"the first defined will be used"), n);
	else
	{
	  mat->setDiffusedReflectionCoeff(
	    this->_parseDouble(n, 0, 0, "diffusedReflection"));
	  diffusedRef = true;
	}
      }
      else if (n.nodeName() == "diffusedReflection")
      {
	if (diffusedRef)
	  this->_putWarning(QObject::tr("A material has several "
					"diffusedReflections, "
					"the first defined will be used"), n);
	else
	{
	  mat->setDiffusedReflectionCoeff(
	    this->_parseInt(n, 0, 0, "diffusedReflection"));
	  diffusedRef = true;
	}
      }
      else if (n.nodeName() == "normalDeformation")
      {
	if (normalDef)
	  this->_putWarning(QObject::tr("A material has several "
					"normalDeformations, "
					"the first defined will be used"), n);
	else
	{
	  this->_parseNormalDef(n, mat);
	  normalDef = true;
	}
      }
      else
	this->_putError(QObject::tr("%1 is not a valid element")
			.arg(n.nodeName()), n);
    }
    n = n.nextSibling();
  }
  if (this->_hasError == false)
    this->_materials.push_back(mat);
}

void			Scene::_parseMaterial(QDomNode n)
{
  QDomNamedNodeMap	nodeMap;
  QString		name;

  while (n.isNull() == false && this->_hasError == false)
  {
    if (n.isComment() == false)
    {
      if (n.nodeName() != "material" || n.isElement() == false)
      {
	this->_putError(QObject::tr("A materials child cannot be empty "
				    "and must be a material element"), n);
	return ;
      }
      if (n.hasChildNodes() == false)
      {
	this->_putError(QObject::tr("A material element cannot be empty"), n);
	return ;
      }
      if (n.hasAttributes() == false
	  || n.attributes().contains("name") == false)
      {
	this->_putError(QObject::tr("The material attributes are missing"), n);
	return ;
      }
      name = n.attributes().namedItem("name").nodeValue();
      if (this->_materialExists(name))
      {
	this->_putError(QObject::tr("The material %1 already exists")
			.arg(name),
			n);
	return ;
      }
      this->_parseMaterialOptions(n.firstChild(), name);
    }
    n = n.nextSibling();
  }
}

void			Scene::_parseMaterials(QDomNode n)
{
  if (n.hasChildNodes() == false)
  {
    this->_putError(QObject::tr("A materials element cannot be empty"), n);
    return ;
  }
 this->_parseMaterial(n.firstChild());
}


QString			Scene::_parseTextureType(QDomNode n,
						 string	  obj_name)
{
  QString		attrValue;

  if (n.hasAttributes() == false || n.attributes().contains("type") == false)
  {
    this->_putError(QObject::tr("%1 type not specified").arg(obj_name.c_str()),
		    n);
    return attrValue;
  }
  attrValue = n.attributes().namedItem("type").nodeValue();
  if (attrValue != "procedural" && attrValue != "file")
    this->_putError(QObject::tr("Wrong texture type"), n);
  return attrValue;
}

Texture*		Scene::_parseTextureSetTexture(QString type,
						       string  name,
						       QDomNode n)
{
  PerlinNoise		*perlin = new PerlinNoise();

  if (type == "procedural")
  {
    if (name == "marble")
      perlin->setMarbleProperties();
    else if (name == "wood")
      perlin->setWoodProperties();
    else if (name == "checkerboard")
      return (new CheckerBoard());
    else if (name != "perlin")
      this->_putError(QObject::tr("%1 is not a valid texture")
		      .arg(name.c_str()), n);
    return perlin;
  }
  else // file
    return new Texture(this->_parseFile(n, "texture"));
}

Texture*	Scene::_parseTexture(QDomNode	parent,
				     string	obj_name)
{
  Texture*	tex = NULL;
  QString	type = this->_parseTextureType(parent, obj_name);
  bool		hasName = false;
  string	name;
  bool		hasRepeatX = false;
  int		repeatX = 1;
  int		repeatY = 1;
  bool		hasRepeatY = false;
  bool		hasColor1 = false;
  bool		hasColor2 = false;
  QRgb		color2;
  QRgb		color1;
  QDomNode	n = parent.firstChild();

  while (n.isNull() == false && this->_hasError == false)
  {
    if (n.isComment() == false)
    {
      if (n.hasChildNodes() == false || n.isElement() == false)
      {
	this->_putError(QObject::tr("Every %1 children must "
				    "be an element").arg(obj_name.c_str()), n);
	return NULL;
      }
      if (n.nodeName() == "name")
      {
	if (hasName)
	  this->_putWarning(QObject::tr("A %1 has several filename, "
					"the first defined will be used")
			    .arg(obj_name.c_str()), n);
	else
	{
	  if (this->_checkContentIsSingleText(n, obj_name))
	  {
	    name = n.toElement().text().toStdString();
	    tex = _parseTextureSetTexture(type, name, n);
	  }
	  hasName = true;
	}
      }
      else if (n.nodeName() == "repeatX")
      {
	if (hasRepeatX)
	  this->_putWarning(QObject::tr("A %1 has several repeatX, "
					"the first defined will be used")
			    .arg(obj_name.c_str()), n);
	else
	{
	  repeatX = _parseInt(n, 0, 0, "repeatX");
	  hasRepeatX = true;
	}
      }
      else if (n.nodeName() == "repeatY")
      {
	if (hasRepeatY)
	  this->_putWarning(QObject::tr("A %1 has several repeatY, "
					"the first defined will be used")
			    .arg(obj_name.c_str()), n);
	else
	{
	  repeatY = _parseInt(n, 0, 0, "repeatY");
	  hasRepeatY = true;
	}
      }
      else if (n.nodeName() == "color1")
      {
	if (hasColor1)
	  this->_putWarning(QObject::tr("A %1 has several color1, "
					"the first defined will be used")
			    .arg(obj_name.c_str()), n);
	else
	{
	  color1 = _parseColor(n);
	  hasColor1 = true;
	}
      }
      else
	this->_putError(QObject::tr("%1 is not a valid element")
			.arg(n.nodeName()), n);
    }
    n = n.nextSibling();
  }
  if (hasName == false)
    this->_putError(QObject::tr("A %1 must have a name").arg(obj_name.c_str())
		    , n);
  if (this->_hasError == false)
  {
    if (hasRepeatX)
      tex->_repeatWidth = repeatX;
    if (hasRepeatY)
      tex->_repeatHeight = repeatY;
    if (hasColor1 && type == "procedural")
    {
      if (name == "perlin" || name == "wood" || name == "marble")
	((PerlinNoise*)tex)->setColor1(Color(color1));
      else if (name == "checkerboard")
	((CheckerBoard*)tex)->setColor1(Color(color1));
    }
    if (hasColor2 && type == "procedural")
    {
      if (name == "perlin" || name == "wood" || name == "marble")
	((PerlinNoise*)tex)->setColor2(Color(color2));
      else if (name == "checkerboard")
	((CheckerBoard*)tex)->setColor2(Color(color2));
    }
  }
  return tex;
}
