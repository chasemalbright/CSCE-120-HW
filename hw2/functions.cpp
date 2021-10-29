#include <iostream>
#include "functions.h"

using std::cout, std::endl;


// this is tested and works
bool is_valid_range(int a, int b) {
	bool valid = false;
	if (a >= 10 && b < 10000 && b-a >= 0){ // we must check athe bounds of given integers to see if they are withing rules
		valid = true;
	}
	return valid;
}

// will have 2, 3, or 4 digits in the values
// ouputs will be M V or N
char classify_mv_range_type(int number) {

	// this is to count dig in number
    int digits = 0;

	int calcDigInNum = number;
    // calc numer of digits in the number 12345 has 5 digits test this
	while(calcDigInNum != 0) {
		calcDigInNum = calcDigInNum /10;
		digits++;
	}
	
	// need magnitudes of 10 for each digit we are comparing
	int magnitudeOfTen = 1;
	for(int i = 1 ;i < digits; i++) {
	    // for every digit we want to have corresponding multiple of 10 for each place
	    magnitudeOfTen = magnitudeOfTen * 10;
	}
	
	int increaseCount = 0;
	int decreaseCount = 0;      // these values initiate num of mountains, valleys and whether to increase or decrease count
	int mountainCount = 0;
	int valleyCount = 0;
	
	calcDigInNum = number / magnitudeOfTen; // find the value for first digit
	number = number % magnitudeOfTen;
	magnitudeOfTen = magnitudeOfTen / 10;
	
	
	int nextDigit;
	while (magnitudeOfTen > 0) {
	    nextDigit = number / magnitudeOfTen;  // find value for the nect consecutive digit
	    // we do this by dividing the num by diff mags of ten 25/10 gives 2 and 25%10 gives 5
		// so we compare these two digits to determine mt or val
	    if (nextDigit == calcDigInNum) {
	        // handles consecutive numbers
			// if values are repeating like 2112 just exit and return BAD
	        return 'N';
	    }
	    if (valleyCount == 0 && mountainCount == 0) { // check if counts are at zero to cont
	        if (nextDigit > calcDigInNum){
				// if next dig is greater then mountain
	            mountainCount = 1;
	        } else {
				// else then it is a valeyyyyyy
	            valleyCount = 1;
	        }
	    }
		// this if is to determine if next dig is bigger or smaller
	    if (nextDigit > calcDigInNum) {
	        increaseCount = increaseCount +1;      // i am using increments to determine if their are
	        decreaseCount = 0;                     // consecutive bigger or smaller numbrs like 1234 or 765
	    } else { // to determine if smaller
	        decreaseCount = decreaseCount +1;
	        increaseCount = 0;
	    }
		//this is exits progrm with n if therre are consecutive numbers
	    if (increaseCount > 1 || decreaseCount > 1) {
	        return 'N';
	    }
		// this stuff below sets values used in loop to be used for the rest of the numbers
	    calcDigInNum = nextDigit;
	    number = number % magnitudeOfTen;
	    magnitudeOfTen = magnitudeOfTen / 10;
	}
	// 
	if (mountainCount == 1) {
	    return 'M';
	} else {           // determines if to return mountain or valley ** check edge cases for returnuing N **
	    return 'V';
	}
	
	
}

void count_valid_mv_numbers(int a, int b) {
	// TODO(student): count the number of valid mountain ranges and valleys
	// ranges in the range [a, b] and print out to console using the format
	// in Requirement 4 of the homework prompt

	//bool validity = is_valid_range(a, b); // first we must check if valid

	int mountainCount = 0;   // DO NOT CHECK FOR VALIDITY IN THIS FUNC
	int valleyCount = 0;

	// if (validity){
	for (int i = a; i <= b; i++) {
		char result = classify_mv_range_type(i);  // for loop to loop through every num in given range
		if (result == 'M') {
			mountainCount++;
		} else if (result == 'V') {
			valleyCount ++;
		}

	} 
	// the necessary print statement
	cout << "There are " << mountainCount << " mountain ranges and " << valleyCount << " valley ranges between " << a << " and " << b << "." << std::endl;

	// } else {
	// 	cout << "Invalid Input" << std::endl;
	// }
}