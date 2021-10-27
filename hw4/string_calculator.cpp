#include <iostream>
#include <string>
#include "./string_calculator.h"

using std::cout, std::endl;
using std::string;

unsigned int digit_to_decimal(char digit) {
    switch (digit) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return (digit - '0');
        default:
            throw std::invalid_argument("Invalid Argument");
        
    }
}

char decimal_to_digit(unsigned int decimal){
    switch(decimal){
        case 0:
            return '0';
        case 1:
            return '1';
        case 2:
            return '2';
        case 3:
            return '3';
        case 4:
            return '4';
        case 5:
            return '5';
        case 6:
            return '6';
        case 7:
            return '7';
        case 8:
            return '8';
        case 9:
            return '9';
        default:
            throw std::invalid_argument("Invalid Argument");
    }
}

string trim_leading_zeros(string num){
    string noZeros = num;
    
    if (num =="00" || num =="000" || num =="00000" || num =="-00000") {
        return "0";
    }
    
    if (num[0] == '-') {
        noZeros.erase(0,1);
        while (noZeros.at(0) == '0'){
        noZeros = noZeros.substr(1);
    }
        return noZeros.insert(0, "-");
    } else {
        while (noZeros.at(0) == '0'){
        noZeros = noZeros.substr(1);
    }
    return noZeros;
    }
}

string charToString(char dec){
    switch(dec){
        case '0':
            return "0";
        case '1':
            return "1";
        case '2':
            return "2";
        case '3':
            return "3";
        case '4':
            return "4";
        case '5':
            return "5";
        case '6':
            return "6";
        case '7':
            return "7";
        case '8':
            return "8";
        case '9':
            return "9";
        default:
            throw std::invalid_argument("Invalid Argument CHAR");
    }
}
//#######################################################################################################
string add(string lhs, string rhs) {
    
    string sum = "";
    
    if (lhs == "0" && rhs == "0") {
        return "0";
    }
    if (lhs == "0"){
        return rhs;
    }
        if (rhs == "0"){
        return lhs;
    }
    
    
    lhs = trim_leading_zeros(lhs);      // remove leading 0s
    rhs = trim_leading_zeros(rhs);
    
    
    if (lhs[0] != '-' && rhs[0] != '-'){ // all positives
        int addLeadZeros = 0;
        if (lhs.length() < rhs.length()){
            addLeadZeros = rhs.length() - lhs.length();
            for(int i = 0; i < addLeadZeros; i++){
                lhs.insert(0,"0");
            }
                                 // to make the strings same length, replace blanks w 0s
        }
        if (lhs.length() > rhs.length()) {
            addLeadZeros = lhs.length() - rhs.length();
            for(int i = 0; i < addLeadZeros; i++){
                rhs.insert(0,"0");
            }
            
        }
        
        // begin arithmatic
        int carry = 0;
        int numA;   // since we are comparing digits decalre these vars
        int numB;
        int middleAddDigits = 0;
        for (int i = rhs.length()-1; i >= 0; i--) {
            numA = digit_to_decimal(rhs[i]);         // we want to move from highest index to lowest
            numB = digit_to_decimal(lhs[i]);
            
            middleAddDigits = numA + numB + carry;
                                                                    //follow the process fro adding (school adding)
            if (middleAddDigits < 10){
                sum.insert(0, charToString(decimal_to_digit(middleAddDigits)));
                carry = 0;
            }else {                                                                 // if > 10 carry = 1
                sum.insert(0, charToString(decimal_to_digit(middleAddDigits %10)));
                carry = 1;
            }
        }                                   // at the end insert the carry into index 0
        sum.insert(0,charToString(decimal_to_digit(carry)));
        
        
    } else {
        lhs.erase(0,1);
        rhs.erase(0,1); // for addition of negatives remove the negatives sign
        
        int addLeadZeros = 0;
        if (lhs.length() < rhs.length()){
            addLeadZeros = rhs.length() - lhs.length();
            for(int i = 0; i < addLeadZeros; i++){
                lhs.insert(0,"0");
            }
                                 // to make the strings same length, replace blanks w 0s
        }
        if (lhs.length() > rhs.length()) {
            addLeadZeros = lhs.length() - rhs.length();
            for(int i = 0; i < addLeadZeros; i++){
                rhs.insert(0,"0");
            }
            
        }
        
        // begin arithmatic
        int carry = 0;
        int numA;
        int numB;
        int middleAddDigits = 0;                                              //  *** SAME CODE
        for (int i = rhs.length()-1; i >= 0; i--) {
            numA = digit_to_decimal(rhs[i]);
            numB = digit_to_decimal(lhs[i]);
            
            middleAddDigits = numA + numB + carry;
            
            if (middleAddDigits < 10){
                sum.insert(0, charToString(decimal_to_digit(middleAddDigits)));
                carry = 0;
            }else {
                sum.insert(0, charToString(decimal_to_digit(middleAddDigits %10)));
                carry = 1;
            }
        }
        sum.insert(0,charToString(decimal_to_digit(carry)));
        sum.insert(0,"-");
        
    }
    return trim_leading_zeros(sum);
}

