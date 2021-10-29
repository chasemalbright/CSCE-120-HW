#include <iostream>
#include <string>
#include "logic.h"

using std::cout, std::endl, std::string;

// void deallocate(char**& map, int maxRow){
//     for (int i = 0; i < maxRow; ++i)
//         {
//             delete[] map[i];
//         }
//         delete[] map;
//         map = nullptr;
// }

// TODO(student): Write unit tests for the functions in logic.h
//                You should end up with at least 500 lines of test code

void testLoadLevel_noReturn(string fileName){
    int maxRow;
    int maxCol;
    Player player;

    char** map = loadLevel(fileName, maxRow, maxCol, player);
    if (map != nullptr){
        deleteMap(map, maxRow);
    }
}

bool test_loadLevel(){
    bool pass = true;  

    {
        // test for player position

        int maxRow = 5;
        int maxCol = 3;

        Player p1;
        p1.row = 0;
        p1.col = 0;
        p1.treasure = 0;


        char** map = loadLevel("example.txt",maxRow,maxCol,p1);

        if (map[0][0] != 'o'){
            pass = false;
        }

        // deallocate memory
        if (map != nullptr){
            deleteMap(map, maxRow);
        }
        

    }
    {
        // test for player position

        int maxRow = 5;
        int maxCol = 3;

        Player p1;
        p1.row = 0;
        p1.col = 0;
        p1.treasure = 0;


        char** map = loadLevel("missing.txt",maxRow,maxCol,p1);

        if (map != nullptr){
            pass = false;
            deleteMap(map, maxRow);
        }
    }
    {
        // test for player position

        int maxRow = 5;
        int maxCol = 3;

        Player p1;
        p1.row = 0;
        p1.col = 0;
        p1.treasure = 0;


        char** map = loadLevel("weird.txt",maxRow,maxCol,p1);

        
        if (map != nullptr){
            if (map[0][0] != '@'){
                pass = false;
            }
            deleteMap(map, maxRow);
        }
    }
    return pass;
}


bool test_getDirection(){
    bool pass = true;
    {
        int nextRow = 1;
        int nextCol = 1;

        char input = 'q';

        getDirection(input, nextRow, nextCol);

        if (nextRow != 1 && nextCol != 1){
            pass = false;
        }
    }
    
    {
        int nextRow = 1;
        int nextCol = 1;

        char input = 'e';

        getDirection(input, nextRow, nextCol);

        if (nextRow != 1 && nextCol != 1){
            pass = false;
        }
    }

    {
        int nextRow = 1;
        int nextCol = 1;

        char input = 'w';

        getDirection(input, nextRow, nextCol);

        if (nextRow != 0 && nextCol != 1){
            pass = false;
        }
    }
    {
        int nextRow = 1;
        int nextCol = 1;

        char input = 'a';

        getDirection(input, nextRow, nextCol);

        if (nextRow != 1 && nextCol != 0){
            pass = false;
        }
    }
    {
        int nextRow = 1;
        int nextCol = 1;

        char input = 's';

        getDirection(input, nextRow, nextCol);

        if (nextRow != 2 && nextCol != 1){
            pass = false;
        }
    }
    {
        int nextRow = 1;
        int nextCol = 1;

        char input = 'd';

        getDirection(input, nextRow, nextCol);

        if (nextRow != 1 && nextCol != 2){
            pass = false;
        }
    }
    return pass;
}

bool test_deleteMap(){
    bool pass = true;
    {
        int maxRow = 5;
        int maxCol = 3;

        Player p1;
        p1.row = 0;
        p1.col = 0;
        p1.treasure = 0;


        char** map = loadLevel("example.txt",maxRow,maxCol,p1);

        // deallocate memory
        if (map != nullptr){
            deleteMap(map, maxRow);
        }

    }
    return pass;


}

bool test_resizeMap(){
    bool pass = true;
    {
        int maxRow = 3;
        int maxCol = 3;

        Player p1;
        p1.row = 1;
        p1.col = 1;
        p1.treasure = 0;

        char** map = loadLevel("example2.txt", maxRow, maxCol, p1);
        // issues with resizing
        map = resizeMap(map, maxRow, maxCol);



        if (map != nullptr){
            if (maxRow != 6){
                pass = false;
            }
            if (maxCol != 6){
                pass = false;
            }
            deleteMap(map, maxRow);
        }
    }
    {
        int maxRow = 3;
        int maxCol = 3;

        Player p1;
        p1.row = 1;
        p1.col = 1;
        p1.treasure = 0;

        char** map = loadLevel("example2.txt", maxRow, maxCol, p1);

        map = resizeMap(map, maxRow, maxCol);

        if (map != nullptr){
            if (maxCol != 6){
                pass = false;
            }
            deleteMap(map, maxRow);
        }
    }

    {
        int maxRow = 3;
        int maxCol = 3;

        Player p1;
        p1.row = 0;
        p1.col = 0;
        p1.treasure = 0;

        char** map = loadLevel("example2.txt", maxRow, maxCol, p1);

        map = resizeMap(map, maxRow, maxCol);


        if (map != nullptr){
            if (map[1][1] != 'o'){
                pass = false;
            }
            if (map[1][1] != 'o'){
                pass = false;
            }
            deleteMap(map, maxRow);
        }
    }
    {
        int maxRow = 3;
        int maxCol = 3;

        Player p1;
        p1.row = 0;
        p1.col = 0;
        p1.treasure = 0;

        char** map =loadLevel("example2.txt", maxRow, maxCol, p1);

        map = resizeMap(map, maxRow, maxCol);

        if (map != nullptr){
            if (map[4][1] == 'o' || map[4][4] == 'o' || map[1][4] == 'o'){
                pass = false;
            }
            deleteMap(map, maxRow);
        }
    }
    return pass;
}

