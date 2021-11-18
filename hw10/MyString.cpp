// only headers we need?
#include "MyString.h"

using namespace std;

// default constructor
MyString::MyString(): cstring(nullptr), csize(0), capacityOf(0) {
    cstring = new char[1];
    cstring[0] = '\0';
} // nullptr or '\0' w size of 1??

// copy constructor
MyString::MyString(const MyString& string): cstring(nullptr), csize(string.csize), capacityOf(string.capacityOf) {
    cstring = new char[csize + 1];
    for(size_t i=0; i<=csize; i++){
        cstring[i] = string.cstring[i];
    }
}

// copy constructor from c string
MyString::MyString(const char* str): cstring(nullptr), csize(0), capacityOf(0) {
    size_t currSize = 0;
    for (size_t i =0; str[i] != '\0'; i++){
        currSize++;
    }

    capacityOf = currSize +1;

    delete[] cstring;

    cstring = new char[currSize+1];

    csize = currSize;
    
    for(size_t i=0; i<=currSize; i++){
        cstring[i] = str[i];
    }
    

}

// destructor
MyString::~MyString(){
    delete[] cstring;
    cstring = nullptr;
    csize = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char* MyString::data() const{
    return cstring;
}

char MyString::front() const{

    return cstring[0];
    
}

char MyString::at(size_t i) const{
    if (i >= csize){
        throw std::out_of_range("out of range of at");
    }
    if ( cstring[i] == '\0'){
        throw;
    }
    return cstring[i];
}
void MyString::clear(){
    csize = 0;
    capacityOf = 1;
    delete[] cstring;
    char* newstr = new char[capacityOf];
    newstr[0] = '\0';
    cstring = newstr;
}

size_t MyString::size() const{
    return csize;
}
size_t MyString::length() const{
    return csize;
}
size_t MyString::capacity() const {
    // if (cstring == nullptr){
    //     return csize;
    // }
    return capacityOf;
}

size_t MyString::find(const MyString& str, size_t pos) const{

    bool first = false;
    bool match = false;

    size_t firstmatchindex = string::npos;
    for (size_t i = 0; i < str.csize; i++){
        for (size_t j = pos; j < csize; j++){
            if(str.cstring[i] == cstring[j]){
                if (first == false){
                    firstmatchindex = j;
                    first = true;
                }
                match = true;
            }
        }
        if (match == false){
            return string::npos;
        }
        match = false;
    }
    return firstmatchindex;

}

bool MyString::empty(){
    if (csize == 0){
        return true;
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////////

MyString& MyString::operator= (const MyString& str){

    if (this != &str){
        delete[] cstring;
        cstring = nullptr;
        csize = str.csize;
        cstring = new char[csize+1];
        for (size_t i = 0; i < csize; i++){
            cstring[i] = str.cstring[i];
        }
    }

    return *this;

}

MyString& MyString::operator+= (const MyString& str){

    // ['c','h','a','s','e','\0']         size = 5 capacity = 6
    // ['h','i','\0']                     size = 2 capacity = 3
    // ['c','h','a','s','e','h','i','\0'] size = 7 capacity = 8
    

    char *temp = new char[csize + str.csize+1];

    for (size_t i = 0; i < csize; i++){
        temp[i] = cstring[i];
    }
    for (size_t i = 0; i < str.csize; i++){
        temp[i+csize] = str.cstring[i];
    }

    temp[csize + str.csize] = '\0';
    delete[] cstring;
    cstring = temp;
    csize = csize + str.csize;

    capacityOf = csize+1;

    return *this;
}

bool operator== (const MyString& lhs, const MyString& rhs){
    if (lhs.csize != rhs.csize){
        return false;
    }

    for (size_t i = 0; i < lhs.csize; i++){
        if (lhs.cstring[i] != rhs.cstring[i]){
            return false;
        }
    }
    return true;
}

MyString operator+ (const MyString& lhs, const MyString& rhs){
    MyString newObj = lhs;
    newObj += rhs;

    return newObj;
}
///////////////////////////////////////////////////////////////////////////////////
std::ostream& operator<< (std::ostream& output, const MyString& string){
    for (size_t i = 0; i < string.length(); ++i){
        output << string.cstring[i];
    }
    return output;
}