//
// A3DSMesh.hpp for  in /home/laplan_m/Src/Epitech/Projects/C++/A3DSParser
//
// Made by melvin laplanche
// Login   <laplan_m@epitech.net>
//
// Started on  Sun May 22 18:03:51 2011 melvin laplanche
// Last update Sun May 29 23:33:39 2011 melvin laplanche
//

#ifndef A3DSMESH_H_
# define A3DSMESH_H_
# include <fstream>
# include <iostream>
# include <map>
# include <vector>
# include "A3DSChunk.hpp"
# include "Point.hpp"

class A3DSMesh
{
public:
				A3DSMesh(std::string, A3DSChunk);

  const std::vector<Point>&	getTextureCoord(void) const;
  const std::vector<Point>&	getVertices(void) const;
  const std::vector<Point>&	getFaces(void) const;
  const std::map<std::string, std::vector<int> >& getMaterialFaces(void) const;


private:
  std::string					_name;
  std::vector<Point>				_textureCoord;
  std::vector<Point>				_vertices;
  std::vector<Point>				_faces;
  std::map<std::string, std::vector<int> >	_materialFaces;
  float						_matrix[4][4];

  void			_parseLocalCoordSystem(A3DSChunk);
  void			_parseVertices(A3DSChunk);
  void			_parseFaces(A3DSChunk);
  void			_parseFacesMaterial(A3DSChunk);
  void			_parseTextCoord(A3DSChunk);
};
#endif /* !A3DSMESH_H_ */