bool test_doPlayerMove(){
    bool pass = true;
    {
        int maxRow = 3;
        int maxCol = 3;

        int nextRow = 0;
        int nextCol = 0;

        Player p1;
        p1.row = 0;
        p1.col = 0;
        p1.treasure = 0;

        char** map =loadLevel("stay.txt", maxRow, maxCol, p1);


        if (map != nullptr){
            int value = doPlayerMove(map, maxRow, maxCol, p1, nextRow, nextCol);

            if (value != 0){
                pass = false;
            }
            deleteMap(map, maxRow);
        }
    }
    {
        int maxRow = 3;
        int maxCol = 3;

        int nextRow = -1;
        int nextCol = 0;

        Player p1;
        p1.row = 0;
        p1.col = 0;
        p1.treasure = 0;

        char** map =loadLevel("stay.txt", maxRow, maxCol, p1);

        if (map != nullptr){
            int value = doPlayerMove(map, maxRow, maxCol, p1, nextRow, nextCol);

            if (value != 0){
                pass = false;
            }

            deleteMap(map, maxRow);
        }
    }
    {
        int maxRow = 3;
        int maxCol = 3;

        int nextRow = 0;
        int nextCol = -1;

        Player p1;
        p1.row = 0;
        p1.col = 0;
        p1.treasure = 0;

        char** map =loadLevel("stay.txt", maxRow, maxCol, p1);


        if (map != nullptr){
            int value = doPlayerMove(map, maxRow, maxCol, p1, nextRow, nextCol);

            if (value != 0){
                pass = false;
            }

            deleteMap(map, maxRow);
        }
    }
    {
        int maxRow = 3;
        int maxCol = 3;

        int nextRow = 3;
        int nextCol = 3;

        Player p1;
        p1.row = 2;
        p1.col = 2;
        p1.treasure = 0;

        char** map =loadLevel("stay2.txt", maxRow, maxCol, p1);

        
        if (map != nullptr){
            int value = doPlayerMove(map, maxRow, maxCol, p1, nextRow, nextCol);

            if (value != STATUS_STAY){
                pass = false;
            }

            deleteMap(map, maxRow);
        }
    }
    {
        int maxRow = 3;
        int maxCol = 3;

        int nextRow = 2;
        int nextCol = 1;

        Player p1;
        p1.row = 1;
        p1.col = 1;
        p1.treasure = 0;

        char** map =loadLevel("move1.txt", maxRow, maxCol, p1);

        if (map != nullptr){
            int value = doPlayerMove(map, maxRow, maxCol, p1, nextRow, nextCol);

            if (value != STATUS_MOVE){
                pass = false;
            }
            deleteMap(map, maxRow);
        }
    }
    {
        int maxRow = 3;
        int maxCol = 3;

        int nextRow = 1;
        int nextCol = 2;

        Player p1;
        p1.row = 1;
        p1.col = 1;
        p1.treasure = 0;

        char** map =loadLevel("move1.txt", maxRow, maxCol, p1);


        if (map != nullptr){

            int value = doPlayerMove(map, maxRow, maxCol, p1, nextRow, nextCol);

            if (value != STATUS_MOVE){
                pass = false;
            }

            deleteMap(map, maxRow);
        }
    }
    {
        int maxRow = 3;
        int maxCol = 3;

        int nextRow = 1;
        int nextCol = 2;

        Player p1;
        p1.row = 1;
        p1.col = 1;
        p1.treasure = 0;

        char** map =loadLevel("treasure.txt", maxRow, maxCol, p1);

        if (map != nullptr){
            int value = doPlayerMove(map, maxRow, maxCol, p1, nextRow, nextCol);

            if (value != STATUS_TREASURE && p1.treasure != 1){
                pass = false;
            }

            deleteMap(map, maxRow);
        }
    }
    {
        int maxRow = 3;
        int maxCol = 3;

        int nextRow = 1;
        int nextCol = 2;

        Player p1;
        p1.row = 1;
        p1.col = 1;
        p1.treasure = 1;

        char** map =loadLevel("leave.txt", maxRow, maxCol, p1);

        
        
        if (map != nullptr){
            int value = doPlayerMove(map, maxRow, maxCol, p1, nextRow, nextCol);

            if (value != STATUS_LEAVE){
                pass = false;
            }

            deleteMap(map, maxRow);
        }
    }
    {
        int maxRow = 3;
        int maxCol = 3;

        int nextRow = 1;
        int nextCol = 2;

        Player p1;
        p1.row = 1;
        p1.col = 1;
        p1.treasure = 0;

        char** map =loadLevel("leave.txt", maxRow, maxCol, p1);

        if (map != nullptr){
            int value = doPlayerMove(map, maxRow, maxCol, p1, nextRow, nextCol);

            if (value == STATUS_LEAVE){
                pass = false;
            }
            deleteMap(map, maxRow);
        }
    }
    {
        int maxRow = 3;
        int maxCol = 3;

        int nextRow = 1;
        int nextCol = 2;

        Player p1;
        p1.row = 1;
        p1.col = 1;
        p1.treasure = 0;

        char** map =loadLevel("escape.txt", maxRow, maxCol, p1);

        
        if (map != nullptr){
            int value = doPlayerMove(map, maxRow, maxCol, p1, nextRow, nextCol);

            if (value != STATUS_ESCAPE){
                pass = false;
            }
            deleteMap(map, maxRow);
        }
    }
    {
        int maxRow = 3;
        int maxCol = 3;


        int nextRow = 1;
        int nextCol = 2;

        Player p1;
        p1.row = 1;
        p1.col = 1;
        p1.treasure = 0;

        char** map =loadLevel("monster.txt", maxRow, maxCol, p1);

    
        if (map != nullptr){

            int value = doPlayerMove(map, maxRow, maxCol, p1, nextRow, nextCol);

            if (value != STATUS_STAY){
                pass = false;
            }

            deleteMap(map, maxRow);
        }
    }
    {
        int maxRow = 3;
        int maxCol = 3;


        int nextRow = 1;
        int nextCol = 2;

        Player p1;
        p1.row = 1;
        p1.col = 1;
        p1.treasure = 0;

        char** map =loadLevel("pillar.txt", maxRow, maxCol, p1);

        
        if (map != nullptr){
            int value = doPlayerMove(map, maxRow, maxCol, p1, nextRow, nextCol);

            if (value != STATUS_STAY){
                pass = false;
            }


            deleteMap(map, maxRow);
        }
    }
    {
        int maxRow = 3;
        int maxCol = 3;


        int nextRow = 1;
        int nextCol = 2;

        Player p1;
        p1.row = 1;
        p1.col = 1;
        p1.treasure = 0;

        char** map =loadLevel("money.txt", maxRow, maxCol, p1);

        if (map != nullptr){

            int value = doPlayerMove(map, maxRow, maxCol, p1, nextRow, nextCol);

            if (value != STATUS_MOVE){
                pass = false;
            }
            deleteMap(map, maxRow);
        }
    }
    {
        int maxRow = 3;
        int maxCol = 3;


        int nextRow = 1;
        int nextCol = 2;

        Player p1;
        p1.row = 1;
        p1.col = 1;
        p1.treasure = 0;

        char** map =loadLevel("at.txt", maxRow, maxCol, p1);

        
        if (map != nullptr){
            int value = doPlayerMove(map, maxRow, maxCol, p1, nextRow, nextCol);

            if (value != STATUS_MOVE){
                pass = false;
            }
            deleteMap(map, maxRow);
        }
    }
    {
        int maxRow = 3;
        int maxCol = 3;


        int nextRow = 1;
        int nextCol = 2;

        Player p1;
        p1.row = 1;
        p1.col = 1;
        p1.treasure = 0;

        char** map =loadLevel("at.txt", maxRow, maxCol, p1);
        if (map != nullptr){
            int value = doPlayerMove(map, maxRow, maxCol, p1, nextRow, nextCol);
            if (p1.row != 1 || p1.col != 2){
                pass = false;
            }
            if (value != STATUS_MOVE){
                pass = false;
            }

            if (map[2][1] != TILE_PLAYER){
                pass = false;
            }


            deleteMap(map, maxRow);
        }
    }
    return pass;
}

