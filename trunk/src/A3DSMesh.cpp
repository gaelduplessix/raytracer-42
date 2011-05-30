//
// A3DSMesh.cpp for  in /home/laplan_m/Src/Epitech/Projects/C++/A3DSParser
//
// Made by melvin laplanche
// Login   <laplan_m@epitech.net>
//
// Started on  Wed May 25 18:28:47 2011 melvin laplanche
// Last update Mon May 30 12:12:17 2011 melvin laplanche
//

#include "A3DSMesh.hpp"

using namespace std;

A3DSMesh::A3DSMesh(string	name,
		   A3DSChunk	c)
{
  this->_name = name;
  while (c)
  {
    if (c.getId() == A3DSChunk::LOCAL_COORD_SYSTEM_ID)
      this->_parseLocalCoordSystem(c);
    else if (c.getId() == A3DSChunk::VERTICES_ID)
      this->_parseVertices(c);
    else if (c.getId() == A3DSChunk::FACES_ID)
      this->_parseFaces(c);
    else if (c.getId() == A3DSChunk::MAPPING_COORD_ID)
      this->_parseTextCoord(c);
    else
    {
      cerr << "Unsused mesh chunk :" << hex << c.getId();
      cerr << " (" << dec << c.getId() << ")" << endl;
    }
    c = c.nextSibling();
  }
}

void	A3DSMesh::_parseLocalCoordSystem(A3DSChunk	c)
{
  for (int i=0; i<4; i++)
    for (int j=0; j<4; j++)
      this->_matrix[i][j] = c.getFloat();
  for (int i=0; i<3; i++)
    this->_matrix[i][3] = 0;
  this->_matrix[3][3] = 1;
}

void	A3DSMesh::_parseTextCoord(A3DSChunk	c)
{
  int		nbTexts = c.getShort();
  Point	v;

  for (int i=0; i<nbTexts; i++)
  {
    v.setVector(c.getFloat(), c.getFloat(), 0);
    this->_textureCoord.push_back(v);
  }
}

void	A3DSMesh::_parseVertices(A3DSChunk	c)
{
  int		nb_vertices = c.getShort();
  Point	v;

  for (int i=0; i<nb_vertices; i++)
  {
    v.setVector(c.getFloat(), c.getFloat(), c.getFloat());
    this->_vertices.push_back(v);
  }
}

void	A3DSMesh::_parseFaces(A3DSChunk	c)
{
  int		nb_faces = c.getShort();
  Point	v;

  for (int i=0; i<nb_faces; i++)
  {
    v.setVector(c.getShort(), c.getShort(), c.getShort());
    c.getShort();
    this->_faces.push_back(v);
  }
  for (A3DSChunk child=c.firstChild(); child; child = child.nextSibling())
  {
    if (child.getId() == A3DSChunk::FACES_MATERIAL_ID)
      this->_parseFacesMaterial(child);
  }
}

void	A3DSMesh::_parseFacesMaterial(A3DSChunk	c)
{
  string	matName = c.getName();
  int		nbFaces = c.getShort();
  vector<int>	faceApplied;

  for (int i=0; i<nbFaces; i++)
    faceApplied.push_back(c.getShort());
  this->_materialFaces[matName] = faceApplied;
}

const std::vector<Point>&	A3DSMesh::getTextureCoord(void) const
{
  return this->_textureCoord;
}

const std::vector<Point>&	A3DSMesh::getVertices(void) const
{
  return this->_vertices;
}

const std::vector<Point>&	A3DSMesh::getFaces(void) const
{
  return this->_faces;
}

const std::map<std::string, std::vector<int> >&
A3DSMesh::getMaterialFaces(void) const
{
  return this->_materialFaces;
}
