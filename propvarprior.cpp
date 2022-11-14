/**
    propvarprior.cpp
    @author Jordy Rillaerts
    @version 1.0 18/03/18
*/

#include "propvarprior.h"

/*!
 * Constructor
 */

PropVarPrior::PropVarPrior(double market_inefficiency){
    tau = market_inefficiency;

}

/*!
 * Constructor
 */

PropVarPrior::PropVarPrior(){

}


/*!
 * Omega
 * Computes the omega matrix with taking into account the variance of the assets whom
 * are subjects to these views.
 * Omega is a diagonal matrix with on the diagonal the variances of the views.
 * @param views. The views combination for which this matrix needs to be computed
 * @return Omega matrix.
 */
Matrix<double> PropVarPrior::omega(){
    //Matrix<double> full_omega = views->P.mult(views->port->VCV() * tau).mult(views->P.t());
    Matrix<double> full_omega = views->P.mult(views->port->VCV() * tau).mult(views->P.t());
    return full_omega.diag();
}

/*
 * Name
 * returns the name of this class
 */
string PropVarPrior::name(){
     return "Proportionate to the variance of the prior";
}