void test_doMonsterAttack(string fileName){
    int maxRow;
    int maxCol;
    Player player;
    // player.col = 0;
    // player.row = 2;
    // player.treasure = 1;
    
    char** map = loadLevel(fileName, maxRow, maxCol, player);

    bool monster;

    //monster = doMonsterAttack(map, maxRow, maxCol, player);

    if (map != nullptr){
        monster = doMonsterAttack(map, maxRow, maxCol, player);
        deleteMap(map, maxRow);
    }
}

int main() {

    cout <<"loadlevel pass? " << test_loadLevel() << endl;
    cout <<"get direction pass? " << test_getDirection() << endl;
    cout <<"delete map pass? " << test_deleteMap() << endl;
    cout << "resize map pass? " << test_resizeMap() << endl;
    cout << "player move pass? " << test_doPlayerMove() << endl;


    testLoadLevel_noReturn("example.txt");
    testLoadLevel_noReturn("load2.txt");
    testLoadLevel_noReturn("load3.txt");
    testLoadLevel_noReturn("load4.txt");
    testLoadLevel_noReturn("missing.txt");



 
    test_doMonsterAttack("monster1.txt");
    test_doMonsterAttack("monster2.txt");
    test_doMonsterAttack("monster3.txt");
    test_doMonsterAttack("monster4.txt");
    
    return 0;
}