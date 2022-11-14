#include "parameters.h"


Parameters::Parameters(double Market_risk_aversion, double Personal_risk_aversion, double Market_inefficiency){
    tau = Market_inefficiency;
    MRA = Market_risk_aversion;
    PRA = Personal_risk_aversion;

}

Parameters::Parameters(double Market_risk_aversion, double Market_inefficiency){
    tau = Market_inefficiency;
    MRA = Market_risk_aversion;
    PRA = Market_risk_aversion;

}

