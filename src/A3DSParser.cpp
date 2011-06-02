//
// A3DSParser.cpp for  in /home/laplan_m/Src/Epitech/Projects/C++/A3DSParser
//
// Made by melvin laplanche
// Login   <laplan_m@epitech.net>
//
// Started on  Tue May 17 18:30:51 2011 melvin laplanche
// Last update Thu Jun  2 16:01:05 2011 melvin laplanche

#include "A3DSParser.hpp"

using namespace std;

void	A3DSParser::_clearObjects(void)
{
  int size;

  this->_hasError = false;
  if (this->_file.is_open())
    this->_file.close();
  size = this->_lights.size();
  for (int i = 0; i < size; i++)
    delete this->_lights[i];
  this->_lights.clear();
  size = this->_materials.size();
  for (int i = 0; i < size; i++)
    delete this->_materials[i];
  this->_materials.clear();
  size = this->_meshes.size();
  for (int i = 0; i < size; i++)
    delete this->_meshes[i];
  this->_meshes.clear();
}

A3DSParser::~A3DSParser(void)
{
  this->_clearObjects();
}

A3DSParser::A3DSParser(string			filename,
		       RenderingInterface*	interface)
  : _hasError(false),
    _interface(interface)
{
  this->loadFile(filename);
  if (this->_hasError == false)
    this->_parse();
}


A3DSParser::A3DSParser(QString			filename,
		       RenderingInterface*	interface)
  : _hasError(false),
    _interface(interface)
{
  this->loadFile(filename);
  if (this->_hasError == false)
    this->_parse();
}

A3DSParser::A3DSParser(const char*		filename,
		       RenderingInterface*	interface)
  : _hasError(false),
    _interface(interface)
{
  this->loadFile(filename);
  if (this->_hasError == false)
    this->_parse();
}

void	A3DSParser::_putError(QString	msg)
{
  this->_hasError = true;
  if (this->_interface != NULL)
    this->_interface->sendErrorMessage(msg.toStdString());
  else
    cerr << "Parse error: " << msg.toStdString() << endl;
}

void	A3DSParser::_putInfo(QString	msg)
{
  if (this->_interface != NULL)
    this->_interface->sendMessage(msg.toStdString());
  else
    cerr << "Info: " << msg.toStdString() << endl;
}

void	A3DSParser::loadFile(string	filename)
{
  this->_clearObjects();
  this->_file.open(filename.c_str(), ios_base::out | ios_base::binary);
  this->_checkFile(filename);
}

void	A3DSParser::loadFile(QString	filename)
{
  this->_clearObjects();
  this->_file.open(filename.toStdString().c_str(),
		   ios_base::out | ios_base::binary);
  this->_checkFile(filename.toStdString());
}

void	A3DSParser::loadFile(const char*	filename)
{
  this->_clearObjects();
  this->_file.open(filename, ios_base::out | ios_base::binary);
  this->_checkFile(filename);
}

void	A3DSParser::_checkFile(string	filename)
{
  t_A3DSHeader	header;

  if (this->_file.is_open() == false)
    this->_putError(QObject::tr("%1 is not openable").arg(filename.c_str()));
  else
  {
    this->_file.read((char*)&header, sizeof(header));
    if (header.id != A3DSChunk::FILE_ID)
      this->_putError(QObject::tr("%1 is not a valid 3ds file")
		      .arg(filename.c_str()));
    this->_file.seekg(0, ios_base::beg);
  }
}

void		A3DSParser::_parse(void)
{
  streampos	currPos = this->_file.tellg();
  streampos	end;

  this->_file.seekg(0, ios::end);
  end = this->_file.tellg();
  this->_file.seekg(currPos);

  A3DSChunk	root = A3DSChunk(this->_file, end);
  A3DSChunk	c = root.firstChild();
  while (c)
  {
    if (c.getId() == A3DSChunk::A3DS_VERSION)
      this->_putInfo(QObject::tr("3ds version: %1").arg(c.getInt()));
    else if (c.getId() == A3DSChunk::EDITOR3D_ID)
      this->_parseEditor3D(c.firstChild());
    else
    {
      cerr << "Unsused main chunk :" << hex << c.getId();
      cerr << " (" << dec << c.getId() << ")" << endl;
    }
    c = c.nextSibling();
  }
}

void		A3DSParser::_parseEditor3D(A3DSChunk	c)
{
  while (c)
  {
    if (c.getId() == A3DSChunk::MATERIAL_ID)
      this->_parseMaterial(c.firstChild());
    else if (c.getId() == A3DSChunk::OBJECT_ID)
      this->_parseObject(c);
    else
    {
      cerr << "Unsused editor chunk :" << hex << c.getId();
      cerr << " (" << dec << c.getId() << ")" << endl;
    }
    c = c.nextSibling();
  }
}

void		A3DSParser::_parseMaterial(A3DSChunk	c)
{
  cerr << "MATERIAL" << endl;
  this->_materials.push_back(new A3DSMaterial(c));
}

void		A3DSParser::_parseObject(A3DSChunk	parent)
{
  string	name;
  A3DSChunk	c = parent.firstChild();

  name = parent.getName();
  while (c)
  {
    if (c.getId() == A3DSChunk::MESH_ID)
      this->_parseMesh(name, c);
    else if (c.getId() == A3DSChunk::LIGHT_ID)
      this->_parseLight(name, c);
    else
    {
      for (A3DSChunk cc = c.firstChild(); cc; cc = cc.nextSibling())
      {
	if (cc.getId() == A3DSChunk::OBJECT_ID)
	  this->_parseObject(cc);
	else if (cc.getId() == A3DSChunk::MESH_ID)
	  this->_parseMesh(name, cc);
	else if (cc.getId() == A3DSChunk::LIGHT_ID)
	  this->_parseLight(name, cc);
	else
	{
	  cerr << "Unsused unknown chunk :" << hex << cc.getId();
	  cerr << " (" << dec << cc.getId() << ")" << endl;
	  //this->_parseObject(c);
	}
      }
    }
    c = c.nextSibling();
  }
}

void	A3DSParser::_parseLight(string		name,
				A3DSChunk	c)
{
  cerr << "LIGHT" << endl;
  this->_lights.push_back(new A3DSLight(name, c));
}

void	A3DSParser::_parseMesh(string		name,
			       A3DSChunk	c)
{
  cerr << "MESH" << endl;
  this->_meshes.push_back(new A3DSMesh(name, c.firstChild()));
}

bool	A3DSParser::hasError(void) const
{
  return this->_hasError;
}

const std::vector<A3DSLight*>&		A3DSParser::getLights(void) const
{
  return this->_lights;
}

const std::vector<A3DSMaterial*>&	A3DSParser::getMaterials(void) const
{
  return this->_materials;
}

const std::vector<A3DSMesh*>&		A3DSParser::getMeshes(void) const
{
  return this->_meshes;
}
