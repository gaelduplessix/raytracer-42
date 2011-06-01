//
// SceneMaterial.cpp for  in /home/laplan_m/Src/Epitech/Projects/C++/raytracer-42
//
// Made by melvin laplanche
// Login   <laplan_m@epitech.net>
//
// Started on  Wed May 11 16:59:26 2011 melvin laplanche
// Last update Wed Jun  1 19:57:22 2011 gael jochaud-du-plessix
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


Texture*			Scene::_parseTexture(QDomNode	n,
						     string	obj_name)
{
  PerlinNoise		*perlin = new PerlinNoise();
  QString		value;
  QString		attrValue;

  if (n.hasAttributes() == false || n.attributes().contains("type") == false)
  {
    this->_putError(QObject::tr("%1 type not specified").arg(obj_name.c_str()),
		    n);
    return perlin;
  }
  if (!this->_checkContentIsSingleText(n, obj_name))
    return perlin;
  attrValue = n.attributes().namedItem("type").nodeValue();
  value = n.toElement().text();
  if (attrValue == "procedural")
  {
    if (value == "marble")
      perlin->setMarbleProperties();
    else if (value == "wood")
      perlin->setWoodProperties();
    else if (value == "checkerboard")
      return (new CheckerBoard());
    else if (value != "perlin")
      this->_putError(QObject::tr("%1 is not a valid texture").arg(value), n);
    return perlin;
  }
  else if (attrValue == "file")
    return new Texture(this->_parseFile(n, obj_name));
  this->_putError(QObject::tr("normalDeformation type must be an integer"), n);
  return (perlin);
}
