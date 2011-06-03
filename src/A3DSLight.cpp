//
// A3DSLight.cpp for  in /home/laplan_m/Src/Epitech/Projects/C++/A3DSParser
//
// Made by melvin laplanche
// Login   <laplan_m@epitech.net>
//
// Started on  Sun May 22 16:08:31 2011 melvin laplanche
// Last update Fri Jun  3 15:11:28 2011 melvin laplanche
//

#include "A3DSLight.hpp"

using namespace std;

A3DSLight::A3DSLight(string	name,
		     A3DSChunk	parent) : _name(name),
					  _isSpot(false)
{
  A3DSChunk	c = parent.firstChild();

  this->_position.setX(c.getFloat());
  this->_position.setY(c.getFloat());
  this->_position.setZ(c.getFloat());
  while (c)
  {
    if (c.getId() == A3DSChunk::SPOTLIGHT_ID)
    {
      this->_isSpot = true;
      this->_target.setX(c.getFloat());
      this->_target.setY(c.getFloat());
      this->_target.setZ(c.getFloat());
    }
    /*else
    {
      cerr << "Unsused light chunk :" << hex << c.getId();
      cerr << " (" << dec << c.getId() << ")" << endl;
      }*/
    c = c.nextSibling();
  }
}

const Vector&		A3DSLight::getPosition(void)
{
  return this->_position;
}

const Vector&		A3DSLight::getTarget(void)
{
  return this->_target;
}

bool		A3DSLight::isSpot(void)
{
  return this->_isSpot;
}
