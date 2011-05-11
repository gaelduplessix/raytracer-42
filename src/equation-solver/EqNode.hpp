//
// EqNode.hpp for  in /home/jochau_g//Desktop/equation-solver
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Thu May  5 13:59:00 2011 gael jochaud-du-plessix
// Last update Fri May  6 16:14:36 2011 gael jochaud-du-plessix
//

#ifndef _EQNODE_HPP_
#define _EQNODE_HPP_

#include <string>

using namespace std;

#include "EqOperator.hpp"
#include "EqEntity.hpp"

class EqNode
{
public:
	static const int ERROR_PARENTHESIS = 0;

	EqNode(const EqNode& node, bool deep=false);
	EqNode(int operatorType, EqNode* left, EqNode* right, EqNode* parent);
	EqNode(string node, EqNode* parent);
	EqNode(double value, EqNode* parent);
	~EqNode(void);
	
	EqOperator*	getOperator(void) const;
	EqEntity*	getEntity(void) const;
	EqNode*		getLeft(void) const;
	EqNode*		getRight(void) const;
	EqNode*		getParent(void) const;
	
	void		setOperator(EqOperator* value, bool deletePrevious=false);
	void		setEntity(EqEntity* entity, bool deletePrevious=false);
	void		setLeft(EqNode* node, bool deletePrevious=false);
	void		setRight(EqNode *node, bool deletePrevious=false);
	void		setParent(EqNode *node, bool deletePrevious=false);
	
	friend ostream&	operator<<(ostream &flux, const EqNode& node);

protected:
	int		_getOperatorPos(const string& node, int& operatorType);
	bool	_isEntity(const string& node);
	void	_unwrapParenthesis(string& node);

private:
	EqOperator*	_operator;
	EqEntity*	_entity;
	EqNode*		_left;
	EqNode*		_right;
	EqNode*		_parent;
};

#endif
