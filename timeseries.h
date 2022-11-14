#ifndef TIMESERIES_H
#define TIMESERIES_H
#include <vector>
#include <iostream>

/*!
 * Base class:
 * Allows user to import a dataset consisting of a time series.
 * Recomendend is copying a time-series (column) from excell and saving it into a .txt file.
 * Important:
 * -> The comma-sign is a .
 * -> Take care of the last 'empty' line of the .txt file => coul be read as a 0 value.
 */


class TimeSeries{

public:
    TimeSeries();
    TimeSeries(std::string origin_adress);

    std::vector <double> values; // elements of the TS
    std::string adress; // adress where the .txt file is saved

    unsigned length_series; // number of elements in TS

    void read_from_file(std::string adress);
    void print();


};

#endif // TIMESERIES_H
