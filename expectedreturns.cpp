/**
    expectedreturns.cpp
    @author Jordy Rillaerts
    @version 1.0 18/03/18
*/
#include "expectedreturns.h"

/*
 * Constructor
 */

ExpectedReturns::ExpectedReturns(){

}

void ExpectedReturns::set_parameters(ViewsCombiner* view_comb, double MRA, OmegaComputer* method){
    views = view_comb;

    omega_method = method;

    gamma = MRA;

    if (method != NULL){
        omega_method->views = view_comb;
    }

}

ostream& operator <<(ostream& os, ExpectedReturns* obj){
    os << obj->name();
    return os;
}
