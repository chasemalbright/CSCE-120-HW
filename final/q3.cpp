#include <iostream>

using namespace std;


// inserting a list into another list after a given character
void insert(char afterLetter, LinkedList& insertList){
    
    //insatntiate a helper pointer to hold val of curr item while traversing the list
    Node* curr = head;
    
    // while loop to find the instance of the letter in a node
    //***if the match is found, the loop will terminate and we insert after the curr node
    while(afterLetter != curr->letter){
        
        //if we reach end of list and match not found, or the letter is not in the list, we found the tail
        // and we insert at the end of the list
        if (curr->next == nullptr){
            break; // break before assigning curr to curr->next to avoid sigfault
        }
        
        //if logic above not satisfied we must travesre to next item
        curr = curr->next;
    }
    
    //for case where match is last item or match not found
    //check if last item just to be safe see if it next is nullptr
    if (curr->next == nullptr){
        // tail->next points to newlisthead and newlistprev points to oldlisttail
        curr->next = insertList->head;
        insertList->head->prev = curr;
        return;
    }
    
    // case where we insert into middle
    // find the newlist tail first 
    
    Node* newlisttail = insertList.head;
    while (newlisttail != nullptr){
        newlisttail= newlisttail->next;
    }
    
    //we found the newlist Tail 
    //newlist tail next now points to curr next
    //set currnext prev to newlisttail
    newlisttail = curr->next;
    curr->next->prev = newlisttail;
    
    //now take care of the next two steps at front of the insertion
    //newlisthead prev points to curr
    // curr next points to newlisthead
    insertList->head->prev = curr;
    curr->next  = insertList->head;
    
}