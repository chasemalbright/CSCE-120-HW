#include <iostream>
#include <cassert>

using std::cout, std::endl;

class Thing {
    int* value;

    public:
        Thing(int the_value) : value(nullptr) {
            value = new int[1];
            value[0] = the_value;
        }

        // put required methods in here
        

        //destructor
        ~Thing(){
            delete [] value;
        }

        //copy constructor
        Thing(const Thing& thingToCopy){
            // need to copy over the dynamic array of ints
            delete[] value; // delete old array and val
            value = new int[1]; // initialize new arr
            value[0] = thingToCopy.value[0]; // copy over the val
        }

        // copy assignment
        Thing& operator=(const Thing& thingToCopy){
            if (this == &thingToCopy){ // if equiavalent just return obj
                return *this;
            }

            delete[] value; // delete old array and val
            value = new int[1]; // initialize new arr
            value[0] = thingToCopy.value[0]; // copy over the val
            return *this; 
        }


        void up() { value[0]++; }

        bool operator==(int rhs) { return value[0]== rhs; }
};


int main() {
    Thing t(8);
    Thing t2(t);

    assert(t==8);
    assert(t2==8);

    t.up();

    assert(t==9);
    assert(t2==8);

    t2 = t;

    assert(t==9);
    assert(t2==9);

    t2.up();

    assert(t==9);
    assert(t2==10);

    return 0;
    
}