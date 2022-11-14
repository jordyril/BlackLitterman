/**
    reportmaker.cpp
    @author Jordy Rillaerts
    @version 1.0 19/03/18
*/

#include "reportmaker.h"
#include "functions.h"
#include <iomanip>
#include <ctime>
#include <chrono>
#include <iostream>

/*!
 * Constructor
 */
ReportMaker::ReportMaker(){

}


/*!
 * Asset description
 * Print description of the asset
 * @param A; Asset
 */
void ReportMaker::asset_description(Asset *A){
        cout << A->name << ": " << endl;
        cout << setprecision(3) << "Mean return = " << 100 * A->mean(true) << "%" << endl;
        cout << setprecision(3) << "Variance = " << 100 * A->variance(true) << "%^2"<< endl;
        cout << setprecision(3) << "STDV = " << 100 * A->stdv(true) << "%" << endl;
        cout << setprecision(3) << "Sharpe ratio = " << A->sharpe_ratio() << endl;

}

/*!
 * Asset description
 * write description of the asset to an ofstream
 * @param A; Asset
 * @param file; ofstream
 */
void ReportMaker::write_asset_description(ofstream &file, Asset *A){
        file << A->name << ": " << endl;
        file << setprecision(3) << "Mean return = " << 100 * A->mean(true) << "%" << endl;
        file << setprecision(3) << "Variance = " << 100 * A->variance(true) << "%^2"<< endl;
        file << setprecision(3) << "STDV = " << 100 * A->stdv(true) << "%" << endl;
        file << setprecision(3) << "Sharpe ratio = " << A->sharpe_ratio() << endl;

}

/*!
 * Portfolio descrption
 * Print a description of a portfolio on the console
 * @param P. pointer to a portfolio
 */
void ReportMaker::portfolio_description(Portfolio *P){
    // intro
    cout << "PORTFOLIO DESCRIPTION - (All data are annualised data):" << endl << endl;

    // General overview of content
    cout << "The portfolio " << P->name << " contains the following " << P->number_of_assets
         << " assets: " << endl << "(weight in the portfolio) " << endl;
    for (unsigned i = 0; i < P->number_of_assets; i++ ){
        cout << i + 1 <<". " << P->assets(i, 0).name << " (" << P->initial_weights(i,0) * 100 << "%)" << endl;
    }
    cout << endl;
    auto func = [] (int x) -> string {
        switch (x){
        case 1:
            return "Annual";

        case 12:
            return "Monthly";

        case 250:
        case 252:
            return "Daily";

        case 52:
            return "Weekly";

        default:
            return "Periodical";
        }

    };
    cout << "The returns series consist of " << func(P->assets(0,0).annualisation_factor)
         << " data, with a total of " << P->assets(0,0).length_series << " observations per Asset." << endl;

    // Portfolio performance
    cout << "Based on the initially given weights and past performance of the individual assets:" << endl;
    cout << setprecision(3) << "-> The portfolio past average return = " << P->portfolio_mean_return(true)*100 << "%;" << endl;
    cout << setprecision(3) << "-> The portfolio volatility = " << P->portfolio_volatility(true)*100 << "%;" << endl;
    cout << endl;

    // Correlation
    cout << "The correlation between assets is represented with the correlation matrix:" << endl;
    for (unsigned i = 1; i < P->number_of_assets + 1; i++){
        cout << setw(5) << right << i << ". ";
    }
    cout << endl;
    P->correlation().print(6, 4);
    cout << endl;

    // More details

    cout << "Going deeper into the individual assets:" << endl;
    for (unsigned i = 0; i < P->number_of_assets; i ++){
        asset_description(&P->assets(i, 0));
        cout << endl;

    }
}

/*!
 * Portfolio descirption
 * Print a description of a portfolio on the console
 * @param P. pointer to a portfolio
 */
void ReportMaker::write_portfolio_description(ofstream& file, Portfolio* P){
    // intro
    file << "PORTFOLIO DESCRIPTION - (All data are annualised data):" << endl;
    file.fill('=');
    file << setw(60) << " " << endl;
    file.fill(' ');

    // General overview of content
    file << "The portfolio " << P->name << " contains the following "
         << P->number_of_assets << " assets :" << endl << "(weight in the portfolio): " << endl;
    for (unsigned i = 0; i < P->number_of_assets; i++ ){
        file << i + 1 <<". " << P->assets(i, 0).name << " (" << P->initial_weights(i,0) * 100 << "%)" << endl;
    }
    file << endl;

    auto func = [] (int x) -> string {
        switch (x){
        case 1:
            return "Annual";

        case 12:
            return "Monthly";

        case 250:
        case 252:
            return "Daily";

        case 52:
            return "Weekly";

        default:
            return "Periodical";
        }

    };

    file << "The returns series consist of " << func(P->assets(0,0).annualisation_factor)
         << " data, with a total of " << P->assets(0,0).length_series << " observations per Asset." << endl;

    // Portfolio performance
    file << "Based on the initially given weights and past performance of the individual assets:" << endl;
    file << setprecision(3) << "-> The portfolio past average return = " << P->portfolio_mean_return(true)*100 << "%;" << endl;
    file << setprecision(3) << "-> The portfolio volatility = " << P->portfolio_volatility(true)*100 << "%;" << endl;
    file << setprecision(3) << "-> The portfolio Sharpe Ratio = " << P->portfolio_mean_return() / P->portfolio_volatility() << endl;
    file << endl;

    // Correlation
    file << "The correlation between assets is represented with the correlation matrix:" << endl;
    for (unsigned i = 1; i < P->number_of_assets + 1; i++){
        file << setw(5) << right << i << ". ";
    }
    file << endl;
    write_matrix_to_file(file, P->correlation(), 6, 4);
    file << endl;

    // More details about portfolio
    file << "Going deeper into the individual assets:" << endl;
    for (unsigned i = 0; i < P->number_of_assets; i ++){
        write_asset_description(file, &P->assets(i,0));
        file << endl;

    }
}

/*!
 * Summary of optimization results
 * @param process; the optimizing process and all its parameters
 */
void ReportMaker::MV_optimization_results_summary(MeanVarianceOptimization *process){

    cout << "OPTIMIZATION SUMMARY" << endl;
    cout.fill('=');
    cout << setw(60) << " " << endl;
    cout.fill(' ');

    cout << "The optimal weighting of the Assets in this portfolio is " << endl
         << "based on a Mean-Variance optimal solution." << endl;
    cout << process->er->name() << " are used as input for the model." << endl;
    if (process->er->omega_method != NULL){
        cout << process->er->omega_method->name() << " is used for computing the variance arround the views." << endl << endl;
    }
    else{
        cout << endl << endl;
    }
    cout << "The optimal weights are:" << endl;
    for (unsigned i = 0; i < process->portfolio->number_of_assets; i++){
        cout << left << "\t" << setw(10) <<  process->portfolio->assets(i, 0).name << ": "
             << fixed << setw(8) << right << setprecision(2)
             <<  process->optimized_weights(i, 0) * 100 << "%" << endl;
    }
    cout << "\t" << setw(10) << setprecision(2) << left << "Riskfree" << ": "
         << right << setw(8) << process->riskfree_weight * 100 << "%" << endl << endl;

    cout << "The PERFORMANCE of the optimally balanced portfolio:" << endl;
    cout << "\t" << "-> Expected excess return: " << process->portfolio_return * 100 << "%" << endl
         << "\t" << "-> Expected volatility: " << process->portfolio_volatility * 100 << "%" << endl
         << "\t" << "-> Sharpe-ratio: " << process->portfolio_sharpe_ratio << endl;
    cout.fill('-');
    cout << setw(60) << " " << endl;
    cout.fill(' ');
}

/*!
 * Writing Summary of optimization results to ofstream
 * @param process; the optimizing process and all its parameters
 * @param
 */
void ReportMaker::write_MV_optimization_results_summary(ofstream & out, MeanVarianceOptimization *process){

    out << "OPTIMIZATION SUMMARY" << endl;
    out.fill('=');
    out << setw(60) << " " << endl;
    out.fill(' ');

    out << "The optimal weighting of the Assets in this portfolio is " << endl
         << "based on a Mean-Variance optimal solution." << endl;
    out << process->er->name() << " are used as input for the model." << endl;
    if (process->er->omega_method != NULL){
        out << process->er->omega_method->name() << " is used for computing the variance arround the views." << endl << endl;
    }
    else{
        out << endl << endl;
    }
    out << "The optimal weights are:" << endl;
    for (unsigned i = 0; i < process->portfolio->number_of_assets; i++){
        out << left << "\t" << setw(10) <<  process->portfolio->assets(i, 0).name << ": "
             << fixed << setw(8) << right << setprecision(2)
             <<  process->optimized_weights(i, 0) * 100 << "%" << endl;
    }
    out << "\t" << setw(10) << setprecision(2) << left << "Riskfree" << ": "
         << right << setw(8) << process->riskfree_weight * 100 << "%" << endl << endl;

    out << "The PERFORMANCE of the optimally balanced portfolio:" << endl;
    out << "\t" << "-> Expected excess return: " << process->portfolio_return * 100 << "%" << endl
         << "\t" << "-> Expected volatility: " << process->portfolio_volatility * 100 << "%" << endl
         << setprecision(4) << "\t" << "-> Sharpe-ratio: " << process->portfolio_sharpe_ratio << endl;
    out.fill('-');
    out << setw(60) << " " << endl;
    out.fill(' ');
}

/*!
 * Summary of views
 * @param views; The views on certain assets of a portfolio
 */
void ReportMaker::views_summary(ViewsCombiner *views){
    cout << "SUMMARY OF THE VIEWS" << endl;
    cout.fill('=');
    cout << setw(60) << " " << endl;
    cout.fill(' ');
    for (unsigned i = 0; i < views->number_of_views; i++){
        cout << "View " << i + 1 << ":" << endl;
        if (views->views[i].relative == NULL){
            cout << "\t" << views->views[i].subject->name << " will have an excess return of "
                 << views->views[i].expectation * 100 << "%." << endl;
            cout << "\t" << "\t" << "-> Standard error surrounding this view, based on expert opinion: "
                 << views->views[i].standard_error * 100 << "%." << endl;
            cout << "\t" << "\t" << "-> Confidence surrounding this view: "
                 << views->views[i].confidence * 100 << "%." << endl;
        }
        else {
            if (views->views[i].expectation < 0){
                cout << "\t" << views->views[i].relative->name << " will OUTPERFORM "
                     << views->views[i].subject->name << " with "
                     << views->views[i].expectation * 100 << "%." << endl;
            }
            else {
                if (views->views[i].expectation > 0){
                    cout << "\t" << views->views[i].subject->name << " will OUTPERFORM "
                         << views->views[i].relative->name << " with "
                         << views->views[i].expectation * 100 << "%." << endl;
                }
                else{
                    cout << "\t" << views->views[i].subject->name << " will perform the same as "
                         << views->views[i].relative->name << endl;
                }
            }
            cout << "\t" << "\t" << "-> Standard error surrounding this view, based on expert opinion: "
                 << views->views[i].standard_error * 100 << "%." << endl;
            cout << "\t" << "\t" << "-> Confidence surrounding this view: "
                 << views->views[i].confidence * 100 << "%." << endl;
        }
    }
    cout.fill('-');
    cout << setw(60) << " " << endl;
    cout.fill(' ');
}

/*!
 * Writing Summary of views to ofstream
 * @param views; The views on certain assets of a portfolio
 * @param out; Ofstream
 */
void ReportMaker::write_views_summary(ofstream &out, ViewsCombiner *views){
    out << "SUMMARY OF THE VIEWS" << endl;
    out.fill('=');
    out << setw(60) << " " << endl;
    out.fill(' ');
    for (unsigned i = 0; i < views->number_of_views; i++){
        out << "View " << i + 1 << ":" << endl;
        if (views->views[i].relative == NULL){
            out << "\t" << views->views[i].subject->name << " will have an excess return of "
                << views->views[i].expectation * 100 << "%." << endl;
            out << "\t" << "\t" << "-> Standard error surrounding this view, based on expert opinion: "
                << views->views[i].standard_error * 100 << "%." << endl;
            out << "\t" << "\t" << "-> Confidence surrounding this view: "
                << views->views[i].confidence * 100 << "%." << endl;
        }
        else {
            if (views->views[i].expectation < 0){
                out << "\t" << views->views[i].relative->name << " will OUTPERFORM "
                    << views->views[i].subject->name << " with "
                    << views->views[i].expectation * 100 << "%." << endl;
            }
            else {
                if (views->views[i].expectation > 0){
                    out << "\t" << views->views[i].subject->name << " will OUTPERFORM "
                        << views->views[i].relative->name << " with "
                        << views->views[i].expectation * 100 << "%." << endl;
                }
                else{
                    out << "\t" << views->views[i].subject->name << " will perform the same as "
                        << views->views[i].relative->name << endl;
                }
            }
            out << "\t" << "\t" << "-> Standard error surrounding this view, based on expert opinion: "
                << views->views[i].standard_error * 100 << "%." << endl;
            out << "\t" << "\t" << "-> Confidence surrounding this view: "
                << views->views[i].confidence * 100 << "%." << endl;
        }
    }
    out.fill('-');
    out << setw(60) << " " << endl;
    out.fill(' ');
}

/*!
 * Make report of single process
 * Actual making of a report file in .txt. This report will only report the result of 1 single method
 * @param filename. Name of the report-file
 * @param process. the computational class of a MV optimization process and its parameters
 */
void ReportMaker::make_report_single_process(string filename, MeanVarianceOptimization* process){
    // opening a file to write in
    ofstream file;
    file.open(filename);

    //time of computation
    time_t tt = chrono::system_clock::to_time_t (chrono::system_clock::now());
    struct tm * ptm = localtime(&tt);

    // Title
    file << "MEAN-VARIANCE OPTIMISATION" << " - report made: " << put_time(ptm, "%c") << endl;
    file.fill('=');
    file << setw(60) << " " << endl;
    file.fill(' ');

    // Parameters of the optimization
    file << "EXECUTIVE SUMMARY" << endl;
    file.fill('=');
    file << setw(60) << " " << endl;
    file.fill(' ');



    file << "Parameters of optimisation proces: " << endl;

    file << "\t" << "-> Returns used: " << process->er->name() << endl; // returns used
    if (process->er->omega_method != NULL){
        file << "\t" << "\t" << ">> Method for computing Omega = "  << process->er->omega_method->name() << endl;
    }

    file << "\t" << "-> Assumed Market risk aversion: " << process->er->gamma << endl; // MRA
    file << "\t" << "-> Assumed Personal risk aversion: " << process->PRA << endl; // PRA
    if (process->er->omega_method != NULL){
        file << "\t" << "-> Assumed Market inefficiency: " << process->er->omega_method->tau * 100 << "%" <<  endl; // tau
    }

    file << "\t" << "-> Portfolio under consideration: " << process->portfolio->name << endl;
    if (process->er->omega_method != NULL){
        file << "\t" << "-> Number of views: " << process->er->views->number_of_views << endl;
    }
    file.fill('-');
    file << setw(60) << " " << endl;
    file.fill(' ');


    //Portfolio details
    write_portfolio_description(file, process->portfolio);
    file.fill('-');
    file << setw(60) << " " << endl;
    file.fill(' ');

    // Views details
    if (process->er->omega_method != NULL){
        write_views_summary(file, process->er->views);
    }


    // Optimisation summary
    write_MV_optimization_results_summary(file, process);

    file.fill('=');
    file << setw(60) << " " << endl;
    file.fill(' ');

    file.close();
}
