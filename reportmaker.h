#ifndef REPORTMAKER_H
#define REPORTMAKER_H
#include <iostream>
#include <fstream>
#include "meanvarianceoptimization.h"
#include "omegacomputer.h"
#include "expectedreturns.h"

/*
 * Base Class:
 *
 * Class is used for making reports of the MV optimization procedure
 */

using namespace std;

class ReportMaker{
public:
    ReportMaker();

    void asset_description(Asset* A);
    void write_asset_description(ofstream &file, Asset* A);

    void portfolio_description(Portfolio* P);
    void write_portfolio_description(ofstream &file, Portfolio* P);

    void MV_optimization_results_summary(MeanVarianceOptimization* process);
    void write_MV_optimization_results_summary(ofstream& out, MeanVarianceOptimization* process);

    void views_summary(ViewsCombiner* views);
    void write_views_summary(ofstream& out, ViewsCombiner* views);

    void make_report_single_process(string filename, MeanVarianceOptimization *process);



};

#endif // REPORTMAKER_H
