#ifndef AVIEW_H
#define AVIEW_H
#include "view.h"


/*
 * Derived class: Base Class = View
 * Views represent thoughts on future performances of assets
 * that are not captured by the market. This class allows to state these views
 * and use them in computations.
 */

class Aview: public View{
public:
    Aview();
    Aview(Asset* sub, double expect, double conf, double stdv = 0);

    string name();
};

#endif // AVIEW_H
