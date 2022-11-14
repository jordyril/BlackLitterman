/**
    matrix.cpp
    @author Jordy Rillaerts
    @version 1.0 18/03/18
*/

#include "matrix.h"
#include <iomanip>
#include <fstream>

using namespace std;

/*!
 * Constructor.
 * Puts the initial values for the amount of rows and columns to zero for every new matrix
 */
template <typename T>
Matrix<T>::Matrix(){
    rows = 0;
    cols = 0;
}

/*!
 * Add row.
 * Allows for adding extra rows to the matrix. The amount of elements in the row should match the amount
 * of columns already present.
 * @param new_row. The row that needs to be added to the matrix. Should be in the form of a vector.
 */
template <typename T>
void Matrix<T>::add_row(vector<T> new_row){
    if (new_row.size() != cols and cols != 0){ // if matrix is not empty, check if elements in new row match the number of columns
        cout << "Dimensions do not fit, not able to add row" << endl;
    }

    else{
        Data.push_back(new_row);

        rows++; // a new row is added, hence row object should be increased by 1

        if (cols == 0){ // In the case of an empty matrix, adding a new row automatically sets the amount of columns as well.
            cols = new_row.size();
        }
    }
}

/*!
 * Add columns.
 * Allows for adding extra columns to the matrix. The amount of elements in the columns should match the amount
 * of rows already present.
 * @param new_col. The columns that needs to be added to the matrix. Should be in the form of a vector.
 */
template <typename T>
void Matrix<T>::add_col(vector<T> new_col){
    if (new_col.size() != rows and rows != 0){// if matrix is not empty, check if elements in new columns match the number of rows
        cout << "Dimensions do not fit, not able to addd column" << endl;
    }

    else{
        for (unsigned i = 0; i < rows; i++){
            Data[i].push_back(new_col[i]);
        }

        cols++; // a new columns is added, hence row object should be increased by 1

        if (rows == 0){ // In the case of an empty matrix, adding a new column automatically sets the amount of rows as well.
            rows = new_col.size();
        }
    }
}

/*!
 * Print.
 * Allows for printing the Matrix to the console. This happens row by row.
 * @param width. The width of every cel.
 * @param precision. The precision  of the numbers in the matrix
 */
template <typename T>
void Matrix<T>::print(int width, int precision){
    for (unsigned i = 0; i < rows; i++){ // row per row

        for (unsigned j = 0; j < cols; j++){ // element per element in every row
            cout.setf(ios::fixed);
            cout << setw(width) << setprecision(precision) << right << Data[i][j] << " ";
        }
        cout << endl; // After every row, a new line has to start
    }
}

/*!
 * Clear.
 * Clear the entire matrix and sets rows and cols back to their original value of 0.
 */
template <typename T>
void Matrix<T>::clear(){
    Data.clear();
    cols = 0;
    rows = 0;
}

/*!
 * Operator ().
 * Allows for easy acces to an element in the matrix.
 * @param r. the row in which the element is located. Indexing starts at 0.
 * @param c. the columns in which the element is located. Indexing starts at 0.
 * @returns the element int the r+1 th row and the c+1 th columns of the matrix.
 */
template <typename T>
T& Matrix<T>::operator () (unsigned r, unsigned c){
    if (r <= rows && c <= cols){
        return Data[r][c];
    }
    else {
        return Data[rows][cols]; // whenever the give coördinates are outside the range of the matrix, the last element gets returned
    }

}

/*!
 * Sum.
 * Takes the sum over all elements in the matrix.
 * @returns the sum of all elements of the matrix.
 */
template <typename T>
T Matrix<T>::sum(){
    T sum = 0;
    for (unsigned i = 0; i < this->rows; i++){
        for (unsigned j = 0; j < this->cols; j++){
            sum = sum + Data[i][j];
        }
    }
    return sum;
}

/*!
 * Operator +=.
 * Sums a matrix elementwise with itself.
 * @returns Matrix with at every position the sum of the elements at that same position of the original two matices
 */
