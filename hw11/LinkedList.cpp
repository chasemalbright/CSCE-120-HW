#include <iostream>
#include <string>
#include <sstream>
#include "LinkedList.h"
#include "Node.h"
#include <cmath>

using std::cout;
using std::string;
using std::ostream;
using std::swap;

LinkedList::LinkedList(): head(nullptr), tail(nullptr) {
}

LinkedList::~LinkedList() {
    clear();
}

LinkedList::LinkedList(const LinkedList& source): head(nullptr), tail(nullptr) {
    // Implement this function
    Node* curr = source.head;
    while (curr != nullptr){
        insert(curr->data.id,curr->data.fov,curr->data.volume,curr->data.center_x,curr->data.center_y,curr->data.min_x,curr->data.max_x,curr->data.min_y,curr->data.max_y);
        curr = curr->next;
    }

}

LinkedList& LinkedList::operator=(const LinkedList& source) 
{
    if (this != &source){
        clear();
        Node* curr = source.head;
        while (curr != nullptr){
            insert(curr->data.id,curr->data.fov,curr->data.volume,curr->data.center_x,curr->data.center_y,curr->data.min_x,curr->data.max_x,curr->data.min_y,curr->data.max_y);
            curr = curr->next;
        }
    }
    return *this;
}

void LinkedList::insert(std::string id, int fov, double volume, double center_x, double center_y, double min_x, double max_x, double min_y, double max_y)
{
    //create new node with information in parameters
    Node* nodeToInsert = new Node(id,fov,volume,center_x,center_y,min_x,max_x,min_y,max_y);

    //case where list is empty
    if (head == nullptr && tail == nullptr){
        head = nodeToInsert;
        tail = nodeToInsert;
        return;
    }

    //case for inserting at the end of the list
    if (tail->data < nodeToInsert->data || tail->data == nodeToInsert->data){
        //if NTI is greater than last element insert at end of list
        //update current tail to point to NTI
        tail->next = nodeToInsert;
        // update tail to be NTI
        tail = nodeToInsert;
        tail->next = nullptr; // added
        return;
    }

    //case for inserting at the beginning of the list
    // [1]
    //  |
    // ___->[2]->[3]->[4]
    
    if (nodeToInsert->data < head->data || nodeToInsert->data == head->data){
        // set NTI to point to the old head
        nodeToInsert->next = head; 
        // set head to NTI
        head = nodeToInsert;
        return;
    }

    //regular cases requires traversal
    // Node nodeToInsert = newly created node // our new element being used to compare

    // since we already took care of cases insert at beginning end, and an empty list we must start 
    // this last method at by looking at the first two elements in list
    Node* curr = head; // second element in list
    Node* prev = head; // helper pointer to hold previous node ptr
    //or nullptr

    // need to start with the first & second node in LinkedList and traverse till 
    // nodeToInsert is between two values
    //            nodeToInsert = [25]
    //                           a=prev  |     b=curr
    // linkedlist => [12]->[13]->[17]->_____->[30]->[32]
    //                 p     c
    // find where (NTI < a)=>false and (NTI < b)=>true
    //be sure to update pointers and special cases for inserting at head and tail
    
    while (curr->data < nodeToInsert->data){
        // move to next list elements
        prev = curr; 
        curr = curr->next;
        //std::cout<< "while loop" << std::endl;
    }
    prev->next = nodeToInsert;
    nodeToInsert->next = curr; // update NTI.next to point to curr

    return;
    //////////////////////////////////////////////////////
    //     while (curr->next != nullptr){
    //     //find where (a < NTI)=>true and (NTI < b)=>true
    //     if (prev->data < nodeToInsert->data && nodeToInsert->data < curr->data){
    //         nodeToInsert->next = curr; // update NTI.next to point to curr
    //         prev->next = nodeToInsert;// update prev to point to NTI
    //         return;
    //     }
    //     // move to next list elements
    //     prev = curr; 
    //     curr = curr->next;
    // }
}

