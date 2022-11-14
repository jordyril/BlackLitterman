#ifndef OMEGACOMPUTER_H
#define OMEGACOMPUTER_H
#include <viewscombiner.h>

/* Base Class:
 * The Omega matrix is the uncertainty/variance arround the views.
 * Different methods exist to compute this matrix.
 * The variance arround the views is inversily related to the
 * investors confidence in these views.
 */

class OmegaComputer{
protected:
    ViewsCombiner* views;

    double tau;

public:
    OmegaComputer(double market_inneficiency);
    OmegaComputer();

    void set_parameters(double market_inneficiency, ViewsCombiner* v_comb);

    virtual Matrix<double> omega() = 0;

    virtual string name() = 0;

    friend ostream& operator<< (ostream& os, OmegaComputer* obj);


    friend class ReportMaker;
    friend class BlackLitterman;
    friend class ExpectedReturns;
};

#endif // OMEGACOMPUTER_H
