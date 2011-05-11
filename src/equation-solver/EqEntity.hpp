//
// EqEntity.hpp for  in /home/jochau_g//Desktop/equation-solver
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Thu May  5 13:59:00 2011 gael jochaud-du-plessix
// Last update Tue May 10 16:49:10 2011 gael jochaud-du-plessix
//

#ifndef _EQENTITY_HPP_
#define _EQENTITY_HPP_

#include <string>

using namespace std;

class EqEntity
{
public:
  EqEntity(const string& entity);
  EqEntity(double value);

  bool		isUnknown(void) const;
  string	getName(void) const;
  double	getValue(void) const;

  void		setValue(double value);

  bool		operator==(const EqEntity& entity);
  
protected:
  bool		_isUnknown;
  string	_name;
  double	_value;
};

#endif