template <typename T>
Matrix<T> Matrix<T>::operator +=(Matrix<T> rhs){
    Matrix<T> result;
    for (unsigned i = 0; i < this->rows; i++){
        vector<T> temp_row;

        for (unsigned j = 0; j < this->cols; j++){
            temp_row.push_back(this->Data[i][j] + rhs.Data[i][j]);
        }

        result.add_row(temp_row);
    }
    return result;
}

/*!
 * Operator +.
 * Sums two matrices elementwise.
 * @returns Matrix with at every position the sum of the elements at that same position of the original two matices
 */
template <typename T>
Matrix<T> Matrix<T>::operator + (T rhs){
    Matrix<T> result;
    for (unsigned i = 0; i < this->rows; i++){
        vector<T> temp_row;
        for (unsigned j = 0; j < this->cols; j++){
            temp_row.push_back(this->Data[i][j] + rhs);
        }

        result.add_row(temp_row);
    }
    return result;
}

/*!
 * Operator -=.
 * subtracts a mtrix elementwise with itself.
 * @returns Matrix with at every position the subtraction of the elements at that same position of the original two matices
 */
template <typename T>
Matrix<T> Matrix<T>::operator -=(Matrix<T> rhs){
    Matrix<T> result;
    for (unsigned i = 0; i < this->rows; i++){
        std::vector<T> temp_row;
        for (unsigned j = 0; j < this->cols; j++){
            temp_row.push_back(this->Data[i][j] - rhs.Data[i][j]);
        }
        result.add_row(temp_row);
    }
    return result;

}

/*!
 * Multiplication.
 * Performs matrix multiplication.
 * @returns Matrix with dimensions r_1 x c_2
 */
template <typename T>
Matrix<T> Matrix<T>::mult(Matrix<T> rhs){
    if (this->cols != rhs.rows){ // dimensions should fit
        cout << "Cannot perform this operation legally, result will not be correct" << endl;
        return *this;
    }
    else{
        Matrix<T> result;

        for (unsigned i = 0; i < this->rows; i++){
            vector<T> temp_row;
            for (unsigned j = 0; j < rhs.cols; j++){
                T sum = 0;
                for (unsigned k = 0 ; k < this->cols; k++){
                    sum = sum + this->Data[i][k] * rhs.Data[k][j];
                }
                temp_row.push_back(sum);
            }
            result.add_row(temp_row);
        }
         return result;
    }
}

/*!
 * Operator *.
 * Performs standard elementwise multiplication of a matrix with a number .
 * @returns Matrix where every element is multiplied with a given number.
 */
template <typename T>
Matrix<T> Matrix<T>::operator * (T rhs){
    Matrix<T> result;
    for (unsigned i = 0; i < this->rows; i++ ){
        vector<T> temp_row;
        for (unsigned j = 0; j < this->cols; j++){
            temp_row.push_back(rhs * this->Data[i][j]);
        }
        result.add_row(temp_row);
    }
    return result;
}

/*!
 * Operator *.
 * Performs standard elementwise multiplication of two matrices .
 * @returns Matrix where every element of the first matrix is multiplied with the element at the same positon from the second matrix.
 */
template <typename T>
Matrix<T> Matrix<T>::operator * (Matrix<T> rhs){
    if (this->cols != rhs.cols && this->rows != rhs.rows){
        cout << "Cannot perform this operation legally, result will not be correct" << endl;
        return *this;
    }
    else {
        Matrix<T> result;
        for (unsigned i = 0; i < this->rows; i++ ){
            std::vector<T> temp_row;
            for (unsigned j = 0; j < this->cols; j++){
                temp_row.push_back(rhs.Data[i][j] * this->Data[i][j]);
            }
            result.add_row(temp_row);
         }
         return result;
    }

}

/*!
 * Transpose.
 * Transposes the matrix.
 * @returns Transposed matrix with dimensions c x r.
 */
template <typename T>
Matrix<T> Matrix<T>::t(){
    Matrix<T> result;
    for (unsigned i = 0; i < this->cols; i++ ){
        vector<T> temp_row;
        for (unsigned j = 0; j < this->rows; j++){
            temp_row.push_back(this->Data[j][i]);
        }
        result.add_row(temp_row);
    }
    return result;
}

