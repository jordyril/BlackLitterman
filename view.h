#ifndef VIEW_H
#define VIEW_H
#include "asset.h"

/*
 * Base Class:
 * Views represent thoughts on future performances of assets
 * that are not captured by the market. This class allows to state these views
 * and use them in computations.
 */

class View{
public:
    View();

    Asset* subject; // Main subject of the view
    Asset* relative; // If relative view

    virtual string name();

    double expectation; // expectation of (over/under)performance
    double standard_error; // STVD surrounding expectation
    double confidence; // Confidence in the view

    friend ostream& operator<< (ostream& os, View* obj);



    friend class ReportMaker;
};

#endif // VIEW_H
