//
// A3DSChunk.hpp for  in /home/laplan_m/Src/Epitech/Projects/C++/A3DSParser
//
// Made by melvin laplanche
// Login   <laplan_m@epitech.net>
//
// Started on  Sat May 21 23:19:04 2011 melvin laplanche
// Last update Sun May 29 15:55:10 2011 melvin laplanche
//

#ifndef CHUNK_H_
# define CHUNK_H_
# include <fstream>

class A3DSChunk
{
public:
  static const int FILE_ID	= 0x4d4d;
  static const int OBJECT_ID	= 0x4000;
  static const int EDITOR3D_ID	= 0x3d3d;
  static const int LIGHT_ID	= 0x4600;
  static const int MESH_ID	= 0x4100;
  static const int SPOTLIGHT_ID = 0x4610;
  static const int MATERIAL_ID	= 0xffffafff; // Don't ask me why...

  static const int MAT_NAME_ID			= 0xffffa000;
  static const int MAT_AMBIENT_COLOR_ID		= 0xffffa010;
  static const int MAT_DIFFUSE_COLOR_ID		= 0xffffa020;
  static const int MAT_SPECULAR_COLOR_ID	= 0xffffa030;
  static const int MAT_SHININESS_ID		= 0xffffa040;
  static const int MAT_SHININESS_STRENGTH_ID	= 0xffffa041;
  static const int MAT_TRANSPARENCY_ID		= 0xffffa050;
  static const int MAT_TRANSPARENCY_FALLOFF_ID	= 0xffffa052;
  static const int MAT_REFLECTION_BLUR_ID	= 0xffffa053;
  static const int MAT_TEXTURE_MAP_1_ID		= 0xffffa200;
  static const int MAT_TEXTURE_MAP_2_ID		= 0xffffa33a;
  static const int TEXTURE_NAME_ID		= 0xffffa300;
  static const int LOCAL_COORD_SYSTEM_ID	= 0x4160;
  static const int VERTICES_ID			= 0x4110;
  static const int FACES_ID			= 0x4120;
  static const int FACES_MATERIAL_ID		= 0x4130;
  static const int MAPPING_COORD_ID		= 0x4140;

			A3DSChunk(std::ifstream&, int);

  std::streampos	getPos(void) const;
  int			getBegin(void) const;
  int			getA3DSChunkEnd(void) const;
  long			getEnd(void) const;
  short			getId(void) const;
  std::string		getName(void);
  float			getFloat(void);
  int			getInt(void);
  short			getShort(void);
  char			getByte(void);

  operator bool(void);
  void			operator=(const A3DSChunk&);

  A3DSChunk		nextSibling(void);
  A3DSChunk		firstChild(void);

private:
  std::ifstream&	_file;
  int			_chunkEnd;
  long			_end;
  int			_begin;
  short			_id;
};
#endif /* !CHUNK_H_ */
