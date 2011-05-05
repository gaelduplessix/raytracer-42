//
// EquationSolver.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Fri Apr 29 11:44:41 2011 loick michard
// Last update Thu May  5 18:05:58 2011 loick michard
//

#include <cmath>
#include "EquationSolver.hpp"
#include "Raytracer.hpp"

vector<double> 
EquationSolver::solveQuadraticEquation(double a, double b, double c,
				       bool all)
{
  double		delta;
  vector<double>	result;
  double		k;

  delta = b * b - 4 * a * c;
  if (delta < 0)
    return (result);
  if (delta >= 0)
    {
      k = (-b + sqrt(delta)) / (2 * a);
      if (all || k > EPSILON)
      	result.push_back(k);
    }
  if (delta > 0)
    {
      k = (-b - sqrt(delta)) / (2 * a);
      if (all || k > EPSILON)
      	result.push_back(k);
    }
  return (result);
}

vector<double>
EquationSolver::CardanMethod(double p, double q)
{
  double delta = q * q + (4.0 / 27.0) * p * p * p;
  vector<double> solutions;

  if (delta > 0)
    solutions.push_back(cbrt((-q + sqrt(delta)) / 2.0) +
			cbrt((-q - sqrt(delta)) / 2.0));
  if (delta == 0)
    {
      solutions.push_back((3.0 * q) / p);
      solutions.push_back((-3.0 * q) / (2.0 * p));
    }
  if (delta < 0)
    {
      for (int i = 0; i <= 2; i++)
	solutions.push_back(2.0 * sqrt(- p / 3.0) * 
			    cos((1.0 / 3.0) *
				acos((-q / 2.0) *
				     sqrt(27.0 / (- p * p * p))) +
				(2.0 * i * M_PI) / 3.0));
    }
  return (solutions);
}

vector<double> 
EquationSolver::solveCubicEquation(double a, double b, 
				   double c, double d,
				   bool all)
{
  if (a == 0)
    return (EquationSolver::solveQuadraticEquation(b, c, d));
  vector<double> solutions = CardanMethod(- ((b * b)/ (3.0 * a * a)) 
					  + (c / a),
					  (b / (27.0 * a)) *
					  (( 2.0 * b * b) / (a * a) -
					   (9.0 * c) / a) + d / a);
  vector<double> final;
  for (unsigned int i = 0; i < solutions.size(); i++)
    {
      solutions[i] -= b / (3 * a);
      if (solutions[i] > EPSILON)
	final.push_back(solutions[i]);
    }
  if (all)
    return (solutions);
  return (final);
}

vector<double>
EquationSolver::solveQuarticEquation(double a, double b,
				     double c, double d,
				     double e, bool all)
{
  if (a == 0)
    return (EquationSolver::solveCubicEquation(b, c, d, e, all));
  double p = (- 3.0 * b * b) / (8.0 * a * a) + c / a;
  double q = (pow(b / 2.0, 3) / (a * a * a)) - 
    ((1.0 / 2.0) * b * c) / (a * a) + d / a;
  double r = - 3.0 * pow((b / 4.0) / a, 4) + 
    c * (((b / 4.0) * (b / 4.0)) / (a * a * a)) -
    ((1.0 / 4.0) * b * d) / (a * a) + e / a;
  double y0 = 
    EquationSolver::solveCubicEquation(8.0, - 4.0 * p, 
				       - 8.0 * r,
				       4.0 * r * p - q * q,
				       true)[0];
  double a0 = sqrt(-p + 2 * y0);
  double b0 = (2 * y0 - p != 0) ? - q / (2 * a0) :
    y0 * y0 -r;
  vector<double> sol1 = 
    EquationSolver::solveQuadraticEquation(1, -a0, y0 - b0, true);
  vector<double> sol2 =
    EquationSolver::solveQuadraticEquation(1, a0, y0 + b0, true);
  vector<double> solutions;
  for (unsigned int i = 0; i < sol1.size(); i++)
    {
      sol1[i] -= b / (4 * a);
      if (all || sol1[i] > EPSILON)
	solutions.push_back(sol1[i]);
    }
  for (unsigned int i = 0; i < sol2.size(); i++)
    {
      sol2[i] -= b / (4 * a);
      if (all || sol2[i] > EPSILON)
	solutions.push_back(sol2[i]);
    }
  return (solutions);
}
