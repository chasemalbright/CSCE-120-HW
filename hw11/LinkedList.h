#ifndef LINKEDLIST
#define LINKEDLIST

#include <iostream>
#include <string>
#include "Node.h"

class LinkedList {
private:
	Node* head;
	Node* tail;

public:
	// Default constructor
	LinkedList();

	// Destructor
	~LinkedList();

	// Copy constructor
	LinkedList(const LinkedList& other);

	// Copy assignment
	LinkedList& operator=(const LinkedList& other);

	// Insert a record to the linked list
  void insert(std::string id, int fov, double volume, double center_x, double center_y, double min_x, double max_x, double min_y, double max_y);

  // Delete a record from the linked list

  void remove(std::string id, int fov, double volume, double center_x, double center_y, double min_x, double max_x, double min_y, double max_y);

	// Clear the content of this linked list
	void clear();

  // given a fov number, count the cells observed in that fov
  int countN(int fov);

  /* given a fov number, compute the average volume of all the cells observed in
   * that fov
   */
  double average(int fov);

  /* given a fov number, compute the variance volume of all the cells observed in
   * that fov
   */
  double variance(int fov);

  /* given a fov number, remove outliers
   */
  std::string outliers(int fov, int k, int N);
  

	// The functions below are written already. Do not modify them.
	std::string print() const;

	Node* getHead() const;
};

std::ostream& operator<<(std::ostream& os, const LinkedList& ll);
#endif
