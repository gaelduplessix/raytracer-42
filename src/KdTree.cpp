//
// KdTree.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Wed May 18 10:28:17 2011 loick michard
// Last update Mon May 23 09:31:03 2011 loick michard
//

#include <algorithm>
#include "KdTree.hpp"

KdTree::KdTree(const vector<Object*>& objects, int depth)
{
  _maxDepth = depth;
  for (unsigned int i = 0; i < objects.size(); i++)
    {
      for (unsigned int j = 0; j < objects[i]->_primitives.size(); j++)
	{
	  if (objects[i]->_primitives[j]->isLimited())
	    _limitedObjects.push_back(objects[i]->_primitives[j]);
	  else
	    _unlimitedObjects.push_back(objects[i]->_primitives[j]);
	}
    }
  this->buildKdTree();
}

KdTree::~KdTree()
{

}

bool
KdTree::getNearestIntersect(Ray &ray,
			    ObjectPrimitive*& primitive,
			    double& res,
			    KdTreeNode* node)
{
  if (!node->leftChild && !node->rightChild)
    {
      double resTmp = res;
      for (unsigned int i = 0; i < node->primitives.size(); i++)
      	node->primitives[i]->intersectWithRay(ray, primitive, res);
      if (resTmp != res)
	return (true);
      return (false);
    }
  double left = node->leftChild->box->intersectWithRay(ray);
  double right = node->rightChild->box->intersectWithRay(ray);
  if (left == -1 && right == -1)
    return (false);
  if (left != -1 && right == -1)
    return (this->getNearestIntersect(ray, primitive, 
				      res, node->leftChild));
  if (right != -1 && left == -1)
    return (this->getNearestIntersect(ray, primitive,
                                      res, node->rightChild));
  if (right < left)
    {
      if (this->getNearestIntersect(ray, primitive,
				    res, node->rightChild))
	return (true);
      return (this->getNearestIntersect(ray, primitive,
					res, node->leftChild));
    }
  else
    {
      if (this->getNearestIntersect(ray, primitive,
                                    res, node->leftChild))
        return (true);
      return (this->getNearestIntersect(ray, primitive,
                                        res, node->rightChild));
    }
}

ObjectPrimitive*		KdTree::getNearestObject(Ray& ray,
							 double& res)
{
  ObjectPrimitive*		primitive = NULL;

  res = -1;
  for (unsigned int i = 0; i < _unlimitedObjects.size(); i++)
    _unlimitedObjects[i]->intersectWithRay(ray, primitive, res);
  if (_root && _root->box->intersectWithRay(ray) != -1)
    this->getNearestIntersect(ray, primitive, res, _root);
  return (primitive);
}

bool
KdTree::addAllIntersect(const Ray &ray,
			vector<t_intersected_object>&
			intersection,
			KdTreeNode* node)
{
  if (!node->leftChild && !node->rightChild)
    {
      for (unsigned int i = 0; i < node->primitives.size(); i++)
        node->primitives[i]->addIntersectionWithRay(ray, intersection);
      return (true);
    }
  double left = node->leftChild->box->intersectWithRay(ray);
  double right = node->rightChild->box->intersectWithRay(ray);
  if (left == -1 && right == -1)
    return (false);
  if (left != -1 && right == -1)
    return (this->addAllIntersect(ray, intersection, node->leftChild));
  if (right != -1 && left == -1)
    return (this->addAllIntersect(ray, intersection, node->rightChild));
  this->addAllIntersect(ray, intersection, node->rightChild);
  this->addAllIntersect(ray, intersection, node->leftChild);
  return (true);
}

void                
KdTree::getIntersectingObjects(const Ray& ray, vector<t_intersected_object>&
			       intersection)
{
  for (unsigned int i = 0; i < _unlimitedObjects.size(); i++)
    _unlimitedObjects[i]->addIntersectionWithRay(ray, intersection);
  if (_root && _root->box->intersectWithRay(ray) != -1)
    this->addAllIntersect(ray, intersection, _root);
}

void	KdTree::buildKdTree(void)
{
  if (_limitedObjects.size())
    {
      _root = new KdTreeNode;
      _root->primitives = _limitedObjects;
      _root->parent = NULL;
      Point min = _limitedObjects[0]->getMin();
      Point max = _limitedObjects[0]->getMax();
      for (unsigned int i = 0; i < _limitedObjects.size(); i++)
	{
	  Point minTmp = _limitedObjects[i]->getMin();
	  Point maxTmp = _limitedObjects[i]->getMax();
	  if (minTmp._x < min._x)
	    min._x = minTmp._x;
	  if (minTmp._y < min._y)
            min._y = minTmp._y;
	  if (minTmp._z < min._z)
            min._z = minTmp._z;
	  if (maxTmp._x > max._x)
            max._x = maxTmp._x;
          if (maxTmp._y > max._y)
            max._y = maxTmp._y;
          if (maxTmp._z > max._z)
            max._z = maxTmp._z;
	}
      min -= 0.5;
      max += 0.5;
      _root->box = new BoundingBox(min, max);
      subdivideKdTree(_root, 0, yPlane);
    }
  else
    _root = NULL;
}

void	KdTree::subdivideKdTree(KdTreeNode *node, int depth, int plane)
{
  plane %= 3;
  if (depth > _maxDepth || node->primitives.size() <= 3 ||
      node->box->size() < 0.05)
    {
      node->leftChild = NULL;
      node->rightChild = NULL;
      return ;
    }
  double	median = getMedianPrimitive(node->primitives, plane);
  node->leftChild = new KdTreeNode;
  node->rightChild = new KdTreeNode;
  node->leftChild->parent = node->rightChild->parent = node;

  Point		medianP = node->box->getVertex2();
  if (plane == xPlane)
    medianP._x = median;
  else if (plane == yPlane)
    medianP._y = median;
  else if (plane == zPlane)
    medianP._z = median;
  node->leftChild->box = new BoundingBox(node->box->getVertex1(),
					 medianP);
  medianP = node->box->getVertex1();
  if (plane == xPlane)
    medianP._x = median;
  else if (plane == yPlane)
    medianP._y = median;
  else if (plane == zPlane)
    medianP._z = median;
  node->rightChild->box = new BoundingBox(medianP,
					  node->box->getVertex2());
  for (unsigned int i = 0; i < node->primitives.size(); i++)
    {
      if (node->primitives[i]->isInBoundingBox(*(node->leftChild->box)))
	node->leftChild->primitives.push_back(node->primitives[i]);
      if (node->primitives[i]->isInBoundingBox(*(node->rightChild->box)))
        node->rightChild->primitives.push_back(node->primitives[i]);
    }
  subdivideKdTree(node->leftChild, depth + 1, plane + 1);
  subdivideKdTree(node->rightChild, depth + 1, plane + 1);
}

double	KdTree::getMedianPrimitive(vector<ObjectPrimitive*> primitives,
				   int plane)
{
  vector<double> values;

  for (unsigned int i = 0; i < primitives.size(); i++)
    {
      if (plane == xPlane)
	values.push_back(primitives[i]->getPosition()._x);
      else if (plane == yPlane)
        values.push_back(primitives[i]->getPosition()._y);
      else if (plane == zPlane)
        values.push_back(primitives[i]->getPosition()._z);
    }
  sort(values.begin(), values.end());
  if (!(values.size() % 2))
    return (values[values.size() / 2]);
  else
    return ((values[(values.size() / 2) - 1] +
	     values[values.size() / 2]) / 2);
}
