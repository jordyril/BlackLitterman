/**
    blacklitterman.cpp
    @author Jordy Rillaerts
    @version 1.0 18/03/18
*/


#include "blacklitterman.h"

/*!
 * Constructor
 */
BlackLitterman::BlackLitterman(){
}


/*!
 * Black Litterman returns
 * Computes the expected returns as a combination of views and implied market MV returns
 * @param Port. Portfolio on which views aplly and for which returns should be computed for further optimization
 */
Matrix<double> BlackLitterman::returns(){
    Matrix<double> returns;

    // v_1 = [VCV^-1 + (P'* Omega^-1 * P * tau]^-1 * VCV^-1

    Matrix<double> v_1;
    v_1 = ((views->port->VCV().inverse() + (omega_method->views->P.t().mult(omega_method->omega().inverse().mult(omega_method->views->P))) *
            omega_method->tau).inverse()).mult(views->port->VCV().inverse());

    // v_2 = [VCV^-1 + (P'* Omega^-1 * P * tau]^-1 * [tau * P' * Omega^-1]

    Matrix<double> v_2;
    v_2 = ((views->port->VCV().inverse() + (omega_method->views->P.t().mult(omega_method->omega().inverse().mult(omega_method->views->P))) *
            omega_method->tau).inverse()).mult((omega_method->views->P.t() * omega_method->tau).mult(omega_method->omega().inverse()));

    // BL-returns = v_1 * R_eq + v_2 * Q
    ImpliedMVReturns implied_returns; // R_eq are the implied MV returns
    implied_returns.set_parameters(views, gamma);

    returns = v_1.mult(implied_returns.returns()) + v_2.mult(omega_method->views->Q);

    return returns;

}

/*
 * Name
 * returns the name of this class
 */
string BlackLitterman::name(){
     return "Black-Litterman returns";
}
