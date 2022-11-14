#include "omegacomputation.h"

/*
 * Constructor
 */
OmegaComputation::OmegaComputation(){

}

/*!
 * Setting the parameters
 * @param view_combo, comnbinations of views
 * @param Market_inefficiency
 */
void OmegaComputation::set_parameters(double market_inneficiency){
    tau = market_inneficiency;
    //views = view_comb;
}

