//
// EquationSolver.hpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Fri Apr 29 11:41:00 2011 loick michard
// Last update Wed May 11 12:37:26 2011 gael jochaud-du-plessix
//

#ifndef _EQUATION_SOLVER_HPP_
#define _EQUATION_SOLVER_HPP_

#include <vector>

using namespace std;

class	EquationSolver
{
public:
  static vector<double> solveEquation(vector<double> &coeffs);

  static vector<double> solveQuadraticEquation(double a, double b, double c,
					       bool all = false);
  static vector<double> solveCubicEquation(double a, double b, 
					   double c, double d,
					   bool all = false);
  static vector<double> solveQuarticEquation(double a, double b,
                                           double c, double d,
                                           double e, bool all = false);
  static vector<double>
  CardanMethod(double p, double q);
};

#endif
