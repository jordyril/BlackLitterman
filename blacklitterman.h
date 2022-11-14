#ifndef BLACKLITTERMAN_H
#define BLACKLITTERMAN_H
#include "expectedreturns.h"
#include "impliedMVreturns.h"
#include "viewscombiner.h"
#include "omegacomputer.h"
/*
 * Derived class: Base class = ExpectedReturns
 *
 * Black-Litterman model, is a model to get to expected returns,
 * making use of the views stated by the investors.
 * BL-returns imply a mixture between MV-equilibrium returns and the returns
 * from the views.
 * BL-returns = v_1 * R^eq + v_2 * Q
 * v_1 = [VCV^-1 + (P'* Omega^-1 * P * tau]^-1 * VCV^-1
 * v_2 = [VCV^-1 + (P'* Omega^-1 * P * tau]^-1 * [tau * P' * Omega^-1]
 */



class BlackLitterman : public ExpectedReturns{


public:
    string name();

    BlackLitterman();

    Matrix<double> returns( );
};

#endif // BLACKLITTERMAN_H
