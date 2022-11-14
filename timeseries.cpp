/**
    timeseries.cpp
    @author Jordy Rillaerts
    @version 1.0 18/03/18
*/

#include <iostream>

#include "timeseries.h"
#include <fstream>
#include <sstream>

using namespace std;

/*!
 * Constructor.
 */
TimeSeries::TimeSeries(){
}

/*!
 * Constructor.
 * Constructor given an adress automatically loads the TS from this adress.
 * @param adress. The adress where the .txt file is saved on your pc.
 */
TimeSeries::TimeSeries(string origin_adress){
    adress = origin_adress;
    read_from_file(adress);
}


/*!
 * File-reader.
 * loads the data from the .txt file from the given adress.
 * @param adress. The adress where the .txt file is saved on your pc.
 */
void TimeSeries::read_from_file(string adress){
        ifstream file;
        file.open(adress);
        if (file.is_open()){
                while ( !file.eof() ){
                    string line;
                    getline(file, line);
                    stringstream fs( line );
                    double f = 0.0;
                    fs >> f;
                    values.push_back(f);
                }
                file.close();
                }
        else {
            values.push_back(0.0);
        }
        length_series = values.size();
}

/*!
 * Data printer.
 * Prints the data line per line to the console.
 */
void TimeSeries::print(){
        for (auto i=values.begin(); i < values.end(); i++){
            cout << *i << endl;
        }
}





