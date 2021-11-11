// Class file for Database class

#include "Database.h"

using std::string, std::vector;

// Constructor
// Constructor for Database class
// TODO(student): implement constructor using member initializer list
Database::Database():stateParkList({}), camperList({}){}
// Destructor
// DO NOT CHANGE, ALREADY IMPLEMENTED
Database::~Database() {
	for (unsigned int i = 0; i < stateParkList.size(); ++i) {
		delete stateParkList.at(i);
	}
	
	for (unsigned int i = 0; i < camperList.size(); ++i) {
		delete camperList.at(i);
	}
}

// Mandatory
// Dynamically creates a new state park and adds it to stateParkList
void Database::addStatePark(string parkName, double entranceFee, double trailMiles) {
	INFO(parkName)
	INFO(entranceFee)
	INFO(trailMiles)
	// TODO(student): implement function
	StatePark* park = new StatePark(parkName, entranceFee, trailMiles);
	stateParkList.push_back(park);
}

// Mandatory
// Dynamically creates a new passport and adds it to camperList
void Database::addPassport(string camperName, bool isJuniorPassport) {
	INFO(camperName)
	INFO(isJuniorPassport)
	Passport * passport = new Passport(camperName, isJuniorPassport);
	camperList.push_back(passport);
}

// Mandatory
// Searches for a passport and state park whose name matches the given parameters and
// adds the park to the passport
void Database::addParkToPassport(string camperName, string parkName) {
	INFO(camperName)
	INFO(parkName)
	bool park = false;
	bool camp = false;
	int index1;
	int index2;
	for (long unsigned int i =0; i < camperList.size(); i++){
		if (camperList.at(i)->getCamperName()==camperName){
			camp = true;
			index1 = i;
		}
	}

	for (long unsigned int j =0; j < stateParkList.size(); j++){
		if (stateParkList.at(j)->getParkName() == parkName){
			park = true;
			index2 = j;
		}
	}
	if (park&&camp){
		camperList.at(index1)->addParkVisited(stateParkList.at(index2));
	}
}

// Option A
// Returns a vector of the names of all the parks whose revenue is between the parameters
// given (including the boundaries)
vector<string> Database::getParksInRevenueRange(double lowerBound, double upperBound) {
	INFO(lowerBound)
	INFO(upperBound)
	// TODO(student): implement function
	return {};
}

// Option B
// Returns a vector of the names of all the campers who have reached at least the hiking
// level given by the parameter
vector<string> Database::getHikersAtLeastLevel(int level) {
	INFO(level)
	// TODO(student): implement function
	return {};
}