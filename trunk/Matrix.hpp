//
// Matrix.hpp for raytracer in /home/michar_l//Raytracer
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Wed Apr 27 15:29:58 2011 loick michard
// Last update Thu Apr 28 23:12:19 2011 loick michard
//

#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <vector>
#include "Vector.hpp"

using namespace std;

class Matrix
{
public:
  Matrix();
  Matrix(int size);
  Matrix(int sizeM, int sizeN);
  ~Matrix();

  void		setValue(int m, int n, double value);
  double	getValue(int m, int n) const;
  int		getSizeM() const;
  int		getSizeN() const;

  const Matrix&        operator+=(const Matrix& matrix);
  template <class T>
  const Matrix&        operator*=(T value);

  friend Matrix  operator*(const Matrix& matrix1, const Matrix& matrix2);
  friend Matrix  operator+(const Matrix& matrix1, const Matrix& matrix2);
  friend Vector  operator*(const Vector& vector, const Matrix& matrix); 
  template <class T>
  friend Matrix  operator+(const Matrix& matrix, T value);
  template <class T>
  friend Matrix  operator*(const Matrix& matrix, T value);

private:
  vector< vector<double> > _matrix;
};

Matrix  operator+(const Matrix& matrix1, const Matrix& matrix2);
Matrix  operator*(const Matrix& matrix1, const Matrix& matrix2);
Vector  operator*(const Vector& vector, const Matrix& matrix);
Vector  operator*(const Matrix& matrix, const Vector& vector);

template <class T>
const Matrix&  Matrix::operator*=(T value)
{
  for (int i = 0; i < this->getSizeM(); i++)
    for (int j = 0; j < this->getSizeN(); j++)
      _matrix[i][j] *= value;
  return (*this);
}

template <class T>
Matrix  operator+(const Matrix& matrix, T value)
{
  Matrix result = matrix;

  for (int i = 0; i < matrix.getSizeM(); i++)
    for (int j = 0; j < matrix.getSizeN(); j++)
      result._matrix[i][j] += value;
  return (result);
}

template <class T>
Matrix  operator*(const Matrix& matrix, T value)
{
  Matrix result = matrix;

  for (int i = 0; i < matrix.getSizeM(); i++)
    for (int j = 0; j < matrix.getSizeN(); j++)
      result._matrix[i][j] *= value;
  return (result);
}

template <class T>
Matrix  operator*(T value, const Matrix& matrix)
{
  return (matrix * value);
}

#endif
