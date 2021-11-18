// We need these headers and file guards
#ifndef MYSTRING_H
#define MYSTRING_H
#include<iostream>

using namespace std;


class MyString{

private:// private data members
    //unsigned int sizeOfString;
    char* cstring;
    size_t csize;
    size_t capacityOf;

public:
//big three are needed, destructors, copy constructors, default?
    MyString(); // default
    MyString(const MyString& string); // copy constructor
    MyString(const char* str);
    //  or  (const char*)
    ~MyString(); // destructor


    const char* data() const; // returns a pointer to the cstring
    char front() const; // returns the first char in cstring array

    size_t capacity() const;
    char at(size_t i) const; // return the character at the given index in cstring, **must check bounds and throw exception
    bool empty(); // return true if cstr is nullptr or size 1 with '\0'
    void clear(); // sets cstring to nullptr or '\0' and size to 0?
    size_t size() const; // return and unsigned integer of size of cstr
    //size_t find(const MyString& string); // return the first inex of start of inputted string
    size_t find(const MyString& string, size_t position=0) const;
    size_t length() const;



    MyString& operator= (const MyString&); // copy assignment
    MyString& operator+= (const MyString& string) ;// for the += operator??

    friend bool operator == (const MyString &, const MyString &);
    friend MyString operator+ (const MyString& lhs, const MyString& rhs);
    friend ostream& operator<< (std::ostream& output, const MyString& string);

};

//std::ostream& operator<< (std::ostream& output, const MyString& string);




#endif