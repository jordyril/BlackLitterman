/**
    averagereturns.cpp
    @author Jordy Rillaerts
    @version 1.0 18/03/18
*/

#include "averagereturns.h"

/*!
 * Constructor
 */
AverageReturns::AverageReturns(){
}

/*!
 * Average returns
 * comutes the average past return in as expectations for future performance
 * @param P. portfolio with the necessary returns
 */
Matrix<double> AverageReturns::returns(){
    return views->port->mean_returns;
}

/*
 * Name
 * returns the name of this class
 */
string AverageReturns::name(){
     return "Average returns";
}




