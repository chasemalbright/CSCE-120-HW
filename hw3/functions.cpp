#include <stdexcept>

int Largest(int a, int b, int c) { // for this function the error i found were a ">>" and a missing semicolon
  int initial = 0; // initial is more easier to see than d vs b
  if ((a >= b) && (a >= c)) {
    initial = a;
  } else if ((b >= a) && (b >= c)) {             // try using the inputs from mimir
    initial = b;
  } else if ((c >= a) && (c >= b)) {
    initial = c;
  }
  return initial;
}

bool SumIsEven(int a, int b) { // in this function, i found that there was a missing { and a logic error
  if (((a+b)%2) == 0) {
      return true;
  } else {                    //PASSED
      return false;
  }
}

int BoxesNeeded(int apples) {  // i found that the only error was in the return line
  if (apples <= 0){ // account for weird illogical inputs
    return 0;
  } else {
    if (apples % 20 == 0){
    return (apples /20);
    } else {
      return ((apples/20)+1);
    }
  }
}

bool SmarterSection(int A_correct, int A_total, int B_correct, int B_total) { // a lot wrong, had to redo logic and throw for invalid input
    if ((A_correct < 0) || (A_total < 0) || (B_correct < 0) || (B_total < 0)){
        throw std::invalid_argument("Invalid Argument: inputs less than 0");
    }
    if ((A_correct > A_total) || (B_correct > B_total)) {
        throw std::invalid_argument("correct greater than total questions");
    }
    if ((static_cast<double>(A_correct)/A_total) > ((static_cast<double>(B_correct)/B_total))) {
        return true;
    } else {
        return false;
    }
}


bool GoodDinner(int pizzas, bool is_weekend) { // had to redo logic and fix syntax errors, brances based on isweekend then if the pizzas meet conditions
    if (is_weekend){
        if (pizzas >= 10) {
            return true;
        } else {
            return false;
        }
    } else {
        if (pizzas >= 10 && pizzas <= 20){
            return true;
        } else {
            return false;
        }
    }
}


int SumBetween(int low, int high){  // had to redo logic to throw exceptions, had to use clever math for checking if there will be overflow
    // int int32_MAX = 32767+1;
    // int int32_MIN = -32768-1;
    if (low > high) {
        throw std::invalid_argument("low and high out of order");
    }
    if (low < 0 && high > 0) {
        int calculation = 0;
        for (int n = high+low; n <= high; n++){
          if (((n > 0) && (((INT32_MAX - n) < calculation))) || (((n < 0) && ((INT32_MIN - n) > calculation)))) {
            throw std::overflow_error("there is overflow in the range sum");
          } else {
            calculation = calculation + n;
          }
        }
        return calculation;
    } else {
        int sbcalculation = 0;
        for (int i = low; i <= high; i++){                                            // the for loop is checking for each addition of i, will adding the next number casue overflow? if so, throw except
            if (((i > 0) && (((INT32_MAX - i) < sbcalculation))) || (((i < 0) && ((INT32_MIN - i) > sbcalculation)))){
                throw std::overflow_error("there is overflow in the range sum");
            } else {
                sbcalculation = sbcalculation + i;
            }
        }
        return sbcalculation;
    }
}

int Product(int a, int b) {
    if (a == 0 || b == 0) {
        return 0;
    }
    if (a > 0 && b > 0){
        if (a > (INT32_MAX / b)){
            throw std::overflow_error("there is overflow1");
        } else {
            return a*b;
        }
    }
    if (a < 0 && b < 0) {
        if ((a*-1) > (INT32_MAX / (b*-1))){
            throw std::overflow_error("there is overflow2");
        } else {
            return a*b;
        }
    }
    if (a > 0 && b < 0) {
        if (a > (INT32_MIN / b)) {
            throw std::overflow_error("there is overflow3");
        } else {
            return a*b;
        }
    }
    if (a < 0 && b > 0) {
        if (b > (INT32_MIN / a)) {
            throw std::overflow_error("there is overflow3");
        } else {
            return a*b;
        }
    }
    return a*b;
}


// HINT: Consider forming conditions forstd::overflow_errorby usinga,b, 
//and INT32_MAXusing division expressions instead of multiplication. 
//Likewise, use a,b, and INT32_MIN in division expressions (for negative product values).