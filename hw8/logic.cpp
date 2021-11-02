#include <iostream>
#include <fstream>
#include <string>
#include "logic.h"

using std::cout, std::endl, std::ifstream, std::string;


bool validateChar(char x){
    switch(x){
        case TILE_OPEN:
        case TILE_PLAYER:
        case TILE_TREASURE:
        case TILE_AMULET:
        case TILE_MONSTER:
        case TILE_PILLAR:
        case TILE_DOOR:
        case TILE_EXIT:
            return true;
        default:
            return false;
    }
}

/**
 * TODO: Student implement this function
 * Load representation of the dungeon level from file into the 2D map.
 * Calls createMap to allocate the 2D array.
 * @param   fileName    File name of dungeon level.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference to set starting position.
 * @return  pointer to 2D dynamic array representation of dungeon map with player's location., or nullptr if loading fails for any reason
 * @updates  maxRow, maxCol, player
 */
char** loadLevel(const string& fileName, int& maxRow, int& maxCol, Player& player) {

   std::ifstream ifs(fileName);

    if (!ifs.is_open()){
        return nullptr;
    }

    //validate row
    ifs >> maxRow;
    if(ifs.fail()){
        return nullptr;
    }
    if(maxRow <= 0){
        return nullptr;
    }

    // validate col
    ifs >> maxCol;
    if(ifs.fail()){
        return nullptr;
    }
    if(maxCol <= 0){
        return nullptr;
    }

    int playerRow,playerCol;


    ifs >> playerRow;
    if(ifs.fail()){
        return nullptr;
    }
    if(playerRow < 0 || playerRow >= maxRow){
        return nullptr;
    }
    player.row = playerRow;


    ifs >> playerCol;
    if(ifs.fail()){
        return nullptr;
    }
    if(playerCol < 0 || playerCol >= maxCol){
        return nullptr;
    }
    player.col = playerCol;

    if (maxRow*maxCol >= INT32_MAX){
        return nullptr;
    }

    // std::ifstream ifs(fileName);
    
    // if(!ifs.is_open()){
    //     return nullptr;
    // }

    // ifs >> maxRow >> maxCol;

    // ifs >> player.row >> player.col;


    ///////////////////////////////////////
    char** map = createMap(maxRow, maxCol);
    ///////////////////////////////////////
    
    if (map == nullptr){
        return nullptr;
    }



    // for (int col = 0; col < maxCol; col++){
    //     for (int row = 0; row < maxRow; row++){
    //         ifs >> map[row][col];
    //         if (ifs.fail() && !ifs.eof()){
    //             return nullptr;
    //         }
    //         if (!validateChar(map[row][col])){
    //             return nullptr;
    //         }
    //     }
    // }

    //map[playerRow][playerCol] = TILE_PLAYER;


    //set file contents to 2d array
    for (int row = 0; row < maxRow; row++) {
        for (int col = 0; col < maxCol; col++) {
            ifs >> map[row][col];
            if (ifs.fail() && !ifs.eof()){
                return nullptr;
            }
            //validate character
            if (!validateChar(map[row][col])){
                return nullptr;
            }

            if(row == player.row && col == player.col){
                map[row][col] = TILE_PLAYER;
            }

        }
    }

    // check for exits
    int doorCount = 0;
    int exitCount = 0;
    for (int row = 0; row < maxRow; row++) {
        for (int col = 0; col < maxCol; col++) {
            if (map[row][col] == TILE_DOOR){
                doorCount++;
            }
            if (map[row][col] == TILE_EXIT){
                exitCount++;
            }
        }
    }

    if (doorCount == 0 && exitCount == 0){
        return nullptr;
    }


    return map;
}


/**
 * TODO: Student implement this function
 * Translate the character direction input by the user into row or column change.
 * That is, updates the nextRow or nextCol according to the player's movement direction.
 * @param   input       Character input by the user which translates to a direction.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @updates  nextRow, nextCol
 */
void getDirection(char input, int& nextRow, int& nextCol) {

    // switch block?

    switch(input) {
        case MOVE_LEFT:
            nextCol--;
            break;
        case MOVE_RIGHT:
            nextCol++;
            break;
        case MOVE_UP:
            nextRow--; // the ++ and -- were are backwards LOOK AT It differnet
            break;
        case MOVE_DOWN:
            nextRow++;
            break;
    }
    
}

/**
 * TODO: [suggested] Student implement this function
 * Allocate the 2D map array.
 * Initialize each cell to TILE_OPEN.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @return  2D map array for the dungeon level, holds char type.
 */
char** createMap(int maxRow, int maxCol) {

    char** map = new char *[maxRow] {};
    for (int row = 0; row < maxRow; row++){
        map[row] = new char[maxCol];
    }


    for (int col = 0; col < maxCol; col++){
        for (int row = 0; row < maxRow; row++){
            map[row][col] = '-';
        }
    }

    return map;
}

/**
 * TODO: Student implement this function
 * Deallocates the 2D map array.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @return None
 * @update map, maxRow
 */
void deleteMap(char**& map, int& maxRow) {
    if (map != nullptr){
        for (int i = 0; i < maxRow; ++i){
            delete[] map[i];
        }
        delete[] map;
        map = nullptr;

        maxRow = 0;
    }
    
}

