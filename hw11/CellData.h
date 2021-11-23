/*
 * CellData.h
 *
 *  Created on: Nov 9, 2021
 *      Author: student
 */

#ifndef CELLDATA
#define CELLDATA
#include <string>

class CellData {
    public:
    std::string id;
    int fov;
    double volume;
    double center_x;
    double center_y;
    double min_x;
    double min_y;
    double max_x;
    double max_y;

    CellData();
    CellData(std::string id, int fov, double volume, double center_x, double center_y, double min_x, double max_x, double min_y, double max_y);
    virtual ~CellData();
    bool operator<(const CellData& b);
    bool operator==(const CellData& b);
};

#endif /* CELLDATA */
