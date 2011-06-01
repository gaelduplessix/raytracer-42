//
// A3DSParser.cpp for  in /home/laplan_m/Src/Epitech/Projects/C++/A3DSParser
//
// Made by melvin laplanche
// Login   <laplan_m@epitech.net>
//
// Started on  Tue May 17 17:29:44 2011 melvin laplanche
// Last update Tue May 31 18:10:20 2011 melvin laplanche
//

#ifndef A3DSPARSER_H_
# define A3DSPARSER_H_
# include <fstream>
# include <iostream>
# include <vector>
# include <string>
# include <QString>

# include "A3DSChunk.hpp"
# include "A3DSLight.hpp"
# include "A3DSMaterial.hpp"
# include "A3DSMesh.hpp"
# include "RenderingInterface.hpp"

struct	t_A3DSHeader
{
  short	id;
  long	length;
};

class A3DSParser
{
public:
  ~A3DSParser(void);
  A3DSParser(void);
  A3DSParser(std::string, RenderingInterface*);
  A3DSParser(QString, RenderingInterface*);
  A3DSParser(const char*, RenderingInterface*);

  void	loadFile(std::string);
  void	loadFile(QString);
  void	loadFile(const char*);

  bool					hasError(void) const;
  const std::vector<A3DSLight*>&	getLights(void) const;
  const std::vector<A3DSMaterial*>&	getMaterials(void) const;
  const std::vector<A3DSMesh*>&		getMeshes(void) const;

private:
  bool				_hasError;
  RenderingInterface*		_interface;
  std::ifstream			_file;
  std::string			_filename;
  std::vector<A3DSLight*>	_lights;
  std::vector<A3DSMaterial*>	_materials;
  std::vector<A3DSMesh*>	_meshes;

  void	_clearObjects(void);
  void	_parseEditor3D(A3DSChunk);
  void	_parseMesh(std::string, A3DSChunk);
  void	_parseObject(A3DSChunk);
  void	_parseMaterial(A3DSChunk);
  void	_parseLight(std::string, A3DSChunk);
  void	_checkFile(std::string);
  void	_putError(QString);
  void	_putInfo(QString);
  void	_parse(void);
};

#endif /* !A3DSPARSER_H_ */
