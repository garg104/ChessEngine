//#include <iostream>
//#include <cstring>
//#include <cstdio>
//#include <fstream>
//#include <time.h>

#include "GameSetup.hpp"
#include "ChessBoard.cpp"


/*
 * get the tile number on the chess board
 *
 * @param row input row by the player
 * @param column input column by the player
 * 
 * @return the location number on the chess board
 */
// int getTileOnBoard(char row, char column);


/*
 * runs the chess engine
 */
int main() {

    // make the chess board to play the game on
    ChessBoard *board = new ChessBoard();
    board->print();
    

}


// int getTileOnBoard(char row, char column) {

// }


