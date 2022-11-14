#ifndef STDVDIRECTLY_H
#define SE_DIRECTLY_H
#include "omegacomputer.h"

/*
 * Derived class: Base Class = OmegaComputation
 *
 * This class computes the Omega matrix required for the Black-Litterman model.
 * It does this by simply taking the variance (based on the self-chosen SE)
 *  and puts these variances on the diagonal of the omega-matrix
 */

class STDVdirectly : public OmegaComputer{

public:
    STDVdirectly(double market_inefficiency);
    STDVdirectly();

    string name();

    Matrix<double> omega();

    friend class ReportMaker;
};

#endif // STDVDIRECTLY_H
