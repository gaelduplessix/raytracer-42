//
// EqNode.cpp for  in /home/jochau_g//Desktop/equation-solver
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Thu May  5 14:29:25 2011 gael jochaud-du-plessix
// Last update Wed May 11 00:09:22 2011 gael jochaud-du-plessix
//

#include "EqNode.hpp"

#include <vector>
#include <iostream>

EqNode::EqNode(const EqNode& node, bool deep):
  _operator(node._operator), _entity(node._entity), _left(node._left),
  _right(node._right), _parent(node._parent)
{
  if (deep)
    {
      if (node._operator)
	_operator = new EqOperator(*node._operator);
      if (node._entity)
	_entity = new EqEntity(*node._entity);
      if (node._left)
	{
	  _left = new EqNode(*node._left, true);
	  _left->_parent = this;
	}
      if (node._right)
	{
	  _right = new EqNode(*node._right, true);
	  _right->_parent = this;
	}
      _parent = node._parent;
    }
}

EqNode::EqNode(int operatorType, EqNode* left, EqNode* right, EqNode* parent):
  _parent(parent)
{
  _entity = NULL;
  _left = new EqNode(*left, true);
  _left->_parent = this;
  _right = new EqNode(*right, true);
  _right->_parent = this;
  _operator = new EqOperator(operatorType);
}

EqNode::EqNode(string node, EqNode* parent):
  _operator(NULL), _entity(NULL), _left(NULL), _right(NULL), _parent(parent)
{
  int	operatorPos = -1;
  int operatorType = -1;

  while ((operatorPos = _getOperatorPos(node, operatorType)) == -1
	 && !_isEntity(node))
    _unwrapParenthesis(node);

  if (operatorPos == -1 || operatorType == -1)
    _entity = new EqEntity(node);
  else
    {
      string leftPart  = node.substr(0, operatorPos);
      string rightPart = node.substr(operatorPos + 1, string::npos);
      _left = new EqNode(leftPart, this);
      _right = new EqNode(rightPart, this);
      _operator = new EqOperator(operatorType);
    }
}

EqNode::EqNode(double value, EqNode* parent):
  _parent(parent)
{
  _entity = new EqEntity(value);
  _left = NULL;
  _right = NULL;
  _operator = NULL;
}

EqOperator*	EqNode::getOperator(void) const
{
  return (_operator);
}

EqEntity*	EqNode::getEntity(void) const
{
  return (_entity);
}

EqNode*		EqNode::getLeft(void) const
{
  return (_left);
}

EqNode*		EqNode::getRight(void) const
{
  return (_right);
}

EqNode*		EqNode::getParent(void) const
{
  return (_parent);
}

void	EqNode::setOperator(EqOperator* value, bool deletePrevious)
{
  if (deletePrevious && _operator)
    delete _operator;
  _operator = value;
}

void	EqNode::setEntity(EqEntity* value, bool deletePrevious)
{
  if (deletePrevious && _entity)
    delete _entity;
  _entity = value;
}

void	EqNode::setLeft(EqNode* value, bool deletePrevious)
{
  if (deletePrevious && _left)
    delete _left;
  _left = value;
  if (_left)
    _left->setParent(this);
}

void	EqNode::setRight(EqNode *value, bool deletePrevious)
{
  if (deletePrevious && _right)
    delete _right;
  _right = value;
  if (_right)
    _right->setParent(this);
}

void	EqNode::setParent(EqNode *value, bool deletePrevious)
{
  if (deletePrevious && _parent)
    delete _parent;
  _parent = value;
}

EqNode::~EqNode(void)
{
  if (_operator)
    delete _operator;
  if (_entity)
    delete _entity;
  if (_left)
    delete _left;
  if (_right)
    delete _right;
}

int	EqNode::_getOperatorPos(const string& node, int& operatorType)
{
  vector< vector<string> >	operators;
  int	parCount;
  unsigned int	i, j, k;
	
  operators.resize(2);
  operators[0].push_back(EqOperator::getLabel(EqOperator::ADD));
  operators[0].push_back(EqOperator::getLabel(EqOperator::SUB));
  operators[1].push_back(EqOperator::getLabel(EqOperator::MULT));
  operators[1].push_back(EqOperator::getLabel(EqOperator::DIV));
  operators[1].push_back(EqOperator::getLabel(EqOperator::POW));
  for (i = 0; i < 2; i++)
    {
      unsigned int nbOps = operators[i].size();
      for (j = 0; j < nbOps; j++)
	{
	  parCount = 0;
	  for (k = 0; k <= node.size(); k++)
	    {
	      if (parCount == 0
		  && node.compare(k, operators[i][j].size(),
				  operators[i][j]) == 0)
		{
		  operatorType = EqOperator::getType(operators[i][j]);
		  return (k);
		}
	      else if (node[k] == '(')
		parCount++;
	      else if (node[k] == ')')
		parCount--;
	    }
	}
    }
  return (-1);
}

bool		EqNode::_isEntity(const string& node)
{
  string validChars = "qwertyuiopasdfghjklzxcvbnm0123456789_.";
  validChars += "QWERTYUIOPASDFGHJKLZXCVBNM";
  if (node.find_first_not_of(validChars)
      != string::npos)
    return (false);
  return (true);
}

void	EqNode::_unwrapParenthesis(string& node)
{
  if (node[0] == '(' && node[node.size() - 1] == ')')
    {
      node.erase(0, 1);
      node.erase(node.size() - 1, 1);
    }
  else
    throw EqNode::ERROR_PARENTHESIS;
}

ostream&	operator<<(ostream &flux, const EqNode& node)
{
  if (node._entity)
    {
      if (node._entity->isUnknown())
	flux << node._entity->getName();
      else
	flux << node._entity->getValue();
    }
  else
    {
      flux << "( ";
      if (node._left)
	flux << *node._left;
      if (node._operator)
	flux << ' ' << EqOperator::getLabel(node._operator->getType())
	     << ' ';
      if (node._right)
	flux << *node._right;
      flux << " )";
    }
  return (flux);
}

