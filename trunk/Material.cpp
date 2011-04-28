//
// Material.cpp for raytracer in /home/olivie_a//rendu/cpp/raytracer-42
// 
// Made by samuel olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  Thu Apr 28 18:55:28 2011 samuel olivier
// Last update Thu Apr 28 18:55:29 2011 samuel olivier
//

#include "Material.hpp"

Material::Material()
{

}

Material::~Material()
{

}

double	Material::getSpecularCoeff() const
{
  return (_specularCoeff);
}

double	Material::getSpecularPow() const
{
  return (_specularPow);
}

double	Material::getReflectionCoeff() const
{
  return (_reflectionCoeff);
}

double	Material::getTransmissionCoeff() const
{
  return (_transmissionCoeff);
}

double	Material::getRefractionIndex() const
{
  return (_refractionIndex);
}

string	Material::getName() const
{
  return (_name);
}

Color&	Material::getColor(double x, double y) const
{
  return (_color);
}

void	Material::setColor(const Color& color)
{
  _color = color;
}

void	Material::setTexture(const Texture& texture)
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

void	Material::setName(string name)
{
  _name = name;
}

void	Material::setHeightmap(const Texture& image)
{
  _heightmap = image;
}

