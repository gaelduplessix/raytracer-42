#include "Material.hpp"

Material::Material(): _isTextured(false)
{

}

Material::Material(const string& name): _isTextured(false)
{

}

Material::Material(const Texture& texture): _isTextured(false)
{

}

string	Material::getName(void) const
{
  return (_name);
}

const Color&	Material::getColor(double x, double y) const
{
  if (_isTextured == false)
    return (_color);
  else
    return (_texture->getColor(x, y));
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
  _texture = texture;
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

void	Material::setTransmissionCoeff(double transmissionCoeff)
{
  _transmissionCoeff = transmissionCoeff;
}

void	Material::setRefractionIndex(double refractionIndex)
{
  _refractionIndex = refractionIndex;
}

void	Material::setHeightmap(Texture* image)
{
  _heightmap = image;
}

