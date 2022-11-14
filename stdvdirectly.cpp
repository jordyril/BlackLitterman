/**
    stdvdirectly.cpp
    @author Jordy Rillaerts
    @version 1.0 18/03/18
*/

#include "stdvdirectly.h"
#include <math.h>

/*
 * Constructor
 */
STDVdirectly::STDVdirectly(double market_inefficiency){
    tau = market_inefficiency;

}

/*
 * Constructor
 */
STDVdirectly::STDVdirectly(){

}

/*!
 * Omega
 * Computes the omega matrix based on simple standard deviations.
 * Omega is a diagonal matrix with on the diagonal the variances of the views.
 * @param views. The views combination for which this matrix needs to be computed
 * @return Omega matrix.
 */
Matrix<double> STDVdirectly::omega(){
    Matrix<double> result;
    for (auto i = views->views.begin(); i < views->views.end(); i++){
        vector<double> temp_row;
        for (auto j = views->views.begin(); j < views->views.end(); j++){
            if (i == j){
                temp_row.push_back(pow(i->standard_error, 2));
            }
            else {
                temp_row.push_back(0);
            }
        }
        result.add_row(temp_row);
    }
    return result;
}


/*
 * Name
 * returns the name of this class
 */
string STDVdirectly::name(){
     return "STDV directly";
}
