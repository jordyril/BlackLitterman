#ifndef AVERAGERETURNS_H
#define AVERAGERETURNS_H
#include "expectedreturns.h"

/*
 * Derived class: Base class = ExpectedReturns
 *
 * Average returns, uses the historic average as prediction for the expected returns
 */

class AverageReturns: public ExpectedReturns{
public:
    AverageReturns();

    string name();

    Matrix<double> returns( );

    friend class ReportMaker;
};

#endif // AVERAGERETURNS_H
