#include <iostream>
#include <string>
#include <limits>
#include "./string_calculator.h"

using std::cout, std::endl, std::cin;
using std::string;

int main() {
    cout << "String Calculator" << endl;
    cout << "\"q\" or \"quit\" or ctrl+d to exit" << endl;
    
    string input;

    string firstNum;
    string secondNum;
    int index;
    // TODO(student): implement the UI
    while (input != "q" || input != "quit"){
        cout << ">> ";
        getline(cin, input);
        cout << endl;
        if (input == "q" ||  input == "quit") {
            break;
        }
        if (input.find('+') != std::string::npos) {
            index = input.find(" + ");
            firstNum = input.substr(0,index);
            secondNum = input.substr(index+3, input.length());

            cout << "ans =" << endl;
            cout << endl;
            cout << "    " << add(firstNum, secondNum) << endl;
            cout << endl;
        }
    
        if (input.find('*') != std::string::npos) {
            index = input.find(" * ");
            firstNum = input.substr(0,index);
            secondNum = input.substr(index+3, input.length());

            cout << "ans =" << endl;
            cout << endl;
            cout << "    " << multiply(firstNum, secondNum) << endl;
            cout << endl;
        }

    }
    cout << "farvel!";
}

