//
// EquationSolver.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Fri Apr 29 11:44:41 2011 loick michard
// Last update Sat Apr 30 10:59:07 2011 loick michard
//

#include <cmath>
#include "EquationSolver.hpp"
#include "Raytracer.hpp"

vector<double> 
EquationSolver::solveQuadraticEquation(double a, double b, double c)
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
      if (k > EPSILON)
      	result.push_back(k);
    }
  if (delta > 0)
    {
      k = (-b - sqrt(delta)) / (2 * a);
      if (k > EPSILON)
      	result.push_back(k);
    }
  return (result);
}
