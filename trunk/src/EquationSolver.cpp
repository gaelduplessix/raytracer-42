//
// EquationSolver.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Fri Apr 29 11:44:41 2011 loick michard
// Last update Fri Apr 29 11:53:22 2011 loick michard
//

#include <cmath>
#include "EquationSolver.hpp"

vector<double> 
EquationSolver::solveQuadraticEquation(double a, double b, double c)
{
  double		delta;
  vector<double>	result;

  delta = b * b - 4 * a * c;
  if (delta < 0)
    return (result);
  if (delta >= 0)
    result.push_back((-b + sqrt(delta)) / (2 * a));
  if (delta > 0)
    result.push_back((-b - sqrt(delta)) / (2 * a));
  return (result);
}
