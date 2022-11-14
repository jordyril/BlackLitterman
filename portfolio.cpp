/**
    portfolio.cpp
    @author Jordy Rillaerts
    @version 1.0 18/03/18
*/

#include "portfolio.h"
#include <math.h>
#include <fstream>

using namespace std;

/*!
 * Constructor.
 * Constructs a basic portfolio of 0 assets.
 */
Portfolio::Portfolio(string portfolio_name){
    number_of_assets = 0;
    name = portfolio_name;
}

/*!
 * Constructor.
 * Constructs a portfolio with the given matrix of assets and their weights.
 * @param asset_matrix. Matrix of assets for the portfolio
 * @param weight_matrix the initial balance of weights in the proposed portfolio
 */
Portfolio::Portfolio(string portfolio_name, Matrix<Asset> asset_matrix, Matrix<double> weight_matrix){
    assets = asset_matrix;
    initial_weights = weight_matrix;
    number_of_assets = asset_matrix.get_rows();
    name = portfolio_name;

}

/*!
 * Add Asset.
 * Adds a single asset to the portfolio.
 * @param new_asset. the new asset that needs to be added.
 * @param w. the initial weight of that asset in the portfolio. default = 0.
 */
void Portfolio::add_asset(Asset new_asset, double w){

    vector<Asset> new_row;
    new_row.push_back(new_asset);
    assets.add_row(new_row);

    vector<double> new_row2;
    new_row2.push_back(w);
    initial_weights.add_row(new_row2);

    vector<double> new_row3;
    new_row3.push_back(new_asset.mean(true));
    mean_returns.add_row(new_row3);

    number_of_assets++;
}

/*!
 * Anualized volatilities.
 * Computes the annualized volatilities of the returns for all assets in the portfolio.
 * @returns row-matrix of all the annualized volatilities
 */
Matrix<double> Portfolio::annualized_volatilities(){
    Matrix<double> a_v;
    vector<double> new_vol;
    for (unsigned i =0; i < number_of_assets; i++){
        double vol = assets(i, 0).stdv() * sqrt( assets(i, 0).annualisation_factor );
        new_vol.push_back(vol);
    }

    a_v.add_row(new_vol);

    return a_v;
}

/*!
 * Correlation.
 * Computes the correlation between all Asset-pair and constructs the correlation matrix
 * correlation between is assets is computed as: 1/(n-1) * sum[(x_i - mu_x) * (y_i - mu_y)] / (stdv_x * stdv_y)
 * @returns square correlation matrix.
 */
Matrix<double> Portfolio::correlation(){
    Matrix<double> cor_matrix;

    for (unsigned i = 0; i < number_of_assets; i++){
        vector < double > temp;

        for (unsigned j = 0; j < number_of_assets; j++){
            double correlation;
            double sum = 0;

            for (unsigned k = 0; k < assets(i, 0).length_series; k++){
                sum += (assets(i, 0).values[k] - assets(i,0).mean()) * (assets(j, 0).values[k] - assets(j,0).mean());
            }

            correlation = sum / (assets(i,0).length_series - 1) * 1 / (assets(i,0).stdv() * assets(j,0).stdv());
            temp.push_back(correlation);
        }

        cor_matrix.add_row(temp);
    }

    return cor_matrix;
}

/*!
 * VCV
 * Constructs the Variance-Covariance matrix for all Assets in the portfolio.
 * Variance/covariance is computed as follows: 1/(n-1) * sum[(x_i - mu_x) * (y_i - mu_y)]
 * @param annualised. Boolean if the VCV should be in annualised terms. Default = true.
 * @returns VCV matrix
 */
Matrix<double> Portfolio::VCV(bool annualised){
    Matrix<double> VCV_matrix;

    for (unsigned i = 0; i < number_of_assets; i++){
        vector < double > temp;

        for (unsigned j = 0; j < number_of_assets; j++){
            double vcv;
            double sum = 0;

            for (unsigned k = 0; k < assets(i,0).length_series; k++){
                sum += (assets(i, 0).values[k] - assets(i,0).mean()) * (assets(j, 0).values[k] - assets(j,0).mean());
            }

            if (annualised){
                vcv = sqrt(assets(i,0).annualisation_factor) * sqrt(assets(j,0).annualisation_factor) * sum / (assets(i,0).length_series - 1);

            }

            else {
                vcv = sum / (assets(i,0).length_series - 1);
            }

            temp.push_back(vcv);
        }

        VCV_matrix.add_row(temp);
    }

    return VCV_matrix;
}

/*!
 * Portfolio mean return.
 * Based on past performance of the individual assets and the weight given in th portfolio.
 * The expected/mean performance of the portfolio can be computed: sum[weight_i * ER_i]
 * @param annualised. Boolean if the mean return should be in annualised terms. Default = true.
 * @returns mean expected return of the portfolio as a whole
 */
double Portfolio::portfolio_mean_return(bool annualised){
    Matrix<double> total_return;
    if (annualised){
        total_return = mean_returns.t().mult(initial_weights);
    }

    else {
        total_return = mean_returns.t().mult(initial_weights);
        total_return = total_return * (1 / assets(0, 0).annualisation_factor);
    }

    return total_return(0,0);
}

/*!
 * Portfolio  variance.
 * Based on past performance of the individual assets and the weight given in th portfolio.
 * The portfolio variance can be computed: weights.t x VCV x weights
 * @param annualised (default = true). Boolean if the mean return should be in annualised terms.
 * @returns variance of the portfolio as a whole
 */
double Portfolio::portfolio_variance(bool annualised){
    Matrix<double> w_VCV_w;
    Matrix<double> w_VCV;

    w_VCV = initial_weights.t().mult(VCV(annualised));
    w_VCV_w = w_VCV.mult(initial_weights);

    return w_VCV_w(0,0);
}

/*!
 * Portfolio  volatility.
 * Based on past performance of the individual assets and the weight given in th portfolio.
 * The portfolio volatility can be computed: weights.t x VCV x weights
 * @param annualised (default = true). Boolean if the mean return should be in annualised terms.
 * @returns volatility of the portfolio as a whole
 */
double Portfolio::portfolio_volatility(bool annualised){
   return sqrt(portfolio_variance(annualised));
}

/*!
 * Portfolio  Sharpe ratio.
 * Expected return / volatility
 * @param annualised (default = true). Boolean if the mean return should be in annualised terms.
 * @returns sharpe ratio of the portfolio as a whole
 */
double Portfolio::portfolio_sharpe_ratio(bool annualised){
    return portfolio_mean_return(annualised) / portfolio_volatility(annualised);
}

/*!
 * Operator ==
 * Checking equality between two portfolios.
 * @returns boolean: true if equal, false if unequal
 */
bool Portfolio::operator ==(Portfolio rhs){
    bool result = true;
    unsigned i = 0;
    if (this->number_of_assets == rhs.number_of_assets){
        while (result == true && i < this->number_of_assets){
            (this->assets(i, 0) == rhs.assets(i, 0)) ? result = true : result = false;
            (this->initial_weights(i, 0) == rhs.initial_weights(i, 0)) ? result = true : result == false;
            i++;
        }

    }
    else{
        result = false;
    }
    return result;
}


