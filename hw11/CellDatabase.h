#ifndef CELL_DB
#define CELL_DB

#include <string>
#include "LinkedList.h"

class CellDatabase {
public:
	CellDatabase();
	~CellDatabase();

	// The two functions below are required

	// Read the cell records from the data file and populate the linked list
	void loadData(const std::string& filename);

		
	// Output the data as ordered in the linked list
	void outputData(const std::string& filename);

	// Read the queries from the query file and perform a series of queries
	void performQuery(const std::string& query_filename);

private:
	// Linked list to store the temperature records. You need to properly populate
	// this link list.
	LinkedList records;

	// You can add any private member variables/functions you feel useful in this class.
};

#endif  // CELL_DB
