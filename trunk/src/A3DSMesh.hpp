//
// A3DSMesh.hpp for  in /home/laplan_m/Src/Epitech/Projects/C++/A3DSParser
//
// Made by melvin laplanche
// Login   <laplan_m@epitech.net>
//
// Started on  Sun May 22 18:03:51 2011 melvin laplanche
// Last update Wed May 25 22:40:43 2011 melvin laplanche
//

#ifndef A3DSMESH_H_
# define A3DSMESH_H_
# include <fstream>
# include <iostream>
# include <map>
# include <vector>
# include "A3DSChunk.hpp"
# include "Vector.hpp"

class A3DSMesh
{
public:
			A3DSMesh(std::string, A3DSChunk);

private:
  std::string					_name;
  std::vector<Vector>				_textureCoord;
  std::vector<Vector>				_vertices;
  std::vector<Vector>				_faces;
  std::map<std::string, std::vector<int> >	_materialFaces;
  float						_matrix[4][4];

  void			_parseLocalCoordSystem(A3DSChunk);
  void			_parseVertices(A3DSChunk);
  void			_parseFaces(A3DSChunk);
  void			_parseFacesMaterial(A3DSChunk);
  void			_parseTextCoord(A3DSChunk);
};
#endif /* !A3DSMESH_H_ */
