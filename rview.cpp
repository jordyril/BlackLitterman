/**
    rview.cpp
    @author Jordy Rillaerts
    @version 1.0 18/03/18
*/
#include "rview.h"
/*
 * Constructor
 */
Rview::Rview(){

}

/*!
 * Constructor.
 * @param sub. The subject asset of the view.
 * @param rel. The related asset.
 * @param expect. The expectation of performance of the subject asset.
 * @param conf. The confidence in the view.
 * @param stdv. The standard deviation arround the expectation.
 */
Rview::Rview(Asset *sub, Asset *rel, double expect, double conf, double stdv){
    subject = sub;
    relative = rel;
    expectation = expect;
    confidence = conf;
    standard_error = stdv;

}

/*
 * Name
 * returns the name of this class
 */
string Rview::name(){
     return "Relative view";
}


