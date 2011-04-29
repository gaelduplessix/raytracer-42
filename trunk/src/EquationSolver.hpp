//
// EquationSolver.hpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Fri Apr 29 11:41:00 2011 loick michard
// Last update Fri Apr 29 12:07:56 2011 loick michard
//

#ifndef _EQUATION_SOLVER_HPP_
#define _EQUATION_SOLVER_HPP_

#include <vector>

using namespace std;

class	EquationSolver
{
public:
  static vector<double> solveQuadraticEquation(double a, double b, double c);
};

#endif
