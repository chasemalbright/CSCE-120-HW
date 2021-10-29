#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include "parallel_tracks.h"

using std::string; using std::ifstream;


//-------------------------------------------------------
// Name: get_runner_data
// PreCondition:  the prepped parallel arrays , and a legit filename is pass
// PostCondition: all arrays contain data from the csv file given
//---------------------------------------------------------
void get_runner_data( const std::string& file, double timeArray[], std::string countryArray[], 
		unsigned int numberArray[], std::string lastnameArray[]) 
{
	ifstream runStream = ifstream(file);
	if (!runStream.is_open()){
		throw std::invalid_argument("Cannot open file");
	}

	string data;
	int lineCounter = 0;
	int spaceIndexAry[5]={0,0,0,0,0};


	while (getline(runStream, data)){

		data = trim(data); // may remove *****

		if (data.length() < 7 && lineCounter < 9){
			throw std::domain_error("File missing data");
		}
		int spaces = 0;
		
		
		for (unsigned int i = 0; i < data.size(); i++){
			if (data[i] == ' '){
				spaceIndexAry[spaces] = i;
				spaces++;
			}
		}
		
		
		string runTime1 = data.substr(0,spaceIndexAry[0]);
		string country1 = data.substr(spaceIndexAry[0]+1, spaceIndexAry[1] - spaceIndexAry[0]-1);
		string number1 = data.substr(spaceIndexAry[1]+1, spaceIndexAry[2] - spaceIndexAry[1]-1);
		string name1 = data.substr(spaceIndexAry[2]+1, data.length()-1);



		
		// tests for invalid times
		if (runTime1.length() <2 || runTime1.find('-') != std::string::npos){
			throw std::domain_error("File contains invalid data (time)");
		}

		// tests for invalid countries
		if (country1.length() != 3){
			throw std::domain_error("File contains invalid data (country)");
		}
		string letters = "abcdefghijklmnopqrstuvwxyz1234567890!@#$%^&*()_+{}[]<,>.?/~`";
		for (unsigned int i =0; i < letters.length(); i++){
			if (letters[i] == country1[0] || letters[i] == country1[1] || letters[i] == country1[2]){
				throw std::domain_error("File contains invalid data (country)");
			}
		}

		//tests for invalid numbers
		if (number1.length() > 2){
			throw std::domain_error("File contains invalid data (number)");
		}
		string letters2 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!`!@#$%^&*()_+:{}?><~`,./|@..";
		for (unsigned int i =0; i < letters2.length(); i++){
			if (letters2[i] == number1[0] || letters2[i] == number1[1]){
				throw std::domain_error("File contains invalid data (number)");
			}
		}

		//tests for invalid names
		if (name1.length() < 2){
			throw std::domain_error("File contains invalid data (name)");
		}
		string letters3 = "1234567890'',./<>?:;[].{}|`1234567890-=~!@#$%^&*()_+";  // i keep failing this case, maybe try numbers
		for (unsigned int i = 0; i < letters3.length(); i++){
			for (unsigned int j = 0; j < name1.length(); j++){
				if (letters3[i] == name1[j]){
					throw std::domain_error("File contains invalid data (name)");
				}
			}
		}


		timeArray[lineCounter] = stod(runTime1);
		countryArray[lineCounter] = country1;
		numberArray[lineCounter] = stoi(number1);
		lastnameArray[lineCounter] = name1;

		for (unsigned int i = 0; i < 5; i++){
			spaceIndexAry[i] = 0;
		}

		lineCounter++;
	}
	

}

//-------------------------------------------------------
// Name: prep_double_array
// PreCondition:  a double arrays is pass in
// PostCondition: data in the array is 'zeroed' out
//---------------------------------------------------------
void prep_double_array(double ary[])
// making sure all values within the array are set to 0.0;
{
	for (int i = 0; i < 9; i++){
		ary[i] = 0.0;
	}
}