/**
 * TODO: Student implement this function
 * Resize the 2D map by doubling both dimensions.
 * Copy the current map contents to the right, diagonal down, and below.
 * Do not duplicate the player, and remember to avoid memory leaks!
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height), to be doubled.
 * @param   maxCol      Number of columns in the dungeon table (aka width), to be doubled.
 * @return  pointer to a dynamically-allocated 2D array (map) that has twice as many columns and rows in size.
 * @update maxRow, maxCol
 */
char** resizeMap(char** map, int& maxRow, int& maxCol) {

    // create temporary var to hold pointer to resized map

    char** mapHolder = createMap(maxRow*2, maxCol*2);

    //first top left quadrant
    for (int row = 0; row < maxRow; row++) {
        for (int col = 0; col < maxCol; col++) {
            mapHolder[row][col] = map[row][col];
        }
    }

    //bottom left quadrant
    for (int row = 0; row < maxRow; row++) {
        for (int col = 0; col < maxCol; col++) {
            if(map[row][col] == TILE_PLAYER){
                mapHolder[row + maxRow][col] = TILE_OPEN;
            } else {
                mapHolder[row + maxRow][col] = map[row][col];
            }
        }
    }


    //top right quadrant
    for (int row = 0; row < maxRow; row++) {
        for (int col = 0; col < maxCol; col++) {
            if(map[row][col] == TILE_PLAYER){
                mapHolder[row][col + maxCol] = TILE_OPEN;
            } else {
                mapHolder[row][col + maxCol] = map[row][col];
            }
        }
    }

        //bottom right quadrant
    for (int row = 0; row < maxRow; row++) {
        for (int col = 0; col < maxCol; col++) {
            if(map[row][col] == TILE_PLAYER){
                mapHolder[row + maxRow][col + maxCol] = TILE_OPEN;
            } else {
                mapHolder[row + maxRow][col + maxCol] = map[row][col];
            }
        }
    }

    //delete old map
    deleteMap(map, maxRow);

    //update vars
    maxRow = maxRow*2;
    maxCol = maxCol*2;

    return mapHolder;
}

/**
 * TODO: Student implement this function
 * Checks if the player can move in the specified direction and performs the move if so.
 * Cannot move out of bounds or onto TILE_PILLAR or TILE_MONSTER.
 * Cannot move onto TILE_EXIT without at least one treasure. 
 * If TILE_TREASURE, increment treasure by 1.
 * Remember to update the map tile that the player moves onto and return the appropriate status.
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object to by reference to see current location.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @return  Player's movement status after updating player's position.
 * @update map contents, player
 */
int doPlayerMove(char** map, int maxRow, int maxCol, Player& player, int nextRow, int nextCol) {
    
    //when does player stay out of bounds, monster, pillar
    if(nextRow < 0 || nextCol < 0 || nextRow >= maxRow || nextCol >= maxCol || map[nextRow][nextCol] == TILE_MONSTER || map[nextRow][nextCol] == TILE_PILLAR){
        nextRow = player.row;
        nextCol = player.col;
        return STATUS_STAY;
    } else if (map[nextRow][nextCol] == TILE_AMULET){ // if next tile is amulert
        map[nextRow][nextCol] = TILE_PLAYER;
        map[player.row][player.col] = TILE_OPEN;
        player.row = nextRow;
        player.col = nextCol;

        return STATUS_AMULET;
    } else if (map[nextRow][nextCol] == TILE_DOOR){ // if on door
        map[nextRow][nextCol] = TILE_PLAYER;
        map[player.row][player.col] = TILE_OPEN;
        player.row = nextRow;
        player.col = nextCol;

        return STATUS_LEAVE;
    } else if (map[nextRow][nextCol] == TILE_TREASURE){ // if on treasure
        player.treasure = player.treasure + 1;
        map[nextRow][nextCol] = TILE_PLAYER;
        map[player.row][player.col] = TILE_OPEN;
        player.row = nextRow;
        player.col = nextCol;

        return STATUS_TREASURE;
    } else if (map[nextRow][nextCol] == TILE_EXIT) { // if on exit
        if (player.treasure < 1){ // player cant exit if he has no treasure
            nextRow = player.row;
            nextCol = player.col;
            return STATUS_STAY;
        } else {
            map[nextRow][nextCol] = TILE_PLAYER;
            map[player.row][player.col] = TILE_OPEN;
            player.row = nextRow;
            player.col = nextCol;

            return STATUS_ESCAPE;
        }
    } else { // last possibility is for tile open in which we move
        map[nextRow][nextCol] = TILE_PLAYER;
        map[player.row][player.col] = TILE_OPEN;
        player.row = nextRow;
        player.col = nextCol;
        
        return STATUS_MOVE; 
    }

    // handles all 6 status constants
}

/**
 * TODO: Student implement this function
 * Update monster locations:
 * We check up, down, left, right from the current player position.
 * If we see an obstacle, there is no line of sight in that direction, and the monster does not move.
 * If we see a monster before an obstacle, the monster moves one tile toward the player.
 * We should update the map as the monster moves.
 * At the end, we check if a monster has moved onto the player's tile.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference for current location.
 * @return  Boolean value indicating player status: true if monster reaches the player, false if not.
 * @update map contents
 */
bool doMonsterAttack(char** map, int maxRow, int maxCol, const Player& player) {


    return false;
}
