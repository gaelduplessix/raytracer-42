//
// Equation.cpp for  in /home/jochau_g//Desktop/equation-solver
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Thu May  5 13:54:24 2011 gael jochaud-du-plessix
// Last update Tue May 10 23:54:28 2011 gael jochaud-du-plessix
//

#include "Equation.hpp"

Equation::Equation(void):
  _root(NULL), _derivate(NULL), _degree(0)
{
  _coeffs.resize(0);
}

Equation::Equation(const string& equation):
  _root(NULL), _derivate(NULL), _degree(0)
{
  string epured;
  
  for (unsigned int i = 0; i < equation.size(); i++)
    if (equation[i] != ' ')
      epured += equation[i];
  _root = new EqNode(epured, NULL);
  _coeffs.resize(0);
}

void		Equation::initWithString(const string& equation)
{
  string	epured;

  for (unsigned int i = 0; i < equation.size(); i++)
    if (equation[i] != ' ')
      epured += equation[i];
  _root = new EqNode(epured, NULL);
  _coeffs.resize(0);
}


Equation::~Equation(void)
{
  if (_root)
    delete _root;
  if (_derivate)
    delete _derivate;
  for (unsigned int i = 0; i < _coeffs.size(); i++)
    if (_coeffs[i])
      delete _coeffs[i];
}

int		Equation::getDegree(void) const
{
  return (_degree);
}

EqNode*		Equation::getFactorizedCoeff(unsigned int coeff) const
{
  if (coeff < _coeffs.size())
    return (_coeffs[coeff]);
  return (NULL);
}

EqNode*		Equation::getDerivate(void) const
{
  return (_derivate);
}

ostream&	operator<<(ostream &flux, const Equation& equation)
{
  flux << *equation._root;
  return (flux);
}

void	Equation::replaceNode(EqNode* oldNode, EqNode* newNode, bool deleteOld)
{
  if (oldNode->getParent() == NULL)
    {
      if (deleteOld)
	delete _root;
      _root = newNode;
    }
  else
    {
      if (oldNode->getParent()->getLeft() == oldNode)
	oldNode->getParent()->setLeft(newNode, deleteOld);
      else if (oldNode->getParent()->getRight() == oldNode)
	oldNode->getParent()->setRight(newNode, deleteOld);
    }
}

bool	Equation::findOperatorInNode(int operatorType, const EqNode* node)
{
  if (!node)
    return (false);
  if (node->getOperator() && node->getOperator()->getType() == operatorType)
    return (true);
  if (node->getLeft() && node->getRight())
    return (findOperatorInNode(operatorType, node->getLeft())
	    || findOperatorInNode(operatorType, node->getRight()));
  return (false);
}

bool	Equation::findEntityInNode(const EqEntity& entity, const EqNode* node)
{
  if (!node)
    return (false);
  if (node->getEntity() && *node->getEntity() == entity)
    return (true);
  if (node->getLeft() && node->getRight())
    return (findEntityInNode(entity, node->getLeft())
	    || findEntityInNode(entity, node->getRight()));
  return (false);
}

EqNode*	Equation::getEpuredNode(EqNode* node)
{
  EqNode*	newNode = epureNode(node);

  while (hasNodeToEpure(newNode))
    {
      EqNode* tmp = newNode;
      newNode = epureNode(newNode);
      delete tmp;
    }
  return (newNode);
}

bool	Equation::hasNodeToEpure(EqNode* node)
{
  if (!node)
    return (false);
  if (node->getOperator() && node->getOperator()->getType() == EqOperator::ADD)
    {
      if (node->getLeft()->getEntity()
	  && *node->getLeft()->getEntity() == EqEntity(0))
	return (true);
      else if (node->getRight()->getEntity()
	  && *node->getRight()->getEntity() == EqEntity(0))
	return (true);
    }
  if (node->getOperator() && node->getOperator()->getType() == EqOperator::MULT)
    {
      if (node->getLeft()->getEntity()
	  && *node->getLeft()->getEntity() == EqEntity(1))
	return (true);
      else if (node->getRight()->getEntity()
	  && *node->getRight()->getEntity() == EqEntity(1))
	return (true);
    }
  if (node->getLeft() && node->getRight())
    return (hasNodeToEpure(node->getLeft())
	    || hasNodeToEpure(node->getRight()));
  return (false);
}

