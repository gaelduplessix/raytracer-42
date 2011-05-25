//
// KdTree.hpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Wed May 18 10:27:25 2011 loick michard
// Last update Tue May 24 13:46:24 2011 loick michard
//

#ifndef _KD_TREE_HPP_
#define _KD_TREE_HPP_

#include "Object.hpp"
#include "BoundingBox.hpp"

typedef struct	KdTreeNode
{
  vector<ObjectPrimitive*>	primitives;
  BoundingBox			*box;
  struct KdTreeNode		*leftChild;
  struct KdTreeNode		*rightChild;
  struct KdTreeNode		*parent;
}		KdTreeNode;

typedef struct s_intersected_object t_intersected_object;

class KdTree
{
public:
  static const int xPlane = 0;
  static const int yPlane = 1;
  static const int zPlane = 2;

  KdTree(const vector<Object*>& objects, int depth = 10);
  ~KdTree();

  bool		   getNearestIntersect(Ray &ray,
				       ObjectPrimitive*& primitive,
				       double& res,
				       KdTreeNode* node);
  ObjectPrimitive* getNearestObject(Ray& ray, double &res);
  bool
  addAllIntersect(const Ray &ray,
		  vector<t_intersected_object>&
		  intersection,
		  KdTreeNode* node);

  void
  getIntersectingObjects(const Ray& ray, vector<t_intersected_object>&
			 intersection);

  void	_deleteNode(KdTreeNode *node);

protected:
  void		buildKdTree(void);
  void		subdivideKdTree(KdTreeNode *node, int depth, int plane);
  double	getMedianPrimitive(vector<ObjectPrimitive*> primitives,
				   int plane);

  int			   _maxDepth;
  vector<ObjectPrimitive*> _unlimitedObjects;
  vector<ObjectPrimitive*> _limitedObjects;
  KdTreeNode		   *_root;
};

#endif