string multiply(string lhs, string rhs) {
    
    lhs = trim_leading_zeros(lhs);      // remove leading 0s
    rhs = trim_leading_zeros(rhs);
    
    if (lhs == "0" || rhs == "0") {  // return 0 if 0 * int
        return "0";                 
    }
    // this is bulky, but an if block for each scenario with slightly modified inputs and outputs
    
    if (lhs[0] != '-' && rhs[0] != '-'){
        string intermediateProduct(lhs.length() + rhs.length(), 0); // we want to set a middleman with length of str1 + str2
        
        for (int i = lhs.length() - 1; i >= 0; i--){            // two for loops, this is becasue we want to multiply each digit by each dig of other num
            for (int x = rhs.length() - 1; x >= 0; x--){        //4dig * 4dig gives us 16 combinations
                int n = (digit_to_decimal(lhs[i]) * digit_to_decimal(rhs[x])) + intermediateProduct[i + x + 1];
                intermediateProduct[i + x + 1] = n % 10;
                intermediateProduct[i + x] = intermediateProduct[i + x] + n/10;  //use a carry and % and / to determine the keeper and carry dig
            }
        }
        for (unsigned int i = 0; i < intermediateProduct.length(); i++) { // since adding needs a zero for each line of addition =>
            intermediateProduct[i] += '0';
        }
       if (intermediateProduct[0] == '0') { // we want to keep track of leading 0s and other 0s
            return intermediateProduct.substr(1);
        }
        return intermediateProduct;
    }
    if (lhs[0] == '-' && rhs[0] == '-'){
        lhs = trim_leading_zeros(lhs);      // remove leading 0s
        rhs = trim_leading_zeros(rhs);
        
        lhs.erase(0,1);
        rhs.erase(0,1);
        string intermediateProduct(lhs.length() + rhs.length(), 0); // we want to set a middleman with length of str1 + str2
        
        for (int i = lhs.length() - 1; i >= 0; i--){            // two for loops, this is becasue we want to multiply each digit by each dig of other num
            for (int x = rhs.length() - 1; x >= 0; x--){        //4dig * 4dig gives us 16 combinations
                int n = (digit_to_decimal(lhs[i]) * digit_to_decimal(rhs[x])) + intermediateProduct[i + x + 1];
                intermediateProduct[i + x + 1] = n % 10;
                intermediateProduct[i + x] = intermediateProduct[i + x] + n/10;  //use a carry and % and / to determine the keeper and carry dig
            }
        }
        for (unsigned int i = 0; i < intermediateProduct.length(); i++) { // since adding needs a zero for each line of addition =>
            intermediateProduct[i] += '0';
        }
       if (intermediateProduct[0] == '0') { // we want to keep track of leading 0s and other 0s
            return intermediateProduct.substr(1);
        }
        return intermediateProduct;
    }
    if (lhs[0] == '-' && rhs[0] != '-'){
        lhs = trim_leading_zeros(lhs);      // remove leading 0s
        rhs = trim_leading_zeros(rhs);
        lhs.erase(0,1);
        string intermediateProduct(lhs.length() + rhs.length(), 0); // we want to set a middleman with length of str1 + str2
        
        for (int i = lhs.length() - 1; i >= 0; i--){            // two for loops, this is becasue we want to multiply each digit by each dig of other num
            for (int x = rhs.length() - 1; x >= 0; x--){        //4dig * 4dig gives us 16 combinations
                int n = (digit_to_decimal(lhs[i]) * digit_to_decimal(rhs[x])) + intermediateProduct[i + x + 1];
                intermediateProduct[i + x + 1] = n % 10;
                intermediateProduct[i + x] = intermediateProduct[i + x] + n/10;  //use a carry and % and / to determine the keeper and carry dig
            }
        }
        for (unsigned int i = 0; i < intermediateProduct.length(); i++) { // since adding needs a zero for each line of addition =>
            intermediateProduct[i] += '0';
        }
       if (intermediateProduct[0] == '0') { // we want to keep track of leading 0s and other 0s
            intermediateProduct.erase(0,1);
            intermediateProduct.insert(0,"-");
            return intermediateProduct;         // this is to put the neg sign back
        }
        intermediateProduct.insert(0,"-");
        return intermediateProduct;
    }
    if (lhs[0] != '-' && rhs[0] == '-'){
        lhs = trim_leading_zeros(lhs);      // remove leading 0s
        rhs = trim_leading_zeros(rhs);
        rhs.erase(0,1);
        string intermediateProduct(lhs.length() + rhs.length(), 0); // we want to set a middleman with length of str1 + str2
        
        for (int i = lhs.length() - 1; i >= 0; i--){            // two for loops, this is becasue we want to multiply each digit by each dig of other num
            for (int x = rhs.length() - 1; x >= 0; x--){        //4dig * 4dig gives us 16 combinations
                int n = (digit_to_decimal(lhs[i]) * digit_to_decimal(rhs[x])) + intermediateProduct[i + x + 1];
                intermediateProduct[i + x + 1] = n % 10;
                intermediateProduct[i + x] = intermediateProduct[i + x] + n/10;  //use a carry and % and / to determine the keeper and carry dig
            }
        }
        for (unsigned int i = 0; i < intermediateProduct.length(); i++) { // since adding needs a zero for each line of addition =>
            intermediateProduct[i] += '0';
        }
       if (intermediateProduct[0] == '0') { // we want to keep track of leading 0s and other 0s
            intermediateProduct.erase(0,1);
            intermediateProduct.insert(0,"-");  // this is to put the neg sign back
            return intermediateProduct;
        }
        intermediateProduct.insert(0,"-");
        return intermediateProduct;
    }
    
    return"error";
}