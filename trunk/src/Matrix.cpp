//
// Matrix.cpp for raytracer in /home/michar_l//Raytracer/raytracer-42
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Thu Apr 28 21:17:09 2011 loick michard
// Last update Sat Apr 30 12:37:41 2011 samuel olivier
//

#include "Matrix.hpp"

Matrix::Matrix()
{

}

Matrix::Matrix(int size)
{
  _matrix.resize(size);
  for (int i = 0; i < size ; i++)
    {
      _matrix[i].resize(size);
      i++;
    }
}

Matrix::Matrix(int sizeM, int sizeN)
{
  _matrix.resize(sizeM);
  for (int i = 0; i < sizeM ; i++)
    {
      _matrix[i].resize(sizeN);
      i++;
    }
}

Matrix::~Matrix()
{

}

void	Matrix::setValue(int m, int n, double value)
{
  _matrix[m][n] = value;
}

double	Matrix::getValue(int m, int n) const
{
  return (_matrix[m][n]);
}

int	Matrix::getSizeM() const
{
  return (_matrix.size());
}

int	Matrix::getSizeN() const
{
  if (_matrix.size())
    return (_matrix[0].size());
  else
    return (0);
}

const Matrix&        Matrix::operator+=(const Matrix& matrix)
{
  if (_matrix.size()
      && _matrix.size() == matrix._matrix.size()
      && _matrix[0].size() == matrix._matrix[0].size())
    {
      for (unsigned int i = 0; i < _matrix.size() ; i++)
	for (unsigned int j = 0; j < _matrix.size() ; j++)
	  _matrix[i][j] += matrix._matrix[i][j];
    }
  return (*this);
}

Matrix		operator*(const Matrix& matrix1, 
			  const Matrix& matrix2)
{
  unsigned int		m;
  unsigned int		n;
  unsigned int		p;

  m = matrix1._matrix.size();
  n = matrix2._matrix.size();
  p = 0;
  if (n && m)
    p = matrix2._matrix[0].size();

  Matrix matrix(m, p);
  if (n && m
      && n == matrix1._matrix[0].size())
    {
      for (unsigned int i = 0; i < m; i++)
	for (unsigned int j = 0; j < p; j++)
	  {
	    matrix._matrix[i][j] = 0;
	    for(unsigned int k = 0; k < n; k++)
	      matrix._matrix[i][j] += 
		matrix1._matrix[i][k] * matrix1._matrix[k][j];
	  }
    }
  return (matrix);
}

Matrix  operator+(const Matrix& matrix1, const Matrix& matrix2)
{
  Matrix matrix = matrix1;

  matrix += matrix2;
  return (matrix);
}

Vector  operator*(const Vector& vector, const Matrix& matrix)
{
  Vector result;

  if (matrix._matrix.size() == 3 && matrix._matrix[0].size() == 3)
    {
      result.setX(vector._x * matrix._matrix[0][0] +
		  vector._y * matrix._matrix[0][1] +
		  vector._z * matrix._matrix[0][2]);
      result.setY(vector._x * matrix._matrix[1][0] +
                  vector._y * matrix._matrix[1][1] +
                  vector._z * matrix._matrix[1][2]);
      result.setZ(vector._x * matrix._matrix[2][0] +
                  vector._y * matrix._matrix[2][1] +
                  vector._z * matrix._matrix[2][2]);
    }
  return (result);
}

Vector  operator*(const Matrix& matrix, const Vector& vector)
{
  return (vector * matrix);
}
