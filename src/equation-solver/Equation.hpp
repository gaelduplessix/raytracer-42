//
// Equation.hpp for  in /home/jochau_g//Desktop/equation-solver
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Thu May  5 13:53:43 2011 gael jochaud-du-plessix
// Last update Tue May 10 23:54:36 2011 gael jochaud-du-plessix
//

#ifndef _EQUATION_HPP_
#define _EQUATION_HPP_

#include <vector>
#include <string>
#include <iostream>

using namespace std;

#include "EqNode.hpp"

class Equation
{
public:
  Equation(void);
  Equation(const string& equation);
  ~Equation(void);

  void		initWithString(const string& equation);

  int		getDegree(void) const;
  EqNode*	getFactorizedCoeff(unsigned int coeff) const;
  EqNode*	getDerivate(void) const;

  friend ostream&	operator<<(ostream &flux, const Equation& equation);

  void		develop(void);

  void		developPow(void);
  EqNode*	getFirstDevelopablePowNode(EqNode* node);

  void		developMult(void);
  bool		isDevelopableNode(EqNode* node);
  EqNode*	getFirstDevelopableNode(EqNode* node);
  void		replaceNode(EqNode* oldNode, EqNode* newNode,
			    bool deleteOld=false);

  void		factorize(const EqEntity& entity);
  int		getMaxDegree(const EqEntity& entity, EqNode* node);
  EqNode*	getCoeffForDegree(EqNode* node, const EqEntity& entity,
				  int degree);
  void		addNodeToCoeff(EqNode** coeff, EqNode* node,
			       int operatorType);

  bool		findOperatorInNode(int operatorType, const EqNode* node);
  bool		findEntityInNode(const EqEntity& entity, const EqNode* node);
  EqNode*	getEpuredNode(EqNode* node);
  bool		hasNodeToEpure(EqNode* node);
  EqNode*	epureNode(EqNode* node);

  void		derivate(const EqEntity& entity);

  EqNode*	getDerivatedNode(EqNode* node, const EqEntity& entity);

  void		injectValues(const EqEntity& entity, double value,
			     EqNode* node = NULL);
  double	evalNode(const EqNode* node, const EqEntity* entity = NULL,
			 double value = -1) const;

protected:
  EqNode*		_root;
  EqNode*		_derivate;
  int			_degree;
  vector <EqNode*>	_coeffs;
};

#endif
