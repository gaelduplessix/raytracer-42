//
// Equation_derivate.cpp for  in /home/jochau_g//Desktop/equation-solver
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Tue May 10 13:17:21 2011 gael jochaud-du-plessix
// Last update Wed May 11 00:02:59 2011 gael jochaud-du-plessix
//

#include "Equation.hpp"

void	Equation::derivate(const EqEntity& entity)
{
  developPow();
  EqNode	*tmp = getDerivatedNode(_root, entity);
  _derivate = epureNode(tmp);
  delete tmp;
}

EqNode*	Equation::getDerivatedNode(EqNode* node, const EqEntity& entity)
{
  if (node->getEntity())
    {
      if (*node->getEntity() == entity)
	return (new EqNode(1, NULL));
      else
	return (new EqNode(0, NULL));
    }
  else if (node->getOperator()
	   && (node->getOperator()->getType() == EqOperator::ADD
	       || node->getOperator()->getType() == EqOperator::SUB))
    {
      EqNode	*left = getDerivatedNode(node->getLeft(), entity);
      EqNode	*right = getDerivatedNode(node->getRight(), entity);
      EqNode	*newNode = new EqNode(node->getOperator()->getType(),
				      left, right, NULL);
      delete left;
      delete right;
      return (newNode);
    }
  else if (node->getOperator()
	   && node->getOperator()->getType() == EqOperator::MULT)
    {
      EqNode	*uPrim = getDerivatedNode(node->getLeft(), entity);
      EqNode	*vPrim = getDerivatedNode(node->getRight(), entity);
      EqNode	*u = new EqNode(*node->getLeft(), true);
      EqNode	*v = new EqNode(*node->getRight(), true);
      EqNode	*left = new EqNode(EqOperator::MULT, uPrim, v, NULL);
      EqNode	*right = new EqNode(EqOperator::MULT, u, vPrim, NULL);
      delete uPrim;
      delete vPrim;
      delete u;
      delete v;
      EqNode	*newNode = new EqNode(EqOperator::ADD, left, right, NULL);
      delete left;
      delete right;
      return (newNode);
    }
  else
    return (new EqNode(0, NULL));
}
