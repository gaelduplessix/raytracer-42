//
// Matrix.hpp for raytracer in /home/michar_l//Raytracer
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Wed Apr 27 15:29:58 2011 loick michard
// Last update Wed Apr 27 15:47:59 2011 loick michard
//

#ifndef _MATRIX_H_
#define _MATRIX_H_

class Matrix
{
public:
  Matrix();
  Matrix(int size);
  Matrix(int sizeL, int sizeM);
  ~Matrix();

  void		setValue(int l, int m, double value);
  double	getValue(int l, int m) const;

  Matrix&        operator+=(Matrix& matrix);
  Matrix&        operator-=(Matrix& matrix);
  Matrix&        operator*=(Matrix& matrix);

private:
  vector< vector<double> > _matrix;
};

Matrix&  operator+(const Matrix& matrix1, const Matrix& matrix2);
Matrix&  operator-(const Matrix& matrix1, const Matrix& matrix2);
Matrix&  operator*(const Matrix& matrix1, const Matrix& matrix2);

Vector&  operator+(const Matrix& matrix, const Vector& vector);
Vector&  operator-(const Matrix& matrix, const Vector& vector);
Vector&  operator*(const Matrix& matrix, const Vector& vector);

#endif
