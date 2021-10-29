#include <iostream>
#include "logic.h"
#include <string>

using std::cout, std::endl;


void deallocate(char**& map, int maxRow){
    for (int i = 0; i < maxRow; ++i)
        {
            delete[] map[i];
        }
        delete[] map;
        map = nullptr;
}

void testLoadLevel_noReturn(string fileName){
    int maxRow;
    int maxCol;
    Player player;

    char** map = loadLevel(fileName, maxRow, maxCol, player);
    //deallocate(map, maxRow);
}

// TODO(student): Write unit tests for the functions in logic.h
//                You should end up with at least 500 lines of test code

int main() {


    testLoadLevel_noReturn("example.txt");
    testLoadLevel_noReturn("load2.txt");
    testLoadLevel_noReturn("load3.txt");
    testLoadLevel_noReturn("load4.txt");
    testLoadLevel_noReturn("missing.txt");
    
    // example
    /*
    example.txt
    -----------
    5 3
    3 0
    M + -
    - + -
    - + !
    - - -
    @ - $
    */
    ////////////////////
    // this is the only code _required_ to get coverage points on part 1 (test first)
    //   invocation --> coverage
    int maxRow;
    int maxCol;
    Player player;
    char** level = loadLevel("example.txt", maxRow, maxCol, player);
    ////////////////////
    
    ////////////////////
    // this is optional but STRONGLY recommended for preparing for part 2 (development)
    //   coverage -/-> correctness
    // note: there are _many_ ways to do this part, including ways that are more elegant and efficient than this way demonstrated here
    
    ////////////////////
    
    ////////////////////
    // this is required to prevent memory leaks on part 1 (test first)
    if (level) {
        for (int row = 0; row < 5; row++) {
            delete[] level[row];
        }
        delete[] level;
    }
    ////////////////////
    
    return 0;
}
