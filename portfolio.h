#ifndef PORTFOLIO_H
#define PORTFOLIO_H
#include "asset.h"
#include <vector>
#include "matrix.cpp"

/**
 * Base class:
 * This Portfolio class allows the user to specifiy different portfolios, consisiting of any Assets
 */

class Portfolio{

public:
    string name;

    Portfolio(string portfolio_name);
    Portfolio(string portfolio_name, Matrix<Asset> asset_matrix, Matrix<double> weight_matrix);

    Matrix<Asset> assets; // column-matrix of all the assets in the portfolio

    unsigned number_of_assets; // The amount of assets in the portfolio

    Matrix<double> initial_weights; // column-matrix of the weights belonging to these assets (in the same order) in the portfolio
    Matrix<double> mean_returns; // column-matrix of all the assets mean returns (same order)

    Matrix<double> annualized_volatilities();
    Matrix<double> correlation();
    Matrix<double> VCV(bool annualised = true);

    double portfolio_mean_return(bool annualised = true);
    double portfolio_variance(bool annualised = true);
    double portfolio_volatility(bool annualised = true);
    double portfolio_sharpe_ratio(bool annualised = true);

    bool operator == (Portfolio rhs);
    friend bool operator != (Portfolio lhs, Portfolio rhs) {if (lhs == rhs){return false;} else {return true;}};

    void add_asset(Asset new_asset, double w = 0);

    friend class ReportMaker;

};

#endif // PORTFOLIO_H
