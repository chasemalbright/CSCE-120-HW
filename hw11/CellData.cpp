/*
 * CellData.h
 *
 *  Created on: Nov 9, 2021
 *      Author: student
 */

#include <iostream>
#include <string>
#include "CellData.h"

using std::cout;
using std::string;

int charToInt(char x){
    switch(x){
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
    }
    return 1111;
}

CellData::CellData(): id("-1"),fov(-1),volume(-1),center_x(-1),center_y(-1), min_x(-1),min_y(-1),max_x(-1), max_y(-1) {} //initialize everything

CellData::CellData(std::string id, int fov, double volume, double center_x, double center_y, double min_x, double max_x, double min_y, double max_y):id(id),fov(fov),volume(volume),center_x(center_x),center_y(center_y), min_x(min_x),min_y(min_y), max_x(max_x),max_y(max_y) {} //initialize everything


CellData::~CellData() {} // You should not need to implement this

bool CellData::operator<(const CellData& b) {
	if (b.fov == this->fov){

        if (this->id.size() < b.id.size()){
            return true;
        } else if (this->id.size() > b.id.size()) {
            return false;
        } else {
            // if magnitudes are equal must compare each digit
            for (long unsigned int i = 0; i < this->id.size(); i++){
                int mem = charToInt(this->id[i]);
                int oth = charToInt(b.id[i]);
                if ( mem > oth ){
                    return false;
                } else if (mem < oth){
                    return true;
                }
            }
            return true;
            
        }


    } else {
        if (this->fov < b.fov){
            return true;
        } else {
            return false;
        }
    }
}

bool CellData::operator==(const CellData& b)
{
    if (this->fov != b.fov){ return false;}
    if (this->volume != b.volume){ return false;}
    if (this->center_x != b.center_x){ return false;}
    if (this->center_y != b.center_y){ return false;}
    if (this->min_x != b.min_x){ return false;}
    if (this->max_x != b.max_x){ return false;}
    if (this->min_y != b.min_y){ return false;}
    if (this->max_y != b.max_y){ return false;}
    return true;
}

