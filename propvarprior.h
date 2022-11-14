#ifndef PROPVARPRIOR_H
#define PROPVARPRIOR_H
#include "omegacomputer.h"

/*
 * Derived class: Base Class = OmegaComputation
 *
 * This class computes the Omega matrix required for the Black-Litterman model.
 * Variance of the views is proportional to the variance of the asset returns.
 * Omega = diag(P(tau*VCV)P')
 * tau = mostly between 5%-15% (according to research) and is a representation
 * for the market inefficiency.
 */


class PropVarPrior: public OmegaComputer{
public:
    PropVarPrior(double market_inefficiency);
    PropVarPrior();

    string name();

    Matrix<double> omega();

    friend class ReportMaker;
};

#endif // PROPVARPRIOR_H
