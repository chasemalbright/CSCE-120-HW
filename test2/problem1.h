#ifndef PROBLEM1_H
#define PROBLEM1_H

#include<string>

struct Row{
    std::string* array = new std::string[1] {};
    size_t capacity = 1;
    size_t size = 0;
};

void add_to_row(Row&,const std::string&);
std::string remove_from_row(Row&);
//Row split(Row&);

#endif