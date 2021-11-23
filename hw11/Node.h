#ifndef NODE
#define NODE

#include "CellData.h"

class Node 
{
    public:
    CellData data;
    Node* next;

    // Default constructor
    Node(); // remember to initialize next to nullptr
    Node(std::string id, int fov, double volume, double center_x, double center_y, double min_x, double max_x, double min_y, double max_y);
    
    /* The following two functions will allow you to just ask if a node is smaller than or equal to
     * another rather than looking at all of cell id and fov information implement if needed.
     * We will not test these two funcitons
     */ 
//    bool operator<(const Node& b);
//    bool operator==(const Node& b);
   
   // The function below is written. Do not modify it
	  virtual ~Node() {}
};

#endif
