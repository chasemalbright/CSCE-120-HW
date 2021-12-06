#include <iostream>
#include "CellDatabase.h"

using std::endl;
using std::cout;

int main(int argc, char** argv) 
{
    if (argc < 3) 
    {
        cout << "Usage: " << argv[0] << " data_file query_file" << endl;
		    return 1;
    } 
    else 
    {
        CellDatabase database;
        database.loadData(argv[1]);
		    database.performQuery(argv[2]); 
	  	  database.outputData(argv[1]); 
    }

    return 0;
}