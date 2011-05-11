//
// Equation_factorize.cpp for  in /home/jochau_g//Desktop/equation-solver
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Tue May 10 13:13:33 2011 gael jochaud-du-plessix
// Last update Tue May 10 23:37:07 2011 gael jochaud-du-plessix
//

#include "Equation.hpp"

void	Equation::factorize(const EqEntity& entity)
{
  _degree = getMaxDegree(entity, _root);
  _coeffs.resize(_degree + 1);
  for (int i = 0; i <= _degree; i++)
    {
      _coeffs[i] = getCoeffForDegree(_root, entity, i);
      EqNode* tmp = getEpuredNode(_coeffs[i]);
      delete _coeffs[i];
      _coeffs[i] = tmp;
    }
}

int	Equation::getMaxDegree(const EqEntity& entity, EqNode* node)
{
  if (!node)
    return (0);
  else if (node->getEntity() && *node->getEntity() == entity)
    return (1);
  else if (!node->getOperator())
    return (0);
  else if (node->getOperator()->getType() == EqOperator::ADD
	   || node->getOperator()->getType() == EqOperator::SUB)
    {
      int coeffLeft  = getMaxDegree(entity, node->getLeft());
      int coeffRight = getMaxDegree(entity, node->getRight());
      return ((coeffLeft > coeffRight) ? coeffLeft : coeffRight);
    }
  else if (node->getOperator()->getType() == EqOperator::MULT)
    {
      return (getMaxDegree(entity, node->getLeft())
	      + getMaxDegree(entity, node->getRight()));
    }
  return (0);
}

EqNode*	Equation::getCoeffForDegree(EqNode* node, const EqEntity& entity,
				    int degree)
{
  EqNode*	coeff = new EqNode(1, NULL);

  if (node->getOperator())
    {
      int operatorType = node->getOperator()->getType();
      if (operatorType == EqOperator::ADD || operatorType == EqOperator::SUB)
	{
	  delete coeff;
	  coeff = new EqNode(0, NULL);
	  if (getMaxDegree(entity, node->getLeft()) == degree
	      || findOperatorInNode(EqOperator::ADD, node->getLeft())
	      || findOperatorInNode(EqOperator::SUB, node->getLeft()))
	    addNodeToCoeff(&coeff, getCoeffForDegree(node->getLeft(),
						     entity, degree),
			   EqOperator::ADD);
	  if (getMaxDegree(entity, node->getRight()) == degree
	      || findOperatorInNode(EqOperator::ADD, node->getRight())
	      || findOperatorInNode(EqOperator::SUB, node->getRight()))
	    addNodeToCoeff(&coeff, getCoeffForDegree(node->getRight(),
						     entity, degree),
			   operatorType);
	}
      else if (operatorType == EqOperator::MULT)
	{
	  if (degree != -1 && getMaxDegree(entity, node) != degree)
	    {
	      delete coeff;
	      return (new EqNode(0, NULL));
	    }
	  else if (!findEntityInNode(entity, node->getLeft())
		   && !findEntityInNode(entity, node->getRight()))
	    addNodeToCoeff(&coeff, node, EqOperator::MULT);
	  else
	    {
	      int addOperator = EqOperator::MULT;
	      addNodeToCoeff(&coeff, getCoeffForDegree(node->getLeft(),
						       entity, -1),
			     addOperator);
	      addNodeToCoeff(&coeff, getCoeffForDegree(node->getRight(),
						       entity, -1),
			     addOperator);
	    }
	}
    }
  else if (node->getEntity())
    {
      if (!(*node->getEntity() == entity))
	addNodeToCoeff(&coeff, node, EqOperator::MULT);
    }
  return (coeff);
}

void	Equation::addNodeToCoeff(EqNode** coeff, EqNode* node,
				 int operatorType)
{
  if (!node)
    return ;
  EqNode* left = *coeff;
  EqNode* right = node;
  EqNode* newNode = new EqNode(operatorType, left, right, NULL);
  delete *coeff;
  *coeff = newNode;
}
