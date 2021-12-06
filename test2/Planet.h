#ifndef PLANET_H
#define PLANET_H

#include<string>

class Planet{
    private:
        std::string name;
        double distanceFromSun;
        bool isGaseous;
    public:
        Planet(std::string text,double distance,bool isgaseous);
        double getDistanceFromSun();
        bool getIsGaseous();
}

#endif