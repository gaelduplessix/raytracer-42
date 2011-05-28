//
// A3DSMaterial.hpp for  in /home/laplan_m/Src/Epitech/Projects/C++/A3DSParser
//
// Made by melvin laplanche
// Login   <laplan_m@epitech.net>
//
// Started on  Sun May 22 21:30:28 2011 melvin laplanche
// Last update Wed May 25 18:11:10 2011 melvin laplanche
//

#ifndef A3DSMATERIAL_H_
# define A3DSMATERIAL_H_
# include <iostream>
# include "A3DSChunk.hpp"

class A3DSMaterial
{
public:
			A3DSMaterial(A3DSChunk);

  void			setName(std::string);
  void			setAmbientColor(char[4]);
  void			setDiffuseColor(char[4]);
  void			setSpecularColor(char[4]);
  void			setTransparency(int);
  void			setTransparencyFalloff(int);
  void			setShininess(int);
  void			setShininessStrength(int);
  void			setReflectionBlur(int);

  const std::string&	getName(void);
  const std::string&	getTextureName(void);
  const char*		getAmbientColor(void);
  const char*		getDiffuseColor(void);
  const char*		getSpecularColor(void);
  int			getTransparency(void);
  int			gtTransparencyFalloff(void);
  int			getShininess(void);
  int			getShininessStrength(void);
  int			getReflectionBlur(void);

private:
  std::string	_name;
  char		_ambientColor[4];
  char		_diffuseColor[4];
  char		_specularColor[4];
  int		_transparency;
  int		_transparencyFalloff;
  int		_shininess;
  int		_shininessStrength;
  int		_reflectionBlur;
  std::string	_textureName;

  void		_fillColor(char[4], A3DSChunk&);
  std::string	_getTextureName(A3DSChunk);
};
#endif /* !A3DSMATERIAL_H_ */