/*!
 * Unity matrix.
 * Clear the original matrix and makes it a unity matrix of order n.
 * @param n. The order of the unity matrix.
 */
template <typename T>
void Matrix<T>::unity(int n){
    Data.clear();
    for (int i = 0; i < n; i++){
        vector<T> temp_row;
        for (int j = 0; j < n; j++){
            if (j == i){
                temp_row.push_back(1);
            }
            else{
                temp_row.push_back(0);
            }
        }
        this->add_row(temp_row);
    }
}

/*!
 * Submatrix.
 * Given an element in the matrix, this method allows for creating the Minor of this element.
 * @param row. The row-number of the element. Indexing starts at 0.
 * @param col. The column-number of the element. Indexing starts at 0.
 */
template <typename T>
Matrix<T> Matrix<T>::submatrix(unsigned row, unsigned col){
    Matrix<T> result;
    for (unsigned i = 0; i < rows; i++){
        if (i != row){
            std::vector<T> temp_row;
            for (unsigned j = 0; j < cols; j++){
                if (j != col){
                    temp_row.push_back(this->Data[i][j]);
                }
            }
        result.add_row(temp_row);
        }

    }
    return result;

}

/*!
 * Determinant.
 * Computes the Determinant of a matrix. It does this in a recursive way.
 * @returns The value for the determinant of a matrix.
 */
template <typename T>
double Matrix<T>::determinant(){
    if (rows != cols){
        cout << "This operation is only possible for square matrices" << endl;
    }

    double result = 0;

    if (rows == 1){ // The determinant of a matrix with 1 element, is the element itself.
        result = Data[0][0];
    }
    else { // As long as the order of the matrix is greater than 1, a submatrix can be created and the determinant of that submatrix should be computed first

        for (unsigned i = 0; i < cols; i++){
            int sign;
            ( i % 2 == 0 ) ? sign = 1: sign = -1;
            double det = this->submatrix(0, i).determinant();
            double d = Data[0][i];
            result = result + (sign * d * det);
        }
    }
    return result;
}

/*!
 * Cofactor.
 * Computes the cofactor matrix. C_i_j = (-1)^{i + j} * M_i_j
 * with M_i_j the Minor of element a_i_j.
 * @returns the matrix of cofactors
 */
template <typename T>
Matrix<T> Matrix<T>::cofactor(){
    Matrix<T> result;
    for (unsigned i = 0; i < rows; i++){
        vector<T> temp_row;
        for ( unsigned j = 0; j < cols; j++){

            int sign;
            ( (i + j) % 2 == 0 ) ? sign = 1 : sign = -1;

            double minor = (this->submatrix(i, j)).determinant();

            temp_row.push_back(sign * minor);
        }

        result.add_row(temp_row);
    }
    return result;

}

/*!
 * Adjugate.
 * Computes the Adjugate matrix as the transposed of the cofactor matrix.
 * @returns the adjugate matrix.
 */
template <typename T>
Matrix<T> Matrix<T>::adjugate(){
    return (this->cofactor()).t();
}

/*!
 * Inverse.
 * Computes the Inverse matrix: Inve(A) = 1/det(A) * Adj(A).
 * @returns the inverse matrix.
 */
template <typename T>
Matrix<T> Matrix<T>::inverse(){
    double det = this->determinant();

    double det_inv = 1 / det;
    Matrix<T> adj = this->adjugate();
    return adj * det_inv;
}

/*!
 * Diagonal.
 * Computes the Diagonal matrix of a square matrix. Meaning that only the elements on the diagonal remain, other elements are put to 0.
 * @returns the diagonal matrix.
 */
template <typename T>
Matrix<T> Matrix<T>::diag(){
    if (this->cols == this->rows){
        Matrix<T> result;
        for (unsigned i = 0; i < rows; i++ ){
            vector<T> temp_row;
            for (unsigned j = 0; j < cols; j++){
                if (i == j){
                    temp_row.push_back(Data[i][j]);
                }
                else{
                    temp_row.push_back(0);
                }
            }
            result.add_row(temp_row);
        }
        return result;
    }
    else {
        cout << "The matrix is not squaure, hence this operation cannot be performed legally" << endl;
        return *this;
    }

}


