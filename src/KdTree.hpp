//
// KdTree.hpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Wed May 18 10:27:25 2011 loick michard
// Last update Wed May 18 14:16:41 2011 loick michard
//

#ifndef _KD_TREE_HPP_
#define _KD_TREE_HPP_

#include "Object.hpp"
#include "BoundingBox.hpp"

typedef struct	kdTreeNode
{
  vector<ObjectPrimitive*>	primitives;
  BoundingBox			box;
  struct kdTreeNode		*leftChild;
  struct kdTreeNode		*rightChild;
  struct kdTreeNode		*parent;
}		kdTreeNode;

class KdTree
{
  KdTree(const vector<Object*>& objects);
  ~KdTree();
};

#endif
