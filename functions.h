#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <vector>
#include <iostream>
#include <fstream>
#include "matrix.h"

using namespace std;


void print_vector(vector <double>vect);
void print_matrix(vector < vector <double> > matrix);

void write_matrix_to_file(ofstream& out, Matrix<double> m, int width = 2, int precision = 1);



#endif // FUNCTIONS_H
