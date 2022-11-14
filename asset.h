#ifndef ASSET_H
#define ASSET_H
#include "timeseries.h"

/**
 * Derived Class (Base class = TimeSeries):
 * This Asset class allows the user to specifiy any particular asset in the form of a returns series.
 */

using namespace std;
class Asset: public TimeSeries{
private:
    int annualisation_factor; // factor to use in order to annualise returns (daily: 250/252, weekly: 52, monthly: 12, annually: 1)

    string name; // name of the asset

public:

    Asset();
    Asset(string asset_name, string adress, int annualisation_f);

    double mean(bool annualised = false);
    double variance(bool annualised = false);
    double stdv(bool annualised = false);
    double sharpe_ratio();

    bool operator == (Asset rhs);
    friend bool operator != (Asset lhs, Asset rhs) {if (lhs == rhs){return false;} else {return true;}};

    friend ostream& operator <<(ostream& os, Asset* obj);

    friend class Portfolio;
    friend class ViewsCombiner;
    friend class ReportMaker;

};

#endif // ASSET_H
