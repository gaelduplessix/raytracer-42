//
// Material.cpp for raytracer in /home/olivie_a//rendu/cpp/raytracer-42/src
//
// Made by samuel olivier
// Login   <olivie_a@epitech.net>
//
// Started on  Sun May  1 20:39:22 2011 samuel olivier
// Last update Sun Jun  5 16:12:32 2011 loick michard
//

#include "Material.hpp"

Material::Material():
  _name(""), _color(Color(255, 255, 255)), _isTextured(false),
  _specularCoeff(0), _specularPow(50), _reflectionCoeff(0),
  _transmissionCoeff(0), _refractionIndex(1), _diffusedReflectionCoeff(0.1),
  _texture(NULL), _limitTexture(NULL), _heightmap(NULL), _hasBumpMap(false),
  _hasNormalDeformation(false), _deformationType(-1), _deformationCoeff(10)
{

}

Material::Material(const string& name):
  _name(name), _color(Color(255, 255, 255)),
  _isTextured(false), _specularCoeff(0), _specularPow(50),
  _reflectionCoeff(0), _transmissionCoeff(0),
  _refractionIndex(1), _diffusedReflectionCoeff(0.1), _texture(NULL),
  _limitTexture(NULL), _heightmap(NULL), _hasBumpMap(false),
  _hasNormalDeformation(false), _deformationType(-1), _deformationCoeff(10)
{

}

Material::~Material()
{
  if (_texture)
    delete _texture;
  if (_limitTexture)
    delete _limitTexture;
  if (_heightmap)
    delete _heightmap;
}

string	Material::getName(void) const
{
  return (_name);
}

Color	Material::getColor(double x, double y) const
{
  if (_isTextured && _texture)
    return (_texture->getColor(x, y));
  return (_color);
}

Color   Material::getHeightmapColor(double x, double y) const
{
  if (_hasBumpMap && _heightmap)
    return (_heightmap->getColor(x, y));
  return (_color);
}

bool	Material::isLimitedAtPoint(double x, double y) const
{
  if (_limitTexture)
    return (_limitTexture->getColor(x, y)._a == 0);
  return (false);
}

double	Material::getSpecularCoeff(void) const
{
  return (_specularCoeff);
}

double	Material::getSpecularPow(void) const
{
  return (_specularPow);
}

double	Material::getReflectionCoeff(void) const
{
  return (_reflectionCoeff);
}

double	Material::getDiffusedReflectionCoeff(void) const
{
  return (_diffusedReflectionCoeff);
}

double	Material::getTransmissionCoeff(void) const
{
  return (_transmissionCoeff);
}

double	Material::getRefractionIndex(void) const
{
  return (_refractionIndex);
}

void	Material::setName(string name)
{
  _name = name;
}

void	Material::setColor(const Color& color)
{
  _color = color;
}

void	Material::setTexture(Texture* texture)
{
  if (_texture)
    delete _texture;
  _texture = texture;
  if (texture != NULL)
    _isTextured = true;
  else
    _isTextured = false;
}

void	Material::setLimitTexture(Texture* texture)
{
  _limitTexture = texture;
}

void	Material::setSpecularCoeff(double specularCoeff)
{
  _specularCoeff = specularCoeff;
}

void	Material::setSpecularPow(double specularPow)
{
  _specularPow = specularPow;
}

void	Material::setReflectionCoeff(double reflectionCoeff)
{
  _reflectionCoeff = reflectionCoeff;
}

void	Material::setDiffusedReflectionCoeff(double diffusedReflectionCoeff)
{
  _diffusedReflectionCoeff = diffusedReflectionCoeff;
}

void	Material::setTransmissionCoeff(double transmissionCoeff)
{
  _transmissionCoeff = transmissionCoeff;
}

void	Material::setRefractionIndex(double refractionIndex)
{
  _refractionIndex = refractionIndex;
}

void	Material::setNormalDeformation(int deformation,
				       int deformationCoeff)
{
  _hasNormalDeformation = 1;
  _deformationType = deformation;
  _deformationCoeff = deformationCoeff;
}

void	Material::setHeightmap(Texture* image)
{
  if (image)
    {
      if (_heightmap)
	delete _heightmap;
      _heightmap = image;
      _hasBumpMap = true;
      _hasNormalDeformation = true;
    }
  else
    {
      if (_heightmap)
	delete _heightmap;
      _heightmap = NULL;
      _hasBumpMap = false;
    }
}

