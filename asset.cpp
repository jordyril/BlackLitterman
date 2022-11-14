/**
    asset.cpp
    @author Jordy Rillaerts
    @version 1.0 18/03/18
*/

#include "asset.h"
#include <math.h>
#include <iomanip>
#include <numeric>
#include <fstream>

/*!
 * Constructor.
 */
Asset::Asset(){
}

/*!
 * Constructor.
 * Constructor given an adress automatically loads the TS from this adress, names it and saves the annualissation factor.
 * @param adress. The adress where the .txt file is saved on your pc.
 * @param asset_name. The name of the Asset.
 * @param annualisation_f. Factor used for annualisation of the returns.
 */
Asset::Asset(string asset_name, string adress, int annualisation_f){
    read_from_file(adress);
    annualisation_factor = annualisation_f;
    name = asset_name;
}

/*!
 * Mean
 * @param annualised. A boolean parameter asking if the mean return should be annualised or not, default = false
 * @return Mean return
 */
double Asset::mean(bool annualised){
    double sum = std::accumulate(values.begin(), values.end(), 0.0);
    if (annualised){
      return annualisation_factor * sum / length_series;
    }
    return sum / length_series;
}

/*!
 * Variance
 * 1/(n-1) * sum((x_i - mu)^2)
 * @param annualised. A boolean parameter asking if the variance should be annualised or not, default = false
 * @return Variance of the returns
 */
double Asset::variance(bool annualised){
    double sum_sq = 0.0;
    double mean_return = mean();
    for (unsigned i = 0; i < length_series; i++){
        sum_sq = sum_sq + pow((values[i] - mean_return), 2);
    }
    if (annualised){
        return annualisation_factor * sum_sq / (length_series - 1);
    }
    else {
        return sum_sq / (length_series - 1);
    }
}

/*!
 * Standard deviation
 * sqrt(Variance)
 * @param annualised. A boolean parameter asking if the variance should be annualised or not, default = false
 * @return STDV of the returns
 */
double Asset::stdv(bool annualised){
    double var = variance();
    if (annualised){
        return sqrt(var) * sqrt(annualisation_factor);
    }
    else{
        return sqrt(var);
    }
}

/*!
 * Sharpe ratio
 * Computes the sharp ratio if an asset: mean_return/volatility
 */
double Asset::sharpe_ratio(){
    return mean(true)/stdv(true);
}

/*!
 * Operator ==
 * Allows for comparisson between different Assets and if they are the same or not.
 * Assets will be considered the same if both their given name as the adress of the the data is the same.
 */
bool Asset::operator == (Asset rhs){
    if (this->name == rhs.name && this->adress == rhs.adress){
        return true;
    }
    else {
        return false;
    }
}


ostream& operator <<(ostream& os, Asset* obj){
    os << obj->name;
    return os;
}



