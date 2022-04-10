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
int getTileOnBoard(char a, char b) {
    int column = a;
    int row = b;
    row = row - 48;
    cout << column << " " << row << endl;

    

    if (column >= 97 && column <= 104) { // A to H
        column = column - 97;
    } else { // error 
        cout << "here1" << endl; 
        return -1;
    }

    if (row >= 1 && row <= 8) { // 1 to 8
        row = row - 1;
    } else { // error
    cout << "here2" << endl; 
        return -1;
    }

    return row * 8 + column;
}



/*
 * runs the chess engine
 */
int main() {

    // default values
    int maxDepth = 5;
    int nThreads = 5;

    // parse in the arguments to definie the game patameters

    // make the chess board to play the game on
    ChessBoard *board = new ChessBoard();
    ChessBoard *copy = new ChessBoard();

    cout << "Starting Game\n" << endl;
    board->print();
    cout << "\nPLAYER INPUT FORMAT IS: \nINITIAL GAME_PIECE DESTINATION\n" << endl;
    board->turn = WHITE; // player(white) turn

    // keep on playing the game till someone wins
    int initial;
    int piece;
    int destination;
    string temp1;
    string temp2;
    string temp3;
    while (1) { 
        // win condition: other players king count is 0

         
        


        // get player move
        board->turn = WHITE; // player(white) turn
        cout << "Your Turn: " << endl;

        // take the input in and parse
        cin >> temp1 >> temp2 >> temp3;
        cout << "test " << temp1[0] << " asd " << temp1[1] << endl;
        initial = getTileOnBoard(temp1[0], temp1[1]);
        piece = temp2[0];
        destination = getTileOnBoard(temp3[0], temp3[1]);
        cout << "paresed input " << initial << " " << destination << endl;


        // make sure that the input is valid
        while (initial < 0 || destination < 0) {
            cout << "Please enter a valid move: " << endl;
            cin >> temp1 >> temp2 >> temp3;
            cout << "test" << temp1[0] << "asd" << temp1[1];
            initial = getTileOnBoard(temp1[0], temp1[1]);
            piece = temp2[0];
            destination = getTileOnBoard(temp3[0], temp3[1]);
            cout << "paresed input " << initial << " " << destination << endl;
        }

        // make sure the the input corresponds to a valid move
        while (!board->moveGamePieceToDestination(initial, piece, destination, WHITE)) {
            do {
                cout << "Please enter a valid move: " << endl;
                cin >> temp1 >> temp2 >> temp3;
                initial = getTileOnBoard(temp1[0], temp1[1]);
                piece = temp2[0];
                destination = getTileOnBoard(temp3[0], temp3[1]);
                cout << "paresed input " << initial << " " << destination << endl;
            } while (initial < 0 || destination < 0);
        }

        board->print();

        // check for white's victory
        if (board->gamePieceCount[blackKing] == 0) {
            // white wins
            cout << "White Wins!" << endl;
            break;
        }




        // AI move (black player)
        board->turn = BLACK;
        cout << "Computer's Turn: " << endl;


        // check for black's victory
        if (board->gamePieceCount[whiteKing] == 0) {
            // Black wins
            cout << "Black Wins!" << endl;
            break;
        }


    }

    return 0;
}







