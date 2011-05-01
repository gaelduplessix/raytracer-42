//
// Material.hpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Wed Apr 27 15:50:09 2011 loick michard
// Last update Sun May  1 17:43:59 2011 samuel olivier
//

#ifndef _MATERIAL_HPP_
#define _MATERIAL_HPP_

#include <string>
#include "Texture.hpp"
#include "Vector.hpp"

using namespace std;

class QImage;

class Material
{
public:
  Material();
  Material(const string& name);
  Material(const Texture& texture);

  void		setName(string name);
  void		setColor(const Color& color);
  void		setTexture(Texture* texture);
  void		setSpecularCoeff(double specularCoeff);
  void		setSpecularPow(double specularPow);
  void		setReflectionCoeff(double reflectionCoeff);
  void		setTransmissionCoeff(double transmissionCoeff);
  void		setRefractionIndex(double refractionIndex);
  void		setHeightmap(Texture* image);

  string	getName(void) const;
  const Color&	getColor(double x, double y) const;  
  double	getSpecularCoeff(void) const;
  double	getSpecularPow(void) const;
  double	getReflectionCoeff(void) const;
  double	getTransmissionCoeff(void) const;
  double	getRefractionIndex(void) const;

  Vector&	getDeformatedNormal(double x, double y,
				    const Vector& normal) const;

private:
  string	_name;
  Color		_color;
  Texture*	_texture;
  bool		_isTextured;
  double	_specularCoeff;
  double	_specularPow;
  double	_reflectionCoeff;
  double	_transmissionCoeff;
  double	_refractionIndex;
  Texture*	_heightmap;
  bool		_hasBumpMap;
};

#endif
