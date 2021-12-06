#include "problem1.h"
#include <stdexcept>
using std::string;

void add_to_row(Row& row,const std::string& str){

    string* old = row.array;
    size_t oldSize = row.size;
    // delete the existing array
    delete[] row.array;

    //update sizes and cap
    row.capacity = row.capacity+1;
    row.size = row.size+1;

    row.array = new string[row.capacity] {};

    for (size_t i = 0; i < oldSize; i ++){
        row.array[i] = old[i];
    }
    row.array[row.size-1] = str;
    delete[] old;
}

string remove_from_row(Row& row){

    if (row.size ==0){
        throw std::out_of_range("NO DUCKS!");
    }
    string* old = row.array;
    // delete the existing array
    delete[] row.array;
    row.size = row.size-1;

    row.array = new string[row.capacity] {};

    for (size_t i = 1; i < row.size+1; i ++){
        row.array[i-1] = old[i];
    }
    string hold = old[0];
    delete[] old;
    return hold;

}

// Row split(Row& row){

//     string* old = row.array;
//     delete[] row.array;

//     row.array = new string[row.capacity] {};
//     string* ret = new string[row.capacity] {};

//     if (row.size%2 ==0){
//         row.size = row.size/2;

//     }




// }

int main() {
    Row test;
    add_to_row(test,"hi");

    remove_from_row(test); 


}
