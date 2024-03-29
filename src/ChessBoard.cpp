#include "ChessBoard.hpp"

class ChessBoard {

public:
    int chessBoard[64];                // the actual game board
    std::map<int, GamePiece *> pieces; // a hashmap to keep track of the game pieces
    int gamePieceCount[15];            // the number of a particular game piece on the board
    int turn;                          // to keep track on the player whose turn it is

    ChessBoard() {
        turn = 0;                      // white plays first always
        makePieces();                  // make the game pieces
        setGamePieceCounts();          // set the number of game pieces
        setGamePiecesOnBoard();        // set the pieces on the board
    }

    /*
     * evaluate the score 
     */
    int evaluate(int player) {
        int value = 0;
        StaticEvaluation *scoreTables = new StaticEvaluation(0);

        for (int i = 0; i < 64; i++) {
            if (chessBoard[i] != nil && pieces[chessBoard[i]]->player == player) {
                // add to the score
                value = value + scoreTables->score[chessBoard[i]][i];
            } else {
                // subtract to the score
                if(chessBoard[i] == whitePawn || chessBoard[i] == blackPawn){
				    value -= 100;
                } else if(chessBoard[i] == whiteKnight || chessBoard[i] == blackKnight){
                    value -= 320;
                } else if(chessBoard[i] == whiteBishop || chessBoard[i] == blackBishop){
                    value -= 330;
                } else if(chessBoard[i] == whiteRook || chessBoard[i] == blackRook){
                    value -= 500;
                } else if(chessBoard[i] == whiteQueen || chessBoard[i] == blackQueen){
                    value -= 900;
                } else if(chessBoard[i] == whiteKing || chessBoard[i] == blackKing){
                    value -= 20000;
                }

            }

        }

        if (player == BLACK ){
            if (gamePieceCount[blackKing] == 0 ){
                value -= 100000;
            }
        } else {
            if (gamePieceCount[whiteKing] == 0 ){
                value += 100000;
            }
	    }
        delete scoreTables;
        

        
        return value;

    }



    /*
     * find  and return the list of all the possible moves at the given instance of the board 
     */
    vector<ChessBoard*> getAllPossibleMoves(int player) {
        // cout << "in possible moves" << "\n" << endl << flush;

        vector<ChessBoard*> moves;
        // make a trial chess board on which to try the moves and copy the existing board in it
        ChessBoard* trial = new ChessBoard();
        *trial = *this;

        // check every possible move combination
        for (int initial = 0; initial < 64; initial++) {
            // make sure that the initial has the player's piece at that position
            if (chessBoard[initial] != nil && pieces[chessBoard[initial]]->player == player) {
                

                for (int final = 0; final < 64; final++) {
                    // make sure that the move is valid and add the move to the list and restore the board
                    if (final != initial) {
                        if ((trial->pieces[chessBoard[initial]])->checkMoveValidity(initial, final, chessBoard)) {
                            if (trial->moveGamePieceToDestination(initial, final, player)) {
                                // store this move in the list
                                ChessBoard* move = new ChessBoard();
                                *move = *trial;
                                moves.push_back(move);
                                // restore the board for next move calculation 
                                *trial = *this;
                            }
                        }
                    }
                }
            }
        }

        // make sure to free memory
        // delete trial;
        return moves;
    }

    /*
     * move the piece from initial to destination if possible
     */
    bool moveGamePieceToDestination(int initial, int final, int currentPlayer) {
        // make sure the initial position is not empty
        if (chessBoard[initial] != nil) { 
            // make sure that it is the current player's piece
            if (pieces[chessBoard[initial]]->player == currentPlayer) {
                // make sure that the destination is empty or has opponents piece(kill)
                if ((chessBoard[final] == nil) ||
                    (pieces[chessBoard[final]]->player != currentPlayer)) {
                    // check if the move is a valid move for the piece player is trying to move
                    if (pieces[chessBoard[initial]]->checkMoveValidity(initial, final, chessBoard)) {
                        // remove the piece from destinaton if it exists
                        if (chessBoard[final] != nil) {
                            killPieceAtFinal(final);
                        }
                        // move the game piece and return true
                        chessBoard[final] = chessBoard[initial];
                        chessBoard[initial] = nil;
                        // cout << "here" << endl;
                        return true;
                    }
                } 
            }
        }


        return false;
    }

    /*
     * Kill the piece at the destination by decreases the piece count of the piece
     * at the destination
     */
    void killPieceAtFinal(int final) {
        gamePieceCount[chessBoard[final]]--;
    }

