#ifndef EXPECTEDRETURNS_H
#define EXPECTEDRETURNS_H
#include "portfolio.h"
#include "matrix.h"
#include "viewscombiner.h"
#include "omegacomputer.h"



/*
 * Base class:
 *
 * Mean-variance optimization relies on the expected returns we give as input
 * This class holds different subclasses on how to compute these input-returns
 */

class ExpectedReturns{
protected:
    ViewsCombiner* views;

    double gamma;

public:

    ExpectedReturns();

    OmegaComputer* omega_method;

    void set_parameters(ViewsCombiner* view_comb, double MRA, OmegaComputer* method = NULL);

    virtual string name() = 0;

    virtual Matrix<double> returns( ) = 0;

    friend ostream& operator <<(ostream& os, ExpectedReturns* obj);

    friend class MeanVarianceOptimization;
    friend class ReportMaker;

};


#endif // EXPECTEDRETURNS_H
