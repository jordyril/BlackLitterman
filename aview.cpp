/**
    aview.cpp
    @author Jordy Rillaerts
    @version 1.0 18/03/18
*/

#include "aview.h"

/*!
 * Constructor.
 * @param sub. The subject asset of the view.
 * @param expect. The expectation of performance of the subject asset.
 * @param conf. The confidence in the view.
 * @param stdv. The standard deviation arround the expectation.
 */
Aview::Aview(Asset* sub, double expect, double conf, double stdv){
    subject = sub;
    expectation = expect;
    confidence = conf;
    standard_error = stdv;
    relative = NULL;

}

/*
 * Constructor.
 */
Aview::Aview(){
    relative = NULL;

}

/*
 * Name
 * returns the name of this class
 */

string Aview::name(){
     return "Absolute view";
}
