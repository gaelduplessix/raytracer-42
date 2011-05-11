//
// EqOperator.hpp for  in /home/jochau_g//Desktop/equation-solver
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Thu May  5 13:59:00 2011 gael jochaud-du-plessix
// Last update Fri May  6 12:05:48 2011 gael jochaud-du-plessix
//

#ifndef _EQOPERATOR_HPP_
#define _EQOPERATOR_HPP_

#include <string>

using namespace std;

class EqOperator
{
public:
  static const int ERROR_UNDEFINED_TYPE = 0;

  static const int ADD	= 0;
  static const int SUB	= 1;
  static const int MULT	= 2;
  static const int DIV	= 3;
  static const int POW	= 4;

  EqOperator(int type=-1);

  int	getType(void);
  void	setType(double type);

  static string getLabel(int type);
  static int getType(string label);

protected:
  int	_type;
};

#endif
