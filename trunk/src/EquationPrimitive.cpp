//
// EquationPrimitive.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
//
// Made by loick michard
// Login   <michar_l@epitech.net>
//
// Started on  Fri Apr 29 10:41:20 2011 loick michard
// Last update Sun Jun  5 16:56:28 2011 melvin laplanche
//

#include <cmath>
#include <vector>
#include "Raytracer.hpp"
#include "EquationPrimitive.hpp"
#include "EquationSolver.hpp"

EquationPrimitive::EquationPrimitive(string equation,
				     Object* object,
				     const Point& absolutePosition,
				     const Rotation& rotation,
				     Material* material) :
  ObjectPrimitive(object, absolutePosition, rotation, material),
  _equation_intersect(), _equation_normal_x(), _equation_normal_y(),
  _equation_normal_z()
{
  _equation_normal_x.initWithString(equation);
  _equation_normal_y.initWithString(equation);
  _equation_normal_z.initWithString(equation);
  _equation_normal_x.derivate(EqEntity("x"));
  _equation_normal_y.derivate(EqEntity("y"));
  _equation_normal_z.derivate(EqEntity("z"));
  string*	vars = new string[3];
  string*	replacements = new string[3];
  vars[0] = "x";
  replacements[0] = "(X0 + k * VX)";
  vars[1] = "y";
  replacements[1] = "(Y0 + k * VY)";
  vars[2] = "z";
  replacements[2] = "(Z0 + k * VZ)";
  for (int i = 0; i < 3; i++)
    {
      size_t pos;
      while ((pos = equation.find(vars[i])) != string::npos)
  	equation.replace(pos, vars[i].size(), replacements[i]);
    }
  _equation_intersect.initWithString(equation);
  _equation_intersect.develop();
  _equation_intersect.factorize(EqEntity("k"));
  delete[] vars;
  delete[] replacements;
}

void		EquationPrimitive::getMappedCoords(const Point& intersectPoint,
						   double& x, double &y) const
{
  x = 0;
  y = 0;
  return ;
  (void)intersectPoint;
}

void        EquationPrimitive::
addIntersectionWithRay(const Ray& ray, vector<struct s_intersected_object>&
		       intersection) const
{
  Ray newRay = getRayAtSimplePosition(ray);
  vector< EqNode* >	coeffNodes;
  vector< double >	coeffs;
  unsigned int		degree = _equation_intersect.getDegree();
  if (degree >= 1 && degree <= 4)
    {
      coeffNodes.resize(degree + 1);
      coeffs.resize(degree + 1);
      for (unsigned int i = 0; i <= degree; i++)
	{
	  coeffNodes[i] = _equation_intersect.getFactorizedCoeff(i);
	  coeffNodes[i] = new EqNode(*coeffNodes[i], true);
	  _injectCoeffs(newRay, coeffNodes[i]);
	  coeffs[i] = _equation_intersect.evalNode(coeffNodes[i], NULL);
	  delete coeffNodes[i];
	}
      vector<double> solutions =
	EquationSolver::solveEquation(coeffs);

      vector<double> validSolutions;
      for (unsigned int i = 0 ; i < solutions.size(); i++)
	if (solutions[i] > EPSILON)
	  validSolutions.push_back(solutions[i]);
      if (validSolutions.size() > 0)
	intersection.push_back((t_intersected_object){this, validSolutions});
    }
}

void	EquationPrimitive::intersectWithRay(const Ray& ray,
					    ObjectPrimitive*& primitive,
					    double &res) const
{
  Ray newRay = getRayAtSimplePosition(ray);
  vector< EqNode* >	coeffNodes;
  vector< double >	coeffs;
  unsigned int		degree = _equation_intersect.getDegree();
  if (degree >= 1 && degree <= 4)
    {
      coeffNodes.resize(degree + 1);
      coeffs.resize(degree + 1);
      for (unsigned int i = 0; i <= degree; i++)
	{
	  coeffNodes[i] = _equation_intersect.getFactorizedCoeff(i);
	  coeffNodes[i] = new EqNode(*coeffNodes[i], true);
	  _injectCoeffs(newRay, coeffNodes[i]);
	  coeffs[i] = _equation_intersect.evalNode(coeffNodes[i], NULL);
	  delete coeffNodes[i];
	}
      vector<double> solutions =
	EquationSolver::solveEquation(coeffs);
      for (unsigned int i = 0; i < solutions.size(); i++)
	{
	  if (solutions[i] > EPSILON && (solutions[i] < res ||  res < 0))
	    {
	      primitive = (ObjectPrimitive*)this;
	      res = solutions[i];
	    }
	}
    }
}

void	EquationPrimitive::_injectCoeffs(const Ray& ray, EqNode* node) const
{
  ((Equation*)&_equation_intersect)->
    injectValues(EqEntity("X0"), ray._point._x, node);
  ((Equation*)&_equation_intersect)->
    injectValues(EqEntity("VX"), ray._vector._x, node);
  ((Equation*)&_equation_intersect)->
    injectValues(EqEntity("Y0"), ray._point._y, node);
  ((Equation*)&_equation_intersect)->
    injectValues(EqEntity("VY"), ray._vector._y, node);
  ((Equation*)&_equation_intersect)->
    injectValues(EqEntity("Z0"), ray._point._z, node);
  ((Equation*)&_equation_intersect)->
    injectValues(EqEntity("VZ"), ray._vector._z, node);
}

void	EquationPrimitive::_injectNormalValues(const Point& point,
					       EqNode* node) const
{
  ((Equation*)&_equation_normal_x)->
    injectValues(EqEntity("x"), point._x, node);
  ((Equation*)&_equation_normal_x)->
    injectValues(EqEntity("y"), point._y, node);
  ((Equation*)&_equation_normal_x)->
    injectValues(EqEntity("z"), point._z, node);
}

Vector	EquationPrimitive::getNormalVector(const Point& intersectPoint,
					   const Vector& viewVector) const
{
  Point		simplePoint = intersectPoint - _absolutePosition;

  EqNode	*derivX = new EqNode(*_equation_normal_x.getDerivate(), true);
  EqNode	*derivY = new EqNode(*_equation_normal_y.getDerivate(), true);
  EqNode	*derivZ = new EqNode(*_equation_normal_z.getDerivate(), true);
  _injectNormalValues(simplePoint, derivX);
  _injectNormalValues(simplePoint, derivY);
  _injectNormalValues(simplePoint, derivZ);
  Vector	normal(
		       _equation_normal_x.evalNode(derivX),
		       _equation_normal_y.evalNode(derivY),
		       _equation_normal_z.evalNode(derivZ)
);
  delete derivX;
  delete derivY;
  delete derivZ;

  double	cosA = viewVector * normal;

  cosA = cosA / (viewVector.getNorm() * normal.getNorm());
  if (cosA <= 0)
    return (normal.normalize() * -1);
  return (normal.normalize());
}

bool		EquationPrimitive::isInBoundingBox(BoundingBox& box) const
{
  box = box;
  return (true);
}
