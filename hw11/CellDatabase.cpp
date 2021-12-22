#include <iostream>
#include <string>
#include <sstream>
#include "CellDatabase.h"
#include "CellData.h"
#include <fstream>

using std::cout;
using std::string;
using std::ifstream;
using std::fstream;
using std::ofstream;
using std::endl;

// Default constructor/destructor. Modify them if you need to.
CellDatabase::CellDatabase() {}
CellDatabase::~CellDatabase() {}

bool isDouble(const string& s)
{
    int nb_point=0;
    for (int i=0; i<s.length();i++)
    {
         if (s[i]=='.'){
              nb_point++;
         } else if (!isdigit(s[i])){
              return false;
         }
    }
    if (nb_point==1 )
    {
          return true;
    }
    else
    {
          return false;
    }
}

bool isInt(const string& s)
{
    int nb_point=0;
    for (int i=0; i<s.length();i++)
    {
         if (s[i]=='.'){
              nb_point++;
         } else if (!isdigit(s[i])){
              return false;
         }
    }
    if (nb_point==0)
    {
          return true;
    }
    else
    {
          return false;
    }
}



void CellDatabase::loadData(const string& filename) 
{
    //if file cant be opened return
    std::ifstream ifs = ifstream(filename);
    if (!ifs.is_open()){
        cout << "Error: Unable to open";
        return; 
    }

    string data;
    int lineCounter = 0;
    int indexArray[9]={0,0,0,0,0,0,0,0,0};

    while (getline(ifs,data)){
        if (lineCounter >= 1){ // dont read in the first line

            int commaCount = 0;

            for (unsigned int i = 0; i < data.size(); i++){
                if (data[i] == ','){
                    indexArray[commaCount] = i;
                    commaCount++;
                }
		    }

            string id ="x";
            string fov = "x";
            string volume = "x";
            string center_x = "x";
            string center_y = "x";
            string min_x = "x";
            string min_y = "x";
            string max_x = "x";
            string max_y = "x";

            // only if there are 8 commas

            if (commaCount == 8){
                id = data.substr(0,indexArray[0]);
                fov = data.substr(indexArray[0]+1, indexArray[1] - indexArray[0]-1);
                volume = data.substr(indexArray[1]+1, indexArray[2] - indexArray[1]-1);
                center_x = data.substr(indexArray[2]+1, indexArray[3] - indexArray[2]-1);
                center_y = data.substr(indexArray[3]+1, indexArray[4] - indexArray[3]-1);
                min_x = data.substr(indexArray[4]+1, indexArray[5] - indexArray[4]-1);
                max_x = data.substr(indexArray[5]+1, indexArray[6] - indexArray[5]-1);
                min_y = data.substr(indexArray[6]+1, indexArray[7] - indexArray[6]-1);
                max_y = data.substr(indexArray[7]+1, data.length()-1);

                if (isInt(id) && isInt(fov) && isDouble(volume) && isDouble(center_x) && isDouble(center_y) && isDouble(min_x) && isDouble(max_x) && isDouble(min_y) && isDouble(max_y) && std::stod(volume) >= 0){
                    records.insert(id,std::stoi(fov),std::stod(volume),std::stod(center_x),std::stod(center_y),std::stod(min_x),std::stod(max_x),std::stod(min_y),std::stod(max_y));
                }
            }
            if (commaCount != 8 || !isInt(id) || !isInt(fov) || !isDouble(volume) || !isDouble(center_x) || !isDouble(center_y) || !isDouble(min_x) || !isDouble(max_x) || !isDouble(min_y) || !isDouble(max_y) || std::stod(volume) < 0){
                cout << "Error, Invalid input: " + data << endl;
            }



        }
        lineCounter++;
    }

}

// Do not modify
void CellDatabase::outputData(const string& filename) {
    ofstream dataout("sorted." + filename);

    if (!dataout.is_open()) 
    {
        cout << "Error: Unable to open " << filename << endl;
        exit(1);
    }
    dataout << records.print();
}

bool verifyOutlier( string data ){
    if(data.substr(0,8) != "OUTLIER "){
        return false;
    }
    
    int spaceIndexAry[5]={0,0,0,0,0};
    int spaces = 0;
    
	for (unsigned int i = 0; i < data.size(); i++){
		if (data[i] == ' '){
			spaceIndexAry[spaces] = i;
			spaces++;
		}
	}
	
	if (spaces != 3 || spaceIndexAry[3] != 0){
	    return false;
	}
	
	string fov = data.substr(spaceIndexAry[0]+1, spaceIndexAry[1] - spaceIndexAry[0]-1);
	string k = data.substr(spaceIndexAry[1]+1, spaceIndexAry[2] - spaceIndexAry[1]-1);
	string N = data.substr(spaceIndexAry[2]+1, data.length()-1);
	
	if (!isInt(fov) || !isInt(k) || !isInt(N)){
	    return false;
	}
	
	return true;
	
	
}

void CellDatabase::performQuery(const string& filename) 
{
    ofstream outfile("result.data");

    std::ifstream ifs = ifstream(filename);
    if (!ifs.is_open()){
        //outfile << "Error: Unable to open";
        outfile.close();
        return;
    }

    string data;

    while (getline(ifs,data)){
        if (data.substr(0,4) == "AVG "){
            if(isInt(data.substr(4,data.length()-1))){
                double av = records.average(stoi(data.substr(4,data.length()-1)));
                outfile << "AVG " + data.substr(4,data.length()-1) + ": " + std::to_string(av) << endl;
            }
        } else if (data.substr(0,4) == "VAR "){
            if(isInt(data.substr(4,data.length()-1))){
                double var = records.variance(stoi(data.substr(4,data.length()-1)));
                outfile << "VAR " + data.substr(4,data.length()-1) + ": " + std::to_string(var) << endl;
            }
        } else if (data.substr(0,6) == "COUNT "){
            if(isInt(data.substr(6,data.length()-1))){
                int cnt = records.countN(stoi(data.substr(6,data.length()-1)));
                outfile << "COUNT " + data.substr(6,data.length()-1) + ": " + std::to_string(cnt) << endl;
            }
        } else if (verifyOutlier(data)){
            int spaceIndexAry[5]={0,0,0,0,0};
            int spaces = 0;
    
            for (unsigned int i = 0; i < data.size(); i++){
                if (data[i] == ' '){
                    spaceIndexAry[spaces] = i;
                    spaces++;
                }
            }

            string fov = data.substr(spaceIndexAry[0]+1, spaceIndexAry[1] - spaceIndexAry[0]-1);
	        string k = data.substr(spaceIndexAry[1]+1, spaceIndexAry[2] - spaceIndexAry[1]-1);
	        string N = data.substr(spaceIndexAry[2]+1, data.length()-1);

            string result = records.outliers(std::stoi(fov),std::stoi(k),std::stoi(N));

            outfile << data + ": " + result << endl;
        } else {
            outfile << "Error, Invalid input: " + data << endl;
        }

    }













    outfile.close();
}