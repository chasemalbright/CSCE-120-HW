/******************************************************************************

File: main.cpp
Author: Prof. Lupoli & Andrew Nemec
Date: 2/16/2021
Section: 
E-mail: slupoli@tamu.edu
Description:
This file contains C++  code that will simulate data collected from a track 
event with 9 lanes. The code will sort the order, then display the results

Updates
Author: J. Michael Moore & Paul Taele

Data File Information
name: data.csv
content: The csv file will contain data in the constant form of:
<Time (double)> <Abbreviated Country (String)> <Uniform number (int)> <Lastname (String)>
32.7 USA 12 Moore
36.5 RUS 35 Polsley
45.8 ENG 73 Teale
52.34 CHN 14 Nemec
76.45 ITY 23 Lupoli     

*******************************************************************************/

#include <iostream>
#include <fstream>
#include "parallel_tracks.h"

using std::cin; using std::cout; using std::endl;
using std::string; using std::getline; using std::ifstream;
using std::invalid_argument; using std::domain_error;

int main()
{
    double time[9];
    string country[9];
    unsigned int runnerNumber[9];
    string lastname[9];

    unsigned int rankAry[9];
	
    prep_double_array(time);
    prep_unsigned_int_array(runnerNumber);
    prep_string_array(country);
    prep_string_array(lastname);



    // string fileName;
    // cout << "Enter file name: ";
    // cin >> fileName;

    bool valid = false; // we need to use a while loop with try catches inside
    string fileName;

    while (valid == false){
        cout << "Enter file name: ";
        cin >> fileName;

        try{
            get_runner_data(fileName, time, country, runnerNumber, lastname);
        }
        catch (std::invalid_argument& e) {
            cout << "Invalid File: " << e.what() << endl; // i need to throw error message in output
            continue; // cont continues to top of loop
        }
        catch (std::domain_error& e) {
            cout << "Invalid File: " << e.what() << endl;
            continue;
        }
        valid = true;
    }
    
    get_ranking(time, rankAry);

    print_results(time,country,lastname,rankAry);



    return 0;
}

