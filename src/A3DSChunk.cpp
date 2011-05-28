//
// A3DSChunk.cpp for  in /home/laplan_m/Src/Epitech/Projects/C++/A3DSParser
//
// Made by melvin laplanche
// Login   <laplan_m@epitech.net>
//
// Started on  Tue May 17 23:48:38 2011 melvin laplanche
// Last update Mon May 23 12:00:25 2011 melvin laplanche
//

#include "A3DSChunk.hpp"

using namespace std;

A3DSChunk::A3DSChunk(ifstream	&file,
	     int	end) : _file(file),
			       _chunkEnd(end),
			       _end(0),
			       _begin(0),
			       _id(0)
{
  this->_begin = file.tellg();
  file.read((char*)&(this->_id), 2);
  file.read((char*)&(this->_end), 4);
  this->_end += this->_begin;
}

streampos	A3DSChunk::getPos(void) const
{
  return this->_file.tellg();
}

short	A3DSChunk::getId(void) const
{
  return this->_id;
}

long	A3DSChunk::getEnd(void) const
{
  return this->_end;
}

int	A3DSChunk::getA3DSChunkEnd(void) const
{
  return this->_chunkEnd;
}

int	A3DSChunk::getBegin(void) const
{
  return this->_begin;
}

void	A3DSChunk::operator=(const A3DSChunk	&chunk)
{
  this->_file.seekg(chunk.getPos());
  this->_chunkEnd = chunk.getA3DSChunkEnd();
  this->_end = chunk.getEnd();
  this->_id = chunk.getId();
  this->_begin = chunk.getBegin();
}

A3DSChunk::operator bool(void)
{
  return (this->_begin < this->_chunkEnd) && (this->_begin >= 0);
}

float	A3DSChunk::getFloat(void)
{
  float	f = 0;

  this->_file.read((char*)&f, 4);
  return f;
}

char	A3DSChunk::getByte(void)
{
  char	c = 0;

  this->_file.read(&c, 1);
  return c;
}

int	A3DSChunk::getInt(void)
{
  int	i = 0;

  this->_file.read((char*)&i, 4);
  return i;
}

short	A3DSChunk::getShort(void)
{
  short	s = 0;

  this->_file.read((char*)&s, 2);
  return s;
}

string		A3DSChunk::getName(void)
{
  string	str;
  char		c;

  do
  {
    this->_file.read(&c, 1);
    str += c;
  } while (c != 0);
  return str;
}

A3DSChunk	A3DSChunk::firstChild()
{
  return A3DSChunk(this->_file, this->_end);
}

A3DSChunk	A3DSChunk::nextSibling(void)
{
  this->_file.seekg(this->_end);
  return A3DSChunk(this->_file, this->_chunkEnd);
}