void LinkedList::remove(std::string id, int fov, double volume, double center_x, double center_y, double min_x, double max_x, double min_y, double max_y)
{
    Node* nodeToRemove = new Node(id,fov,volume,center_x,center_y,min_x,max_x,min_y,max_y);

    // removing the first item in the list
    if (nodeToRemove->data == head->data){
        // for 1 item in list
         if (head->next == nullptr){
             delete head;
             delete nodeToRemove;
             tail = nullptr;
             head = nullptr;
             return;
         }

         // delete first item

         // hold the pointer to head.next
         head = head->next;
         delete nodeToRemove;
         return;
    }

    // normal deletion process
    Node* curr = head;
    Node* prev = head;

    while (curr->next != nullptr){
        if (curr->data == nodeToRemove->data){
            if (curr == tail){
                prev->next = nullptr;
                tail = prev;
                delete nodeToRemove;
                return;
            }
            break;
        }
        prev = curr; 
        curr = curr->next;
    }

    prev->next = curr->next;
    curr = prev;
    delete nodeToRemove;
    return;

}

void LinkedList::clear() 
{	
    while(head != nullptr){
        Node* delNode = head;
        head = head->next;
        delete delNode;
    }
    head = nullptr;
    tail = nullptr;
}

Node* LinkedList::getHead() const 
{
    return head;
}

string LinkedList::print() const 
{
    std::stringstream ss;

    ss << "fov" << "," << "volume" << "," << "center_x" << "," << "center_y" << "," << "min_x" << "," << "max_x" << "," << "min_y" << "," << "max_y" << std::endl;
   	 
    Node* curr = head;
    while (curr != nullptr){
        ss << curr->data.id << ","<< curr->data.fov << "," << curr->data.volume << "," << curr->data.center_x << "," << curr->data.center_y << "," << curr->data.min_x << "," << curr->data.max_x << "," << curr->data.min_y << "," << curr->data.max_y << std::endl;
        curr = curr->next;
    }

    return ss.str();
}

ostream& operator<<(ostream& os, const LinkedList& ll) {
	/* Do not modify this function */
	os << ll.print();
	return os;
}

// given a fov number, count the cells observed in that fov
int LinkedList::countN(int fov)
{
	/* Do not modify this function */
    int count = 0;
    Node* cur = head;
    while (cur)
    {
        if (cur->data.fov == fov)
            count++;
        cur = cur->next;
    }
    return count;
}

/* given a fov number, compute the average volume of all the cells observed in
 * that fov
 */
double LinkedList::average(int fov){



    Node* cur = head;
    int count = countN(fov);
    double total = 0.0;
    while (cur)
    {
        if (cur->data.fov == fov)
            total = total+cur->data.volume;
        cur = cur->next;
    }

    return static_cast<double>(total)/count;
}

/* given a fov number, compute the variance volume of all the cells observed in
 * that fov
 */
double LinkedList::variance(int fov)
{
	/* Do not modify this function */
    double sum = 0;
    double avg = average(fov);
    int count = countN(fov);

    if (count == 0)
        return -1;

    Node* cur = head;
    while (cur)
    {
        if (fov == cur->data.fov)
            sum += (cur->data.volume - avg) * (cur->data.volume - avg);
        cur = cur->next;
    }

    return sum/count;
}

/* given a fov number, remove outliers
 *///                            k       j      N
string LinkedList::outliers(int fov, int k, int N)
{
    if (countN(fov) < N){
        return "Less than "+ std::to_string(N)+ " cells in fov "+ std::to_string(fov);
    }
    double low = average(fov) - (k* sqrt(variance(fov)));
    double high = average(fov) + (k* sqrt(variance(fov)));

    Node* cur = head;
    int count = 0;
    while (cur){
        if (cur->data.volume <= low || cur->data.volume >= high){
            remove(cur->data.id,cur->data.fov,cur->data.volume,cur->data.center_x,cur->data.center_y,cur->data.min_x,cur->data.max_x,cur->data.min_y,cur->data.max_y);
            count++;
        }
        cur = cur->next;
    }
    string x = std::to_string(count) + " cells are removed.";
    return x;
}

