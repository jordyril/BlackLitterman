#ifndef IDZOREK_H
#define IDZOREK_H
#include "omegacomputer.h"


/*
 * Derived class: Base class = OmegaComputation
 *
 * This class computes the Omega matrix required for the Black-Litterman model.
 * This method is based on a confidence arround a view,
 * specified by the investor
 * Omega = diag(alpha*P*(tau*VCV)*P')
 * alpha = (1 - confidence)/confidence
 */

class Idzorek: public OmegaComputer{

public:
    Idzorek(double market_inefficiency);
    Idzorek();

    string name();

    Matrix<double> alpha();
    Matrix<double> omega();

    friend class ReportMaker;
};

#endif // IDZOREK_H
