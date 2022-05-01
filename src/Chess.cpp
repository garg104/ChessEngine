#include "Chess.hpp"
#include <chrono>


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

    if (column >= 97 && column <= 104) {
        // a to h
        column = column - 97;
        if (row >= 1 && row <= 8) {
            // 1 to 8
            row = row - 1;
        } else {
            // error
            return -1;
        }
    } else {
        // error 
        return -1;
    }

    return row * 8 + column;
}


/*
 * runs the chess engine
 */
int main(int argc, char **argv) {

    // default values
    int maxDepth = 5;
    int nThreads = 5;
    int aiType = 1;

    // parse in the arguments to definie the game patameters

    // make the chess board to play the game on
    ChessBoard *board = new ChessBoard();
    ChessBoard *copy = new ChessBoard();

    // files to keep track of moves and time
    ofstream timeAI;
    timeAI.open ("time.txt");
    ofstream move;
    move.open ("moves.txt");


    if (argc > 1) {
        aiType = atoi(argv[1]);
    }
    if (argc > 2) {
        maxDepth = atoi(argv[2]);
    }
    if (argc > 3) {
        nThreads = atoi(argv[3]);
    }


    cout << "Starting Game\n" << endl;

    board->print();
    
    // player(white) turn
    board->turn = WHITE; // player(white) turn

    cout << "\nPLAYER INPUT FORMAT IS: INITIAL DESTINATION\n" << endl;

    
    // keep on playing the game till someone wins
    // win condition: other players king count is 0
    while (1) {
        // player(white) turn
        board->turn = WHITE; 
        cout << "Your Turn: " << endl;

        int inputError = 0;
        int initial;
        int final;
        string in_initial;
        string in_final;
        do {
            if (inputError > 0) {
                cout << "Please enter a valid move: " << endl;
            }
            // get player move
            cin >> in_initial >> in_final;
            initial = getTileOnBoard(in_initial[0], in_initial[1]);
            final = getTileOnBoard(in_final[0], in_final[1]);
            inputError++;
        } while ((initial < 0 || final < 0) ||
                 (!board->moveGamePieceToDestination(initial, final, WHITE)));
        
        move << in_initial << " " << in_final << endl;
        board->print();

        // check for white's victory
        if (board->gamePieceCount[blackKing] == 0) {
            // white wins
            cout << "White Wins!" << endl;
        }


        // AI move (black player)
        board->turn = BLACK;
        cout << "Computer's Turn: " << endl;

        // start time
        auto start = std::chrono::high_resolution_clock::now();
        if (aiType == 1) {
            copy = alphaBetaPrune(maxDepth, board);
        } else {
            //cout << "PV Splitting" << endl;
            copy = PVSplit(nThreads, maxDepth, board);
        }
        // end time
        auto end = std::chrono::high_resolution_clock::now();
        long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        cout <<  (double) microseconds/1000000 << endl;

        delete board;
        board = copy;
        
        // get the time taken
        
        board->print();
        timeAI << (double) microseconds/1000000 << endl;
        cout << (double) microseconds/1000000 << endl;

        // check for black's victory
        if (board->gamePieceCount[whiteKing] == 0) {
            // Black wins
            cout << "Black Wins!" << endl;
            break;
        }


    }

    timeAI.close();
    move.close();

    return 0;
}