//-------------------------------------------------------
// Name: prep_double_array
// PreCondition:  a double arrays is pass in
// PostCondition: data in the array is 'zeroed' out
//---------------------------------------------------------
void prep_unsigned_int_array(unsigned int ary[])
// making sure all values within the array are set to 0;
{
	for (int i = 0; i < 9; i++){
		ary[i] = 0;
	}
}

//-------------------------------------------------------
// Name: prep_string_array
// PreCondition:  a string arrays is pass in
// PostCondition: data in the array is "N/A" out to determine if
// a value has changed
//---------------------------------------------------------
void prep_string_array(std::string ary[])
// making sure all values within the array are set to "N/A";
{
	for (int i = 0; i < 9; i++){
		ary[i] = "N/A";
	}
}

//-------------------------------------------------------
// Name: get_ranking
// PreCondition:  just the time array is passed in, and has valid data
// PostCondition: after a very inefficient nested loop to determine the placements 
// and places the ranks in a new array. That new array is returned
//---------------------------------------------------------
void get_ranking(const double timeArray[], unsigned int rankArray[])
{
	for (int i = 0; i < 9; i++){
        int rank =0;
        for(int j = 0; j < 9; j++){
            if (timeArray[j] < timeArray[i]){
                rank++;
            }
        }
        rankArray[i] = rank+1;
    }

	// double timeArr[9];
    
    // for (int i = 0; i < 9; i++){
    //     timeArr[i] = timeArray[i];
    // }
    
    // double lowest;
    
    // for (int i = 0; i < 9; i++){
    //     for (int j = 0; j < 9; j++){
    //         if (j != 8){
    //             if (timeArr[j] > timeArr[j+1]){
    //                 lowest = timeArr[j];
    //                 timeArr[j] = timeArr[j+1];
    //                 timeArr[j+1] = lowest;
    //             }
    //         }
    //     }
    // }
    
    // for (int i = 0; i < 9; i++){
    //     for (int j = 0; j < 9; j++){
    //         if (timeArr[i] == timeArray[j]){
    //             rankArray[i] = j+1;
    //         }
    //     }
    // }

	// unsigned int rankRev[9];
	// for (int i = 8; i <=0; i--){
    //     rankRev[8-i] = rankArray[i];
    // }
	// unsigned int rankRev1[9] = {1,2,3,4,5,6,7,8,9};
	// for (int i = 0; i < 9; i++){
    //     rankArray[i] = rankRev1[i];
    // }

}


//-------------------------------------------------------
// Name: print_results
// PreCondition:  almost all parallel arrays are passed in and have valid data
// PostCondition: after a very inefficient nested loop to determine the ranks
// it then displays then along with a delta in time from the start
//---------------------------------------------------------
void print_results(const double timeArray[], const std::string countryArray[],
		const std::string lastnameArray[], const unsigned int rankArray[])
{

	std::cout << "Final results!!";
	std::cout << std::setprecision(2) << std::showpoint << std::fixed << std::endl;
	double best_time = 0.0;
		
	// print the results, based on rank, but measure the time difference_type
	for(unsigned int j = 1; j <= SIZE; j++)
	{
		
		// go thru each array, find who places in "i" spot
		for(unsigned int i = 0; i < SIZE; i++)
		{
			if(rankArray[i] == 1) // has to be a better way, but need the starting time
			{
				best_time = timeArray[i];
			}
			
			
			if(rankArray[i] == j) // then display this person's data
			{
				// this needs precision display
				std::cout << "[" << j << "]  " << timeArray[i] << " " << std::setw(15) << std::left << lastnameArray[i] << "\t" << "(" << countryArray[i] << ")  +" << (timeArray[i] - best_time) << std::endl; 
			}
			
		}
	}	
}

std::string trim(const std::string word) {
	string ret = word;

	// remove whitespace from the beginning
	while (!ret.empty() && isspace(ret.at(0))) {
			ret.erase(0, 1);
		}

	// remove whitespace from the end
	//  Note: last index is (.size() - 1) due to 0 based indexing
	while (!ret.empty() && isspace(ret.at(ret.size()-1))) {
		ret.erase(ret.size()-1, 1);
	}
	
	return ret;
}