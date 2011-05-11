//
// EqOperator.cpp for  in /home/jochau_g//Desktop/equation-solver
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Thu May  5 14:29:25 2011 gael jochaud-du-plessix
// Last update Fri May  6 12:05:35 2011 gael jochaud-du-plessix
//

#include "EqOperator.hpp"

EqOperator::EqOperator(int type):
  _type(type)
{
  
}

int	EqOperator::getType(void)
{
  return (_type);
}

void	EqOperator::setType(double type)
{
  _type = type;
}

string EqOperator::getLabel(int type)
{
  if (type == EqOperator::ADD)
    return ("+");
  else if (type == EqOperator::SUB)
    return ("-");
  else if (type == EqOperator::MULT)
    return ("*");
  else if (type == EqOperator::DIV)
    return ("/");
  else if (type == EqOperator::POW)
    return ("^");
  else
    throw EqOperator::ERROR_UNDEFINED_TYPE;
}

int EqOperator::getType(string label)
{
  if (label == getLabel(EqOperator::ADD))
    return (EqOperator::ADD);
  else if (label == getLabel(EqOperator::SUB))
    return (EqOperator::SUB);
  else if (label == getLabel(EqOperator::MULT))
    return (EqOperator::MULT);
  else if (label == getLabel(EqOperator::DIV))
    return (EqOperator::DIV);
  else if (label == getLabel(EqOperator::POW))
    return (EqOperator::POW);
  return (-1);
}
