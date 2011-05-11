//
// Equation_develop.cpp for  in /home/jochau_g//Desktop/equation-solver
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Tue May 10 13:11:58 2011 gael jochaud-du-plessix
// Last update Tue May 10 16:14:16 2011 gael jochaud-du-plessix
//

#include "Equation.hpp"

void		Equation::develop(void)
{
  developPow();
  developMult();
}

void	Equation::developPow(void)
{
  EqNode	*node;

  while ((node = getFirstDevelopablePowNode(_root)) != NULL)
    {
      if (node->getOperator()->getType() == EqOperator::POW)
	{
	  EqNode *left = NULL, *right = NULL;
	  if (node->getLeft()->getEntity()
	      && !node->getLeft()->getEntity()->isUnknown())
	    {
	      left = node->getRight();
	      right = node->getLeft();
	    }
	  else if (node->getRight()->getEntity()
		   && !node->getRight()->getEntity()->isUnknown())
	    {
	      left = node->getLeft();
	      right = node->getRight();
	    }
	  if (left && right)
	    {
	      int pow = right->getEntity()->getValue();
	      if (pow > 1)
		{
		  EqNode *newLeft, *newRight, *newRightLeft, *newPowNode;
		  newLeft = new EqNode(*left, true);
		  newRightLeft = new EqNode(*left, true);
		  newPowNode = new EqNode(pow - 1, node);
		  newRight = new EqNode(EqOperator::POW, newRightLeft,
					newPowNode, node);
		  delete newRightLeft;
		  delete newPowNode;
		  replaceNode(node->getLeft(), newLeft, true);
		  replaceNode(node->getRight(), newRight, true);
		  node->getOperator()->setType(EqOperator::MULT);
		}
	      else if (pow <= 1)
		{
		  EqNode *newNode;
		  if (pow == 1)
		    newNode = new EqNode(*left, true);
		  else
		    newNode = new EqNode(1, node);
		  replaceNode(node, newNode, true);
		}
	    }
	}
    }
}

EqNode*	Equation::getFirstDevelopablePowNode(EqNode* node)
{
  EqNode*	developableNode;

  if (node && node->getOperator() && node->getLeft() && node->getRight())
    {
      if (node->getOperator()->getType() == EqOperator::POW
	  && node->getLeft() && node->getRight())
	{
	  if ((node->getLeft()->getEntity()
	       && !node->getLeft()->getEntity()->isUnknown())
	      || (node->getRight()->getEntity()
		  && !node->getRight()->getEntity()->isUnknown()))
	    return (node);
	}
      if ((developableNode = getFirstDevelopablePowNode(node->getLeft())))
	return (developableNode);
      if ((developableNode = getFirstDevelopablePowNode(node->getRight())))
	return (developableNode);
    }
  return (NULL);  
}

void	Equation::developMult(void)
{
  EqNode	*node, *left, *right, *newNodeLeft, *newNodeRight;

  while ((node = getFirstDevelopableNode(_root)) != NULL)
    {
      left = node->getRight();
      right = node->getLeft();
      if (node->getRight()->getOperator()
	  && (node->getRight()->getOperator()->getType()
	      == EqOperator::ADD
	      || node->getRight()->getOperator()->getType()
	      == EqOperator::SUB))
	{
	  left = node->getLeft();
	  right = node->getRight();
	}
      newNodeLeft = new EqNode(EqOperator::MULT, left,
			       right->getLeft(), node);
      newNodeRight = new EqNode(EqOperator::MULT, left,
				right->getRight(), node);
      node->getOperator()->setType(right->getOperator()->getType());
      replaceNode(node->getLeft(), newNodeLeft, true);
      replaceNode(node->getRight(), newNodeRight, true);
    }
}

bool	Equation::isDevelopableNode(EqNode* node)
{
  if (node)
    {
      if (node->getOperator()
	  && node->getOperator()->getType() == EqOperator::MULT
	  && node->getLeft() && node->getRight())
	{
	  if (node->getRight()->getOperator()
	      && (node->getRight()->getOperator()->getType() 
		  == EqOperator::ADD
		  || node->getRight()->getOperator()->getType()
		  == EqOperator::SUB))
	    return (true);
	  else if (node->getLeft()->getOperator()
		   && (node->getLeft()->getOperator()->getType() 
		       == EqOperator::ADD
		       || node->getLeft()->getOperator()->getType()
		       == EqOperator::SUB))
	    return (true);
	}
    }
  return (false);
}

EqNode*	Equation::getFirstDevelopableNode(EqNode* node)
{
  EqNode*	developableNode;
	
  if (node && node->getOperator() && node->getLeft() && node->getRight())
    {
      if (isDevelopableNode(node))
	return (node);
      if ((developableNode = getFirstDevelopableNode(node->getLeft())))
	return (developableNode);
      if ((developableNode = getFirstDevelopableNode(node->getRight())))
	return (developableNode);
    }
  return (NULL);
}
