#ifndef IMPLIED_MV_RETURNS_H
#define IMPLIED_MV_RETURNS_H
# include "expectedreturns.h"


/*
 * Derived class: Base class = ExpectedReturns
 *
 * Implied returns are th returns based on the market weights and the
 * fact that market allocate resources in a mean-variance optimal way
 */

class ImpliedMVReturns: public ExpectedReturns{

public:
    string name();

    ImpliedMVReturns();

    Matrix<double> returns( );

    friend class ReportMaker;
};

#endif // IMPLIED_MV_RETURNS_H
