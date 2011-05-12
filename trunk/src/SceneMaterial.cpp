//
// SceneMaterial.cpp for  in /home/laplan_m/Src/Epitech/Projects/C++/raytracer-42
//
// Made by melvin laplanche
// Login   <laplan_m@epitech.net>
//
// Started on  Wed May 11 16:59:26 2011 melvin laplanche
// Last update Thu May 12 17:07:16 2011 gael jochaud-du-plessix
//

#include "Scene.hpp"

void			Scene::_failIfMaterialNameExists(QString	name,
							 QDomNode	n)
{
  int		nbMat = this->_materials.size();
  string	toFind = name.toStdString();

  for (int i = 0; i < nbMat; i++)
    if (this->_materials[i]->getName() == toFind)
      this->_putError("The material " + toFind + " already exists", n);
}

void			Scene::_failIfMaterialNameDoesntExists(QString	name,
							       QDomNode	n)
{
  int		nbMat = this->_materials.size();
  string	toFind = name.toStdString();

  for (int i = 0; i < nbMat; i++)
  {
    if (this->_materials[i]->getName() == toFind)
      return ;
  }
  this->_putError("The material " + toFind + " doesnt exists"
		  " (you must define a material before use it)", n);
}


Material		Scene::_getMaterialByName(QString	name)
{
  int		nbMat = this->_materials.size();
  string	toFind = name.toStdString();

  for (int i = 0; i < nbMat; i++)
    if (this->_materials[i]->getName() == toFind)
      return *_materials[i];
  return (Material());
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

  while (n.isNull() == false)
  {
    if (n.hasChildNodes() == false || n.isElement() == false)
      this->_putError("Every material children must be an element", n);
    if (n.nodeName() == "color")
    {
      if (color)
	this->_putWarning("A material has several colors, "
			  "the first defined will be used", n);
      else
      {
	mat->setColor(this->_parseColor(n));
	color = true;
      }
    }
    else if (n.nodeName() == "heightmap")
    {
      if (heightmap)
	this->_putWarning("A material has several heightmaps, "
			  "the first defined will be used", n);
      else
      {
	mat->setHeightmap(this->_parseTexture(n, "heightmap"));
	heightmap = true;
      }
    }
    else if (n.nodeName() == "texture")
    {
      if (texture)
	this->_putWarning("A material has several textures, "
			  "the first defined will be used", n);
      else
      {
	mat->setTexture(this->_parseTexture(n, "texture"));
	texture = true;
      }
    }
    else if (n.nodeName() == "limitTexture")
    {
      if (limitTexture)
	this->_putWarning("A material has several limitTextures, "
			  "the first defined will be used", n);
      else
      {
	mat->setLimitTexture(this->_parseTexture(n, "limitTexture"));
	limitTexture = true;
      }
    }
    else if (n.nodeName() == "specular")
    {
      if (specular)
	this->_putWarning("A material has several speculars, "
			  "the first defined will be used", n);
      else
      {
	mat->setSpecularCoeff(this->_parseDouble(n, 0, 0, "specular"));
	specular = true;
      }
    }
    else if (n.nodeName() == "specularPow")
    {
      if (specularPow)
	this->_putWarning("A material has several specularPows, "
			  "the first defined will be used", n);
      else
      {
	mat->setSpecularPow(this->_parseDouble(n, 0, 0, "specularPow"));
	specularPow = true;
      }
    }
    else if (n.nodeName() == "reflection")
    {
      if (reflection)
	this->_putWarning("A material has several reflections, "
			  "the first defined will be used", n);
      else
      {
	mat->setReflectionCoeff(this->_parseDouble(n, 0, 0, "reflection"));
	reflection = true;
      }
    }
    else if (n.nodeName() == "transmission")
    {
      if (transmission)
	this->_putWarning("A material has several transmissions, "
			  "the first defined will be used", n);
      else
      {
	mat->setTransmissionCoeff(_parseDouble(n, 0, 0, "transmission"));
	transmission = true;
      }
    }
    else if (n.nodeName() == "refractionIndex")
    {
      if (refractionIndex)
	this->_putWarning("A material has several refractionIndexs, "
			  "the first defined will be used", n);
      else
      {
	mat->setRefractionIndex(_parseDouble(n, 0, 0, "refractionIndex"));
	refractionIndex = true;
      }
    }
    else if (n.nodeName() == "diffusedReflection")
    {
      if (diffusedRef)
	this->_putWarning("A material has several diffusedReflections, "
			  "the first defined will be used", n);
      else
      {
	mat->setDiffusedReflectionCoeff(this->_parseInt(n, 0, 0,
						  "diffusedReflection"));
	diffusedRef = true;
      }
    }
    else if (n.nodeName() == "diffusedReflection")
    {
      if (diffusedRef)
	this->_putWarning("A material has several diffusedReflections, "
			  "the first defined will be used", n);
      else
      {
	mat->setDiffusedReflectionCoeff(this->_parseInt(n, 0, 0,
							"diffusedReflection"));
	diffusedRef = true;
      }
    }
    else if (n.nodeName() == "normalDeformation")
    {
      if (normalDef)
	this->_putWarning("A material has several normalDeformations, "
			  "the first defined will be used", n);
      else
      {
	this->_parseNormalDef(n, mat);
	normalDef = true;
      }
    }
    else
      this->_putError(n.nodeName().toStdString() + " is not a valid element",
		      n);
    n = n.nextSibling();
  }
  this->_materials.push_back(mat);
}

void			Scene::_parseMaterial(QDomNode n)
{
  QDomNamedNodeMap	nodeMap;
  QString		name;

  while (n.isNull() == false)
  {
    if (n.nodeName() != "material" || n.isElement() == false)
      this->_putError("A materials child cannot be empty and must be a "
			"material element", n);
    if (n.hasChildNodes() == false)
      this->_putError("A material element cannot be empty", n);
    if (n.hasAttributes() == false|| n.attributes().contains("name") == false)
      this->_putError("The material attributes are missing", n);
    name = n.attributes().namedItem("name").nodeValue();
    this->_failIfMaterialNameExists(name, n);
    this->_parseMaterialOptions(n.firstChild(), name);
    n = n.nextSibling();
  }
}

void			Scene::_parseMaterials(QDomNode n)
{
  if (n.hasChildNodes() == false)
    this->_putError("A materials element cannot be empty", n);
  this->_parseMaterial(n.firstChild());
}


Texture*			Scene::_parseTexture(QDomNode	n,
						     string	obj_name)
{
  PerlinNoise		*perlin = new PerlinNoise();
  QString		value;
  QString		attrValue;

  if (n.hasAttributes() == false || n.attributes().contains("type") == false)
    this->_putError(obj_name + " type not specified", n);
  this->_checkContentIsSingleText(n, obj_name);
  attrValue = n.attributes().namedItem("type").nodeValue();
  value = n.toElement().text();
  if (attrValue == "procedural")
  {
    if (value == "marble")
      perlin->setMarbleProperties();
    else if (value == "wood")
      perlin->setWoodProperties();
    else if (value != "perlin")
      this->_putError(value.toStdString() + " is not a valid texture", n);
    return perlin;
  }
  else if (attrValue == "file")
    return new Texture(this->_parseFile(n, obj_name));
  this->_putError("normalDeformation type must be an integer", n);
  return (NULL);
}
