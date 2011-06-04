//
// A3DSMaterial.cpp for  in /home/laplan_m/Src/Epitech/Projects/C++/A3DSParser
//
// Made by melvin laplanche
// Login   <laplan_m@epitech.net>
//
// Started on  Wed May 25 15:09:09 2011 melvin laplanche
// Last update Sat Jun  4 14:51:54 2011 gael jochaud-du-plessix
//

#include "A3DSMaterial.hpp"

using namespace std;

A3DSMaterial::A3DSMaterial(A3DSChunk	c) : _name(""),
					     _ambientColor(),
					     _diffuseColor(),
					     _specularColor(),
					     _transparency(0),
					     _transparencyFalloff(0),
					     _shininess(0),
					     _shininessStrength(0),
					     _reflectionBlur(0),
					     _textureName("")
{
  _ambientColor[0] = 0;_ambientColor[1] = 0;_ambientColor[2] = 0;
  _ambientColor[3] = 0;
  _diffuseColor[1] = 0;_diffuseColor[1] = 0;_diffuseColor[2] = 0;
  _diffuseColor[3] = 0;
  _specularColor[0] = 0;_specularColor[1] = 0;_specularColor[2] = 0;
  _specularColor[3] = 0;
  while (c)
  {
    if (c.getId() == A3DSChunk::MAT_NAME_ID)
      this->_name = c.getName();
    else if (c.getId() == A3DSChunk::MAT_AMBIENT_COLOR_ID)
      this->_fillColor(this->_ambientColor, c);
    else if (c.getId() == A3DSChunk::MAT_DIFFUSE_COLOR_ID)
      this->_fillColor(this->_diffuseColor, c);
    else if (c.getId() == A3DSChunk::MAT_SPECULAR_COLOR_ID)
      this->_fillColor(this->_specularColor, c);
    else if (c.getId() == A3DSChunk::MAT_SHININESS_ID)
      this->_shininess = c.getInt();
    else if (c.getId() == A3DSChunk::MAT_SHININESS_STRENGTH_ID)
      this->_shininessStrength = c.getInt();
    else if (c.getId() == A3DSChunk::MAT_TRANSPARENCY_ID)
      this->_transparency = c.getInt();
    else if (c.getId() == A3DSChunk::MAT_TRANSPARENCY_FALLOFF_ID)
      this->_transparencyFalloff = c.getInt();
    else if (c.getId() == A3DSChunk::MAT_REFLECTION_BLUR_ID)
      this->_reflectionBlur = c.getInt();
    else if (c.getId() == A3DSChunk::MAT_TEXTURE_MAP_1_ID
	     || c.getId() == A3DSChunk::MAT_TEXTURE_MAP_2_ID)
      this->_textureName = this->_getTextureName(c.firstChild());
    /*else
    {
      cerr << "Unsused material chunk :" << hex << c.getId();
      cerr << " (" << dec << c.getId() << ")" << endl;
      }*/
    c = c.nextSibling();
  }
}

void	A3DSMaterial::_fillColor(char		color[4],
				 A3DSChunk&	c)
{
  color[0] = c.getByte();
  color[1] = c.getByte();
  color[2] = c.getByte();
  color[3] = c.getByte();
}

string	A3DSMaterial::_getTextureName(A3DSChunk	c)
{
  string	name;

  while (c)
  {
    if (c.getId() == A3DSChunk::TEXTURE_NAME_ID)
      return c.getName();
    /*else
    {
      cerr << "Unsused texture name chunk :" << hex << c.getId();
      cerr << " (" << dec << c.getId() << ")" << endl;
      }*/
    c = c.nextSibling();
  }
  return name;
}

const std::string&	A3DSMaterial::getName(void)
{
  return this->_name;
}

const std::string&	A3DSMaterial::getTextureName(void)
{
  return this->_textureName;
}

const char*		A3DSMaterial::getAmbientColor(void)
{
  return this->_ambientColor;
}

const char*		A3DSMaterial::getDiffuseColor(void)
{
  return this->_diffuseColor;
}

const char*		A3DSMaterial::getSpecularColor(void)
{
  return this->_specularColor;
}

int			A3DSMaterial::getTransparency(void)
{
  return this->_transparency;
}

int			A3DSMaterial::gtTransparencyFalloff(void)
{
  return this->_transparencyFalloff;
}

int			A3DSMaterial::getShininess(void)
{
  return this->_shininess;
}

int			A3DSMaterial::getShininessStrength(void)
{
  return this->_shininessStrength;
}

int			A3DSMaterial::getReflectionBlur(void)
{
  return this->_reflectionBlur;
}
