/**
 * Base Class:
 * This Matrix class allows the user perform the necessary Matrix operations.
 */

#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
#include <iostream>
#include <math.h>
#include <fstream>

using namespace std;

template <typename T>
class Matrix{

    vector <vector <T> > Data; // The actual data in the Matrix

    unsigned cols; // number of columns
    unsigned rows; // number of rows
public:

    Matrix();

    void add_row(vector <T> new_row);
    void add_col(vector <T> new_col);
    void print(int width = 6, int precision = 3);

    void clear();
    void unity(int n);

    double determinant();

    T sum();
    T& operator () (unsigned r, unsigned c);

    unsigned get_rows(){return rows;};
    unsigned get_cols(){return cols;};

    Matrix<T> mult(Matrix<T> rhs);

    Matrix<T> t();
    Matrix<T> submatrix(unsigned row, unsigned col);
    Matrix<T> cofactor();
    Matrix<T> adjugate();
    Matrix<T> inverse();
    Matrix<T> diag();
    Matrix<T> operator += (Matrix<T> rhs);
    Matrix<T> operator + (T rhs);
    Matrix<T> operator * (Matrix<T> rhs);
    Matrix<T> operator * (T rhs);
    Matrix<T> operator -= (Matrix<T> rhs);

    friend Matrix<T> operator + (Matrix<T> lhs, Matrix<T> rhs){return lhs += rhs;};
    friend Matrix<T> operator - (Matrix<T> lhs, Matrix<T> rhs){return lhs -= rhs;};
};

#endif // MATRIX_H
