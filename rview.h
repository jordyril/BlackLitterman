#ifndef RVIEW_H
#define RVIEW_H
#include "view.h"


/*
 * Derived class: Base Class = View
 * Views represent thoughts on future performances of assets
 * that are not captured by the market. This class allows to state these views
 * and use them in computations.
 */

class Rview: public View{


public:
    Rview();
    Rview(Asset* sub, Asset* rel, double expect, double conf, double stdv = 0);

    string name();


};

#endif // RVIEW_H
