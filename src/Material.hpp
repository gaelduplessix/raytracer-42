//
// Material.hpp for raytracer in /home/michar_l//Raytracer/raytracer-42/src
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Wed May  4 17:40:55 2011 loick michard
// Last update Sat Jun  4 18:49:58 2011 gael jochaud-du-plessix
//

#ifndef _MATERIAL_HPP_
#define _MATERIAL_HPP_

#include <string>

#include "Texture.hpp"
#include "Vector.hpp"

using namespace std;

class Material
{
public:
  static const int WAVES_X = 0;
  static const int WAVES_Y = 1;
  static const int WAVES_Z = 2;

  Material();
  Material(const string& name);
  ~Material();

  void		setName(string name);
  void		setColor(const Color& color);
  void		setTexture(Texture* texture);
  void		setLimitTexture(Texture* texture);
  void		setSpecularCoeff(double specularCoeff);
  void		setSpecularPow(double specularPow);
  void		setReflectionCoeff(double reflectionCoeff);
  void		setDiffusedReflectionCoeff(double diffusedReflectionCoeff);
  void		setDiffusedTransmissionCoeff(double diffusedTransmissionCoeff);
  void		setTransmissionCoeff(double transmissionCoeff);
  void		setRefractionIndex(double refractionIndex);
  void		setHeightmap(Texture* image);
  void		setNormalDeformation(int deformation,
				     int deformationCoeff = 10);

  string	getName(void) const;
  Color		getColor(double x, double y) const;
  bool		isLimitedAtPoint(double x, double y) const;
  Color		getHeightmapColor(double x, double y) const;
  double	getSpecularCoeff(void) const;
  double	getSpecularPow(void) const;
  double	getReflectionCoeff(void) const;
  double	getDiffusedReflectionCoeff(void) const;
  double	getTransmissionCoeff(void) const;
  double	getRefractionIndex(void) const;

  Vector&	getDeformatedNormal(double x, double y,
				    const Vector& normal) const;

  string	_name;
  Color		_color;
  bool		_isTextured;
  double	_specularCoeff;
  double	_specularPow;
  double	_reflectionCoeff;
  double	_transmissionCoeff;
  double	_refractionIndex;
  double	_diffusedReflectionCoeff;

  Texture*	_texture;
  Texture*	_limitTexture;
  Texture*	_heightmap;
  bool		_hasBumpMap;
  bool		_hasNormalDeformation;
  int		_deformationType;
  int		_deformationCoeff;
};

#endif
