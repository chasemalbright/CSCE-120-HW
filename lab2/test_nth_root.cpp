#include <iostream>
#include <cmath>
#include "./nth_root.h"
#include <stdexcept>

int main() {
    {   // MINIMUM REQUIREMENT (for this lab)
        // just call the function with various values of n and x
        
        nth_root(1, 1);
        nth_root(-1, 1);
        nth_root(-5, 1);
        nth_root(-10, 2);
        nth_root(-3, 1);
        nth_root(10, 1);
        nth_root(3, 2);
        nth_root(5, 0);
        nth_root(6, 1);
        nth_root(3, -2);
        nth_root(10, 5);
        nth_root(2, 3.122/2.31);
    }
    try {
        nth_root(0, 1);
    } catch (std::domain_error) {}
    try {
        nth_root(4, -1);
    } catch (std::domain_error) {}
    try {
        nth_root(-4, 0);
    } catch (std::domain_error) {

    }

    {   // TRY HARD
        // report the value
        double actual = nth_root(2, 1);
        std::cout << "nth_root(2, 1) = " << actual << std::endl;

        actual = nth_root(3,2);
        std::cout << "nth_root(2, 1) = " << actual << std::endl;
    }

    {   // TRY HARDER
        // compare the actual value to the expected value
        double actual = nth_root(2, 1);
        double expected = 1;
        if (std::fabs(actual - expected) > 0.00005) {
            std::cout << "[FAIL] (n=2, x=1)" << std::endl;
            std::cout << "  expected nth_root(2, 1) to be " << expected << std::endl;
            std::cout << "  got " << actual << std::endl;
        } else {
            std::cout << "[PASS] (n=2, x=1)" << std::endl;
        }
    }
}