EqNode*	Equation::epureNode(EqNode* node)
{
  EqNode*	newNode = NULL;

  newNode = new EqNode(*node, true);
  if (newNode->getOperator())
    {
      if (newNode->getOperator()->getType() == EqOperator::ADD)
	{
	  EqNode *left = NULL, *right = NULL;
	  if (newNode->getLeft() && newNode->getLeft()->getEntity()
	      && *newNode->getLeft()->getEntity() == EqEntity(0))
	    {
	      left = newNode->getLeft();
	      right = newNode->getRight();
	    }
	  else if (newNode->getRight() && newNode->getRight()->getEntity()
		   && *newNode->getRight()->getEntity() == EqEntity(0))
	    {
	      left = newNode->getRight();
	      right = newNode->getLeft();
	    }
	  if (left && right)
	    {
	      EqNode *epured = new EqNode(*right, true);
	      EqNode *newEpured = epureNode(epured);
	      delete epured;
	      delete newNode;
	      return (newEpured);
	    }
	}
      else if (newNode->getOperator()->getType() == EqOperator::MULT)
	{
	  EqNode *left = NULL, *right = NULL;
	  if (newNode->getLeft() && newNode->getLeft()->getEntity()
	      && *newNode->getLeft()->getEntity() == EqEntity(1))
	    {
	      left = newNode->getLeft();
	      right = newNode->getRight();
	    }
	  else if (newNode->getRight() && newNode->getRight()->getEntity()
		   && *newNode->getRight()->getEntity() == EqEntity(1))
	    {
	      left = newNode->getRight();
	      right = newNode->getLeft();
	    }
	  if (left && right)
	    {
	      EqNode *epured = new EqNode(*right, true);
	      EqNode *newEpured = epureNode(epured);
	      delete epured;
	      delete newNode;
	      return (newEpured);
	    }
	}
      newNode->setLeft(epureNode(node->getLeft()), true);
      newNode->setRight(epureNode(node->getRight()), true);
    }
  return (newNode);
}

void	Equation::injectValues(const EqEntity& entity, double value,
			       EqNode* node)
{
  if (node == NULL)
    node = _root;
  if (node->getEntity() && *node->getEntity() == entity)
    node->getEntity()->setValue(value);
  if (node->getLeft())
    injectValues(entity, value, node->getLeft());
  if (node->getRight())
    injectValues(entity, value, node->getRight());
}

double	Equation::evalNode(const EqNode* node, const EqEntity* entity,
			   double value) const
{
  if (node == NULL)
    node = _root;
  if (node->getEntity())
    {
      if (entity != NULL && *node->getEntity() == *entity)
	return (value);
      else if (!node->getEntity()->isUnknown())
	return (node->getEntity()->getValue());
      else
	return (0);
    }
  if (node->getOperator() && node->getOperator()->getType() == EqOperator::ADD)
    return (evalNode(node->getLeft(), entity, value)
	    + evalNode(node->getRight(), entity, value));
  else if (node->getOperator()
	   && node->getOperator()->getType() == EqOperator::SUB)
    return (evalNode(node->getLeft(), entity, value)
	    - evalNode(node->getRight(), entity, value));
  else if (node->getOperator()
	   && node->getOperator()->getType() == EqOperator::MULT)
    return (evalNode(node->getLeft(), entity, value)
	    * evalNode(node->getRight(), entity, value));
  else if (node->getOperator()
	   && node->getOperator()->getType() == EqOperator::DIV)
    return (evalNode(node->getLeft(), entity, value)
	    / evalNode(node->getRight(), entity, value));
  else
    return (0);
}
