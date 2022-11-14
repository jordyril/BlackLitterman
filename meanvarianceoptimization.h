#ifndef MEANVARIANCEOPTIMIZATION_H
#define MEANVARIANCEOPTIMIZATION_H
#include "expectedreturns.h"
#include "matrix.h"

/*
 * Base Class:
 * Allows for the performance of a mean-variance optimization on portfolios.
 * Mean variance means maximizing: weights * ER - gamma/2 * weights.t * VCV * weights
 * Hence the optimal weights are:
 * weights_optimal = 1 / gamma * ER * VCV^-1
 */

class MeanVarianceOptimization{

protected:
    double expected_return();
    double expected_variance();
    double expected_volatility();
    double sharpe_ratio();
    double riskfree();

    Matrix<double> optimal_weights();

    ExpectedReturns* er;

    Portfolio* portfolio;

    double PRA;

public:

    double portfolio_return;
    double portfolio_variance;
    double portfolio_volatility;
    double portfolio_sharpe_ratio;
    double riskfree_weight;

    MeanVarianceOptimization();
    ~MeanVarianceOptimization();

    void optimise(ExpectedReturns *ER, double personal_risk_aversion);

    Matrix<double> optimized_weights;

    friend class ReportMaker;
};

#endif // MEANVARIANCEOPTIMIZATION_H
