/**
    idzorek.cpp
    @author Jordy Rillaerts
    @version 1.0 18/03/18
*/

#include "idzorek.h"

/*
 * Constructor
 */
Idzorek::Idzorek(double market_inefficiency){
    tau = market_inefficiency;
}

/*
 * Constructor
 */
Idzorek::Idzorek(){

}

/*!
 * Alpha
 * Constructs the matrix of alphas for each view
 * @param views. The combination of views concerning
 * @return Column-matrix of alphas used for coputation of omega.
 */
Matrix<double> Idzorek::alpha(){
    // Constructing alpha
    Matrix<double> alpha;
    for (auto i = views->views.begin(); i < views->views.end(); i ++){
        std::vector<double> alpha_row;
        alpha_row.push_back((1 - i->confidence)/i->confidence);
        alpha.add_row(alpha_row);
    }
    return alpha;

}

/*!
 * Omega
 * Computes the omega matrix with Idzorek's formula
 * Omega is a diagonal matrix with on the diagonal the variances of the views.
 * @param views. The views combination for which this matrix needs to be computed
 * @return Omega matrix.
 */
Matrix<double> Idzorek::omega(){
    Matrix<double> full_omega = views->P.mult(views->port->VCV() * tau).mult(views->P.t());
    for (unsigned i = 0; i < full_omega.get_rows(); i++){
        for(unsigned j = 0; j < full_omega.get_cols(); j++){
            full_omega(i, j) = alpha()(i, 0) * full_omega(i, j);
        }
    }

    return full_omega.diag();
}

/*
 * Name
 * returns the name of this class
 */
string Idzorek::name(){
     return "Idzorek";
}



