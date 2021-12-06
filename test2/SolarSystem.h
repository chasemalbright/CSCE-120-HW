#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H

#include<string>
#include <vector>
#inlcude "Planet.h"

class SolarSystem{
    private:
        std::string name;
        std::vector<Planet*> planets;
    public:
        SolarSystem(std::string text);
        std::string getName();
        void addPlanet(const Planet& newPlanet);
};

#endif