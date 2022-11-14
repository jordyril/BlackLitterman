/**
    impliedMVreturns.cpp
    @author Jordy Rillaerts
    @version 1.0 18/03/18
*/
#include "impliedMVreturns.h"

/*
 * Constructor
 */
ImpliedMVReturns::ImpliedMVReturns(){

}

/*!
 * Implied MV returns
 * Computes the returns based on the reverse engineeering of MV optimal solution
 * ER = gamma * VCV * weigths
 * @param P. Portfolio
 */
Matrix<double> ImpliedMVReturns::returns(){
    return  views->port->VCV().mult(views->port->initial_weights) * gamma;
}

/*
 * Name
 * returns the name of this class
 */
string ImpliedMVReturns::name(){
     return "Implied MV returns";
}


