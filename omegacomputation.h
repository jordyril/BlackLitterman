#ifndef OMEGACOMPUTATION_H
#define OMEGACOMPUTATION_H
#include "matrix.h"
#include "viewscombiner.h"


/* Base Class:
 * The Omega matrix is the uncertainty/variance arround the views.
 * Different methods exist to compute this matrix.
 * The variance arround the views is inversily related to the
 * investors confidence in these views.
 */


class OmegaComputation{
public:

    double tau;

    OmegaComputation();

    void set_parameters(double market_inneficiency);

    virtual Matrix<double> omega(ViewsCombiner* views)=0;

    virtual string name() = 0;

    friend class ReportMaker;

};

#endif // OMEGACOMPUTATION_H
