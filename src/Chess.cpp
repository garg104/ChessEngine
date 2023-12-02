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
    int maxDepth = 4;
    int nThreads = 1;
    int aiType = 1;
    int test = 2;

    // parse in the arguments to define the game parameters

    // make the chess board to play the game on
    ChessBoard *board = new ChessBoard();
    ChessBoard *copy = new ChessBoard();

    // read in the arguments
    if (argc > 1) {
        aiType = atoi(argv[1]);
    }
    if (argc > 2) {
        maxDepth = atoi(argv[2]);
    }
    if (argc > 3) {
        nThreads = atoi(argv[3]);
    }
    if (argc > 4) {
        test = atoi(argv[4]);
    }


    // files to keep track of moves and time
    ofstream timeAI;
    timeAI.open ("time_" + to_string(aiType) + ".txt");
    ofstream move;
    move.open ("moves.txt");

    FILE* testFile;

    if (test == 1) {
        // test file
        string filename("test.moves");
        testFile = fopen("test.moves", "r");
        if (testFile == NULL) {
            return EXIT_FAILURE;
        }
    }



    cout << "Starting Game\n" << endl;

    board->print();
    
    // player(white) turn
    board->turn = WHITE; // player(white) turn

    cout << "\nPLAYER INPUT FORMAT IS: INITIAL DESTINATION\n" << endl;

    
    // keep on playing the game till someone wins
    // win condition: other players king count is 0
    int turnNumb = 1;
    while (1) {
        // player(white) turn
        board->turn = WHITE;
        cout << "Your Turn: " << endl;
        

        int inputError = 0;
        int initial;
        int final;
        char* c_line = nullptr;
        size_t len = 0;
        string in_initial;
        string in_final;
        string testFileLine;
        do {
            if (inputError > 0) {
                cout << "Please enter a valid move: " << endl;
            }
            // get player move
            if (test == 0) {
                cin >> in_initial >> in_final;
            } else if (test == 1) {
                // read in from test file moves
                if (getline(&c_line, &len, testFile) != -1) {
                    testFileLine.assign(c_line);
                    in_initial = testFileLine.substr(0, 2);
                    in_final = testFileLine.substr(3, 2);
                    cout << in_initial << " " << in_final << endl;
                } else {
                    return EXIT_FAILURE;
                }
            } else {
              if (aiType == 1) {
                copy = alphaBetaPrune(maxDepth, board, 0);
              } else {
                //cout << "PV Splitting" << endl;
                copy = PVSplit(nThreads, maxDepth, board);
              }   
              delete board;
              board = copy;
              // board->print();

              break;
            }
            
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
            break;
        }


        // AI move (black player)
        board->turn = BLACK;
        cout << "Computer's Turn: \n" << endl;

        // start time
        //auto start = std::chrono::high_resolution_clock::now();
        if (aiType == 1) {
            copy = alphaBetaPrune(maxDepth, board, 1);
        } else {
            //cout << "PV Splitting" << endl;
            copy = PVSplit(nThreads, maxDepth, board);
        }
        // end time
        //auto end = std::chrono::high_resolution_clock::now();
        //long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        delete board;
        board = copy;
        
        // get the time taken
        
        board->print();
        //timeAI << turnNumb << " " << (double) microseconds/1000000 << endl;

        // check for black's victory
        if (board->gamePieceCount[whiteKing] == 0) {
            // Black wins
            cout << "Black Wins!" << endl;
            break;
        }

        turnNumb++;
    }

    if (test == 1) {
      fclose(testFile);
      testFile = NULL;
    }

    timeAI.close();
    move.close();

    return 0;
}







