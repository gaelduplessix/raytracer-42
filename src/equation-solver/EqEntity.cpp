//
// EqEntity.cpp for  in /home/jochau_g//Desktop/equation-solver
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Thu May  5 13:59:27 2011 gael jochaud-du-plessix
// Last update Tue May 10 16:50:16 2011 gael jochaud-du-plessix
//

#include "EqEntity.hpp"

#include <stdlib.h>

EqEntity::EqEntity(const string& entity):
  _isUnknown(false), _name(entity), _value(0)
{
  if (_name.find_first_not_of("0123456789") != string::npos)
    _isUnknown = true;
  else
    _value = atof(_name.c_str());
}


EqEntity::EqEntity(double value):
  _isUnknown(false), _name(), _value(value)
{
}

bool	EqEntity::isUnknown(void) const
{
	return (_isUnknown);
}

string	EqEntity::getName(void) const
{
	return (_name);
}

double	EqEntity::getValue(void) const
{
	return (_value);
}

void	EqEntity::setValue(double value)
{
  _isUnknown = false;
  _value = value;
}

bool	EqEntity::operator==(const EqEntity& entity)
{
  if (_isUnknown)
    {
      if (!entity._isUnknown)
	return (false);
      else
	return (_name == entity._name);
    }
  else if (entity._isUnknown)
    return (false);
  return (_value == entity._value);
}