    /*
     * Make game pieces and add them to the map
     */
    void makePieces() {

        pieces[whitePawn] = new Pawn(WHITE);
        pieces[blackPawn] = new Pawn(BLACK);

        pieces[whiteKnight]	= new Knight(WHITE);
        pieces[blackKnight]	= new Knight(BLACK);

        pieces[whiteBishop]	= new Bishop(WHITE);
        pieces[blackBishop]	= new Bishop(BLACK);

        pieces[whiteRook] = new Rook(WHITE);
        pieces[blackRook] = new Rook(BLACK);
       
        pieces[whiteQueen] = new Queen(WHITE);
        pieces[blackQueen] = new Queen(BLACK);

        pieces[whiteKing] = new King(WHITE);      
        pieces[blackKing] = new King(BLACK);
    }

    /*
     * Set the game piece counts to keep track of the pieces on board
     * Size of the array is 15 as the last piece (blackKing) is numbered 14
     * refer to gameSetup.cpp for more info
     */
    void setGamePieceCounts() {
        // initialize everything with -1
        for (int i = 0; i < 15; i++) {
            gamePieceCount[i] = -1;
        }

        // white pieces
        gamePieceCount[whitePawn] = 8;
        gamePieceCount[whiteBishop] = 2;
        gamePieceCount[whiteKnight] = 2;
        gamePieceCount[whiteRook] = 2;
        gamePieceCount[whiteQueen] = 1;
        gamePieceCount[whiteKing] = 1;

        // black pieces
        gamePieceCount[blackPawn] = 8;
        gamePieceCount[blackBishop] = 2;
        gamePieceCount[blackKnight] = 2;
        gamePieceCount[blackRook] = 2;
        gamePieceCount[blackQueen] = 1;
        gamePieceCount[blackKing] = 1;

    }

    /*
     * Set the game piece counts to keep track of the pieces on board
     * Size of the array is 15 as the last piece (blackKing) is numbered 14
     * refer to gameSetup.cpp for more info
     */
    void setGamePiecesOnBoard() {
        // set empty spaces
        for (int i = 0; i < 64; i++) {
            chessBoard[i] = nil;
        }

        // set black pieces
        chessBoard[a1] = blackRook;
        chessBoard[b1] = blackKnight;
        chessBoard[c1] = blackBishop;
        chessBoard[d1] = blackQueen;
        chessBoard[e1] = blackKing;
        chessBoard[f1] = blackBishop;
        chessBoard[g1] = blackKnight;
        chessBoard[h1] = blackRook;
        for (int i = 8; i <=15; i++) {
            chessBoard[i] = blackPawn;
        }

        // set white pieces
        chessBoard[a8] = whiteRook;
        chessBoard[b8] = whiteKnight;
        chessBoard[c8] = whiteBishop;
        chessBoard[d8] = whiteQueen;
        chessBoard[e8] = whiteKing;
        chessBoard[f8] = whiteBishop;
        chessBoard[g8] = whiteKnight;
        chessBoard[h8] = whiteRook;
        for (int i = 48; i <=55; i++) {
            chessBoard[i] = whitePawn;
        }
        
    }

    /*
     * Prints the chess board
     */
    void print() {
        cout << "    a b c d e f g h " << endl
             << "    - - - - - - - - " << endl;
        for (int i = 0; i < 8; i++) {
            cout << i + 1 << "  |";
            for (int j = 0; j < 8; j++) {
                switch (chessBoard[i * 8 + j]) {
                    case whitePawn:
                        cout << "P|";
                        break;
                    case whiteKnight:
                        cout << "K|";
                        break;
                    case whiteBishop:
                        cout << "B|";
                        break;
                    case whiteRook:
                        cout << "R|";
                        break;
                    case whiteQueen:
                        cout << "Q|";
                        break;
                    case whiteKing:
                        cout << "+|";
                        break;
                    case blackPawn:
                        cout << "p|";
                        break;
                    case blackKnight:
                        cout << "k|";
                        break;
                    case blackBishop:
                        cout << "b|";
                        break;
                    case blackRook:
                        cout << "r|";
                        break;
                    case blackQueen:
                        cout << "q|";
                        break;
                    case blackKing:
                        cout << "*|";
                        break;
                    default:
                        cout << " |";
                        break;
                }
            }
            cout << "  " << i + 1 << endl;
        }
        cout << "    - - - - - - - - " << endl
             << "    a b c d e f g h \n" << endl;
    }

    /*
     * Prints the chess board with Piece values at a given place
     */
    void printValues() {
        cout << " - - - - - - - - " << endl;
        for (int i = 0; i < 8; i++) {
            cout << "|";
            for (int j = 0; j < 8; j++) {
                cout << chessBoard[i * 8 + j] << "|";
            }
            cout << "  " << i + 1 << endl;
        }
        cout << " - - - - - - - - " << endl
             << " a b c d e f g h " << endl;
    }


    /*
     * destructor
     */
    ~ChessBoard() {

    }

};