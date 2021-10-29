#include <iostream>
#include "functions.h"

using std::cout, std::cin, std::endl;

int main() {
	int a;
	int b;
	
	bool isValid = false;

	while (isValid == false) { // while the range valid is false, we want to keep promting the input 
		std::cout << "Enter numbers 10 <= a <= b < 10000: ";
		std::cin >> a >> b ;
        isValid = is_valid_range(a,b);
		if (isValid == true) {
			count_valid_mv_numbers(a,b); // if true hsow results
		} else {  // if false we prompt again
			cout << "Invalid Input" << std::endl;
		}

	}
	
	return 0;
}