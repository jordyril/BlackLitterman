#include <iostream>
#include <fstream>
#include <vector>
#include "timeseries.h"
#include "asset.h"
#include "portfolio.h"
#include "rview.h"
#include "aview.h"
#include "impliedMVreturns.h"
#include "meanvarianceoptimization.h"
#include "averagereturns.h"
#include "viewscombiner.h"
#include "stdvdirectly.h"
#include "propvarprior.h"
#include "idzorek.h"
#include "blacklitterman.h"
#include "reportmaker.h"
#include "omegacomputer.h"
#include <string.h>
#include "questions.cpp"
#include <sstream>
#include "multiplechoice.cpp"



using namespace std;

struct Parameters{
    double MRA ;
    double PRA ;
    double tau ;
};

int main(){

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// HARDCODE VERSION ///
/*


    // STEP 1:
    // Reading loading the necessary return-series/time-series/assets into the program

    // Example of AEX index over-/underweighing: 9/11/2007 - 9/11/2017 (weekly data)
    Asset AEX("AEX", "C:\\Users\\jordy\\Dropbox\\Solvay\\Courses\\Advanced_Programming_C++\\Project\\Project\\Data\\AEX.txt", 52);
    Asset Philips("Philips", "C:\\Users\\jordy\\Dropbox\\Solvay\\Courses\\Advanced_Programming_C++\\Project\\Project\\Data\\Philips.txt", 52);
    Asset Unilever("Unilever", "C:\\Users\\jordy\\Dropbox\\Solvay\\Courses\\Advanced_Programming_C++\\Project\\Project\\Data\\Unilever.txt", 52);
    Asset Ahold("Ahold", "C:\\Users\\jordy\\Dropbox\\Solvay\\Courses\\Advanced_Programming_C++\\Project\\Project\\Data\\Ahold.txt", 52);
    Asset ING("ING", "C:\\Users\\jordy\\Dropbox\\Solvay\\Courses\\Advanced_Programming_C++\\Project\\Project\\Data\\ING.txt", 52);
    Asset Randstad("Randstad", "C:\\Users\\jordy\\Dropbox\\Solvay\\Courses\\Advanced_Programming_C++\\Project\\Project\\Data\\Randstad.txt", 52);

    // Example of countries:  3/02/06 - 28/01/2011 (weekly data)
    Asset Canada("Canada", "C:\\Users\\jordy\\Dropbox\\Solvay\\Courses\\Advanced_Programming_C++\\Project\\Project\\Data\\Canada.txt", 52);
    Asset Japan("Japan", "C:\\Users\\jordy\\Dropbox\\Solvay\\Courses\\Advanced_Programming_C++\\Project\\Project\\Data\\Japan.txt", 52);
    Asset Germany("Germany", "C:\\Users\\jordy\\Dropbox\\Solvay\\Courses\\Advanced_Programming_C++\\Project\\Project\\Data\\Germany.txt", 52);
    Asset US("US", "C:\\Users\\jordy\\Dropbox\\Solvay\\Courses\\Advanced_Programming_C++\\Project\\Project\\Data\\US.txt", 52);
    Asset Italy("Italy", "C:\\Users\\jordy\\Dropbox\\Solvay\\Courses\\Advanced_Programming_C++\\Project\\Project\\Data\\Italy.txt", 52);
    Asset UK("UK", "C:\\Users\\jordy\\Dropbox\\Solvay\\Courses\\Advanced_Programming_C++\\Project\\Project\\Data\\UK.txt", 52);
    Asset France("France", "C:\\Users\\jordy\\Dropbox\\Solvay\\Courses\\Advanced_Programming_C++\\Project\\Project\\Data\\France.txt", 52);

    // STEP 2:
    // The portfolio(s)

    // Step 2a:
    // Constructing The portfolio(s)

    Portfolio* AEX_index = new Portfolio("AEX Index");

    AEX_index->add_asset(AEX, 1); // in the AEX-index, the start is the full weight on the index itself
    AEX_index->add_asset(Philips);
    AEX_index->add_asset(Unilever);
    AEX_index->add_asset(Ahold);
    AEX_index->add_asset(ING);
    AEX_index->add_asset(Randstad);

    Portfolio* Countries = new Portfolio("Countries"); // weights were computed based on the market capitalisation
    Countries->add_asset(Canada, 0.0657);
    Countries->add_asset(France, 0.0690);
    Countries->add_asset(Germany, 0.0532);
    Countries->add_asset(Italy, 0.0227);
    Countries->add_asset(Japan, 0.1394);
    Countries->add_asset(UK, 0.1148);
    Countries->add_asset(US, 0.5352);


    // Step 2b:
    // Set-up (parameters)
    Parameters model_param;

    // The risk aversion on the market (somewhere between 0-10)
    model_param.MRA = 1.27;

    // Your personal risk aversion (somewhere between 0-10)
    model_param.PRA = 1.27;

    // Market inefficiency (usually between 5% - 15%)
    model_param.tau = 0.05;

    // Set_up a possible view combiner, even if you do not have views, a combiner must be set-up
    // This is because it is linked with a certain portfolio, which is needed in later steps
    ViewsCombiner* views_AEX = new ViewsCombiner(AEX_index);

    // Step 2c (only used in case of Black - Litterman analysis):
    // Declaring personal views on the different assets regarding future performance
    // and combining them with the portfolio

    // Absolute views
    Aview performance_of_ING(&ING, 0.12, 0.4, 0.012);

    // Relative views
    Rview performance_randstad_philips(&Randstad, &Philips, 0, 0.8, 0.1);
    Rview outperformance_unilever(&Unilever, &Ahold, 0.01, 0.6, 0.001);

    // Combine them together and with portfolio

    views_AEX->add_view(&performance_of_ING);
    views_AEX->add_view(&performance_randstad_philips);
    views_AEX->add_view(&outperformance_unilever);


    //  Step 2d:
    //  Selection of the computational method for the Omega-matrix (variance surrounding views)
    //  Also only in the case of BLACK LITTERMAN

    // 1. Simple use of own expert opinion on STDV of views
    STDVdirectly* se = new STDVdirectly(model_param.tau);

    // 2. Proportionate to the variance of the prior (to the assets)
    PropVarPrior* prop = new PropVarPrior(model_param.tau);

    // 3. Idzorek's method
    Idzorek* idzorek = new Idzorek(model_param.tau);


    // STEP 3:
    // Mean-Variance optimization

    // Step 3a:
    // Selection of expected returns that should be used for MV-optimization

    // 1. Based on average (past) returns
    AverageReturns* ar = new AverageReturns;
    ar->set_parameters(views_AEX, model_param.MRA);

    // 2. Based on Implied MV equilibrium returns
    ImpliedMVReturns* impl = new ImpliedMVReturns;
    impl->set_parameters(views_AEX, model_param.MRA);

    // 3. Black-Litterman model = based on combination of Implied MV equilibrium returns and views - All parameters should be given
    // Here the views come into play, hence also the OmegaComputation class we selected above
    BlackLitterman* bl_se = new BlackLitterman;
    BlackLitterman* bl_prop = new BlackLitterman;
    BlackLitterman* bl_idzorek = new BlackLitterman;

    bl_se->set_parameters(views_AEX, model_param.MRA,  se);
    bl_prop->set_parameters(views_AEX, model_param.MRA,  prop);
    bl_idzorek->set_parameters(views_AEX, model_param.MRA,  idzorek);

    // Step 3b:
    // Setting up an MV optimization object

    MeanVarianceOptimization* MV_opt = new MeanVarianceOptimization;


    // STEP 4:
    // Reporting

    ReportMaker reportingtool;

    string directory = "C:\\Users\\jordy\\Dropbox\\Solvay\\Courses\\Advanced_Programming_C++\\Project\\Project\\Results\\";

    cout << "Preparing reports" << endl;
    cout << "Report 1: ";

    // 1. AR
    MV_opt->optimise(ar, model_param.PRA);
    reportingtool.make_report_single_process(directory + "auto_AEX_AR_.txt", MV_opt);

    cout << "Finished;" << endl << "Report 2: ";

    // 2. Implied ER
    MV_opt->optimise(impl, model_param.PRA);
    reportingtool.make_report_single_process(directory + "auto_AEX_IMPL.txt", MV_opt);

    cout << "Finished;" << endl << "Report 3: ";

    // 3.1 BL - STDV
    MV_opt->optimise(bl_se, model_param.PRA);
    reportingtool.make_report_single_process(directory + "auto_AEX_BL_STDV.txt", MV_opt);

    cout << "Finished;" << endl << "Report 4: ";

    // 3.2 BL - prop_var
    MV_opt->optimise(bl_prop, model_param.PRA);
    reportingtool.make_report_single_process(directory + "auto_AEX_BL_Prop_var.txt", MV_opt);

    cout << "Finished;" << endl << "Report 5: ";

    // 3.3 BL - Idzorek
    MV_opt->optimise(bl_idzorek, model_param.PRA);
    reportingtool.make_report_single_process(directory + "auto_AEX_BL_Idzorek.txt", MV_opt);

    cout << "Finished;" << endl;

*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INTERACTIVE VERSION ///


    // SETTING UP ALL OBJECTS
    //ER
    ExpectedReturns* er_method;

    AverageReturns* ar = new AverageReturns;
    ImpliedMVReturns* impl = new ImpliedMVReturns;
    BlackLitterman* bl = new BlackLitterman;

    // OMEGA
    OmegaComputer* omega_method;

    STDVdirectly* se = new STDVdirectly;
    PropVarPrior* prop = new PropVarPrior;
    Idzorek* idzorek = new Idzorek;

    // views + combiner
    Rview* rel_view = new Rview;
    Aview* abs_view = new Aview;
    ViewsCombiner* views = new ViewsCombiner;

    // Portfolio
    Portfolio* P;

    // MV-optimzer
    MeanVarianceOptimization* MV_opt = new MeanVarianceOptimization;

    // Reporter
    ReportMaker* report = new ReportMaker;

    // Actual program

    // Introduction
    cout << "Welcome to this basic Mean-Variance optimising program. (made by Jordy Rillaerts)" << endl << endl
         << "Are you ready to make some money?" << endl
         << "...Of course you are, why else would you use me?" << endl << endl;

    // Determining the level of expertise
    bool beginner = false;
    string yes = "y";
    string answer;
    do {
        cout << "Are you an absolute beginner in this program, or do you easily make typos/mistakes/... ? (y/n)" << endl;
        cin >> answer;
        cout << "You said " << answer << ". Are you sure? (y/n)" << endl;
        cin >> yes;
    } while(yes != "y");
    if (answer == "y"){
        beginner = true;

    }

    // portfolio name
    Questions<string> portfolio_name("What is the name of the Portfolio you want to construct and optimize?");
    string name_port = portfolio_name.answer_and_verification(beginner);

    P = new Portfolio(name_port);

    // number of assets
    Questions<int> Q1("How many Assets do you want to add?");
    int n = Q1.answer_and_verification(beginner);

    // periodicity
    Questions<int> periodicity("What is the periodicity of your data? (#observations/year)");
    int period = periodicity.answer_and_verification();

    // Adding all assets
    for (int i = 0; i < n; i++){
        stringstream t;
        t << i + 1;

        // asking the name
        Questions<string> q_name_asset("What is the name of Asset " + t.str());
        string name_asset = q_name_asset.answer_and_verification();

        // Asking the adress of return-file
        Questions<string> q_adress_asset("What is the adress of the return-file of Asset " + t.str());
        string adress_asset = q_adress_asset.answer_and_verification(beginner);

        // Initial weight in portfolio
        Questions<double> q_weight_asset("What is the weight of " + name_asset + " in " + name_port);
        double weight_asset = q_weight_asset.answer_and_verification();

        // adding asset to portfolio
        Asset new_asset(name_asset, adress_asset, period);
        P->add_asset(new_asset, weight_asset);
   }

    // Asking for the necessary parameters (MRA, PRA, tau)
    Parameters param;
    cout << "What is the Market Risk aversion? (usually between 0-10, default = 1.27)" << endl;
    cin >> param.MRA;

    cout << "What is the Market inefficiency rate? (usually between 0.05-0.15, default = 0.05)" << endl;
    cin >> param.tau;

    cout << "What is your Personal risk aversion? (usually between 0-10, default = 1.27)" << endl;
    cin >> param.PRA;

    // Even when no views, viewscombiner should be linked to the portfolio
    views->set_portfolio(P);

    // Adding the views (optional)

    // Number of views
    Questions<int> q_number_views("How many Views do you have concerning the assets in " + P->name +  "?");
    int n_views = q_number_views.answer_and_verification(beginner);

    if (n_views >= 1){

        // Should use Black Litterman in case of views
        er_method = bl;

        // Choice of method for computing omega

        // setting up question
        Multiplechoice<OmegaComputer*> q_omega("What method for the computation of the Omega matrix would you like to use? (select number)");
        q_omega.add_choice(se);
        q_omega.add_choice(prop);
        q_omega.add_choice(idzorek);

        // asking and selecting
        omega_method = q_omega.answer_and_verification();


        // adding specific views
        for (int i = 0; i < n_views; i++){
            stringstream t;
            t << i + 1;

            // type of view
            Multiplechoice<View*> q_view("What kind of View is View " + t.str() + "?");
            q_view.add_choice(rel_view);
            q_view.add_choice(abs_view);

            // new view
            View* new_view = q_view.answer_and_verification();

            // Setting the subject
            Multiplechoice<Asset*> q_subject("Which Asset is the subject of View " + t.str());
            for (unsigned j = 0; j < P->number_of_assets; j++){
                q_subject.add_choice(&P->assets(j, 0));
            }

            Asset* subject = q_subject.answer_and_verification();
            new_view->subject = subject;

            // Setting the relative (if applicable)
            if (new_view->name() == "Relative view"){
                Multiplechoice<Asset*> q_relative("Which Asset is the relative of View " + t.str());
                for (unsigned j = 0; j < P->number_of_assets; j++){
                    q_relative.add_choice(&P->assets(j, 0));
                }

                Asset* relative = q_relative.answer_and_verification();
                new_view->relative = relative;
            }

            // Setting expectation
            Questions<double> q_exp("What is your expectation concerning the performance?");
            new_view->expectation = q_exp.answer_and_verification();

            // Setting confidence
            Questions<double> q_conf("What is your confidence in this view?");
            new_view->confidence = q_conf.answer_and_verification();

            // Setting stdv
            Questions<double> q_stdv("What is the standard error surrounding this view?");
            new_view->standard_error = q_stdv.answer_and_verification();

            views->add_view(new_view);

        }

        omega_method->set_parameters(param.tau, views);

    }

    else{

        // Which Expected returns object should we use  if no views
        // setting up question
        Multiplechoice<ExpectedReturns*> q_er("What method for the computation of the Expected returns would you like to use? (select number)");
        q_er.add_choice(ar);
        q_er.add_choice(impl);

        // selecting ER object
        er_method = q_er.answer_and_verification();

        // standard NULL pointer in case of no views
        omega_method = NULL;

    }

    // viewscombiner, omega (even when NULL), and MRA should be added ass parameter to Expected returns computer
    er_method->set_parameters(views, param.MRA, omega_method);

    cout << "Compute everything...";

    // Computations of the optimisation are done here
    MV_opt->optimise(er_method, param.PRA);

    // Standard filename
    string filename = P->name + "_" + er_method->name();
    if (omega_method != NULL){
        filename = filename + "_" + omega_method->name();
    }

    cout << "Report is being made...";

    // Make a report
    report->make_report_single_process("C:\\Users\\jordy\\Dropbox\\Solvay"
                                       "\\Courses\\Advanced_Programming_C++\\Project\\Project\\Results\\"
                                       + filename + ".txt", MV_opt);

    cout << "Finished!" << endl;


    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    return 0;
}

