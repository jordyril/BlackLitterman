#include "omegacomputer.h"


/*
 * Constructor
 */
OmegaComputer::OmegaComputer(){
}

/*
 * Constructor
 */
OmegaComputer::OmegaComputer(double market_inneficiency){
    tau = market_inneficiency;

}

/*!
 * Setting the parameters
 * @param view_combo, comnbinations of views
 * @param Market_inefficiency
 */
void OmegaComputer::set_parameters(double market_inneficiency, ViewsCombiner* v_comb){
    tau = market_inneficiency;
    views = v_comb;
}

ostream& operator <<(ostream& os, OmegaComputer* obj){
    os << obj->name();
    return os;
}
