#include "meanvarianceoptimization.h"

/*
 * Constructor
 */
MeanVarianceOptimization::MeanVarianceOptimization(){

}

/*!
 * Setting the parameters
 * Makes sure all data within the class is reset before being used again and sets the parameters for the new optimization problem
 * @param P. Portfolio to be optimised
 * @param er. Expected returns used for optimization
 * @param risk aversion. Personal risk aversion of the investor = gamma
 */
void MeanVarianceOptimization::optimise(ExpectedReturns* ER, double personal_risk_aversion){
    optimized_weights.clear();
    portfolio = ER->views->port;
    er = ER;
    PRA = personal_risk_aversion;

    // doing all computations
    optimized_weights =  optimal_weights();
    portfolio_return = expected_return();
    portfolio_variance = expected_variance();
    portfolio_volatility = expected_volatility();
    portfolio_sharpe_ratio = sharpe_ratio();
    riskfree_weight = riskfree();
}

/*!
 * MV optimal weights
 * computes the MV optimal weights, without constraints based on weights_optimal = 1 / gamma * ER * VCV^-1
 * @param percentages. Boolen argument that makes it possible to put weights in percentages
 * @returns matrix of optimal weights for the portfolio in the same order as the assets in the portfolio
 */
Matrix<double> MeanVarianceOptimization::optimal_weights(){
    return portfolio->VCV().inverse().mult(er->returns()) * (1 / PRA);
}

/*!
 * MV optimal expected return
 * computes the expected return of the optimizd portfolio based on the MV optimal weights, w_optimal * ER
 * @param percentages. Boolen argument that makes it possible to put weights in percentages
 * @returns matrix of optimal weights for the portfolio in the same order as the assets in the portfolio
 */
double MeanVarianceOptimization::expected_return(){
    Matrix<double> port_return = optimized_weights.t().mult(er->returns());
    return port_return(0,0);


}

/*!
 * MV optimal expected variance
 * computes the expected variance of the optimizd portfolio based on the MV optimal weights, w_optimal * VCV * w_optimal
 * @param percentages. Boolen argument that makes it possible to put weights in percentages
 * @returns matrix of optimal weights for the portfolio in the same order as the assets in the portfolio
 */
double MeanVarianceOptimization::expected_variance(){
    Matrix<double> variance = optimized_weights.t().mult(portfolio->VCV().mult(optimized_weights));
    return variance(0,0);
}

/*!
 * MV optimal expected volatility
 * computes the expected volatility of the optimizd portfolio based on the MV optimal weights, w_optimal * ER
 * @param percentages. Boolen argument that makes it possible to put weights in percentages
 * @returns volatility of the portfolio
 */
double MeanVarianceOptimization::expected_volatility(){
    return sqrt(expected_variance());
}

/*!
 * MV (optimal) sharpe ratio
 * computes the sharpe ratio of the optimized portfolio based on the MV optimal weights, return/volatility
 * @returns sharp ratio of the portfolio
 */
double MeanVarianceOptimization::sharpe_ratio(){
    return expected_return()/expected_volatility();

}

/*!
 * Riskfree rate
 * computes the weight invested/borrowed in the riskfree rate, portfolio should have total weight of 100%, riskfree is used to make this happen
 * @returns weight
 */
double MeanVarianceOptimization::riskfree(){
    return 1 - optimized_weights.sum();

}





