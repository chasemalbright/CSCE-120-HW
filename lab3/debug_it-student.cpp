//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//                              DEBUG IT! LAB                               //
//                           debug_it-student.cpp                           //
//                                                                          //
// Written By : Michael R. Nowak        Environment : Mac OS X 10.10.5      //
// Date ......: 2017/05/16              Compiler ...: Homebrew GCC 6.3.0_1  //
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <string>
#include <random>
using namespace std;

constexpr int NO_TEMPS = 10;

int main (int argc, char * argv[])
{
    char delim = '\n';
    std::default_random_engine d_engine{};
    std::normal_distribution<> temp_dist{32, 2};
    vector <double> ftemps ; int j = 0; int i = 100;
    for (int i = 0; i <= NO_TEMPS; ++i) {
        ftemps.push_back(temp_dist(d_engine));
    }
    vector<double> ctemps;
    double ctemp;
    for (decltype(ftemps.size()) i = 0; i < ftemps.size() - 1; i++) {
        ctemp = ((ftemps.at(i) - 32) * (5.0 / 9.0));
        ctemps.push_back(ctemp);
    }

    
    double min = ctemps.at(0); 
    double max = ctemps.at(0);


    for (decltype(ctemps.size()) i = 0; i <= ctemps.size() - 1; ++i){
        if (min > ctemps.at(i)){
            min = ctemps.at(i);
        }
        if (max < ctemps.at(i)){
            max = ctemps.at(i);
        }
            
        cout << "[" << i << "]" << " " << ftemps.at(i) << " to " << ctemps.at(i) << delim;
    }
    cout << "Max Temp (in celsius) : " << max << '\t' << "Min Temp (in celsius) : " << min << endl;
    return 0;
}