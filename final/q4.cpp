#include <iostream>

using namespace std;


int *duplicateEvenNumbers(int *x, int count, int &newCount){
    // we want to count the number of even numbers in x array inorder to resize
    int evenCount = 0;
    for (int i = 0; i < count; i++){
        if (x[i]%2 ==0){
            evenCount++;
        }
    }
    
    //if there are no even numbers return original array, save resources
    if (evenCount == 0){
        newCount = count;
        return x;
    }
    
    // we want to create an array now with the new size
    int *newArray = new int[count+evenCount];
    
    // set newcount so we dont forget
    newCount = count+evenCount;
    
    // implement logic 
    //new array index holder
    int a = 0;
    for (int i = 0; i < count; i++){
        if (x[i]%2 == 0){ // use of a to hold projected indexes of the larger array
            newArray[a] = x[i];
            newArray[a+1] = x[i];
            a++;
            a++;
        } else {
            newArray[a] = x[i];
            a++;
        }
    }
    
    //delete old array
    delete [] x;
    
    //return new array
    return newArray;
    
    
}




int main()
{
    int count = 4;
    int newcount = 0;
    int *x = new int[4];
    x[0] = 3;
    x[1] = 4;
    x[2] = 8;
    x[3] = 5;
    
    for (int i = 0; i < count; i++){
        cout << x[i] << endl;
    }
    
    cout << endl;
    int *y = duplicateEvenNumbers(x, count, newcount);
    
    for (int i = 0; i < newcount; i++){
        cout << y[i] << endl;
    }
    
    ///////////////////////////
   ////   sameer = goat  /////
  ///////////////////////////

    return 0;
}