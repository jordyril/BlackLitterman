#ifndef VIEWSCOMBINER_H
#define VIEWSCOMBINER_H
#include "matrix.h"
#include "rview.h"
#include "aview.h"
#include "portfolio.h"


class ViewsCombiner{
protected:
    Portfolio* port;

    vector<View> views;

public:
    ViewsCombiner();
    ViewsCombiner(Portfolio* po);

    unsigned number_of_views;

    Matrix<double> confidence_matrix;
    Matrix<double> P;
    Matrix<double> Q;

    void add_view(View* new_view);
    void set_portfolio(Portfolio* po);

    friend class BlackLitterman;
    friend class ReportMaker;
    friend class Idzorek;
    friend class STDVdirectly;
    friend class PropVarPrior;
    friend class AverageReturns;
    friend class MeanVarianceOptimization;
    friend class ImpliedMVReturns;


};

#endif // VIEWSCOMBINER_H
