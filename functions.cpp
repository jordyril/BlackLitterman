#include "functions.h"
#include <iomanip>

void print_vector(vector <double>vect){
    for (vector<double>::iterator i = vect.begin(); i < vect.end(); i++){
        cout << *i << endl ;
    }
}

void print_matrix(vector< vector <double> > matrix){
    for (auto i = matrix.begin(); i < matrix.end(); i++){
        for (auto j = i->begin(); j < i->end(); j++){
            cout << *j << " ";
        }
        cout << endl;

    }
}

string periodicity(int factor){
    string periodicity;
    switch (factor){
    case 1:
        periodicity = "Annual";
        break;
    case 12:
        periodicity = "Monthly";
        break;
    case 250:
    case 252:
        periodicity = "Daily";
        break;
    case 52:
        periodicity = "Weekly";
        break;
    default:
        periodicity = "Periodical";
        break;
    }
    return periodicity;
}

void write_matrix_to_file(ofstream& out, Matrix<double> m, int width, int precision){
    for (unsigned i = 0; i < m.get_rows(); i++){ // row per row

        for (unsigned j = 0; j < m.get_cols(); j++){ // element per element in every row
            out  << setw(width) << setprecision(precision) <<  right << m(i, j) << " ";
        }
        out << endl; // After every row, a new line has to start
    }
}







