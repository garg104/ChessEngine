#include "GameSetup.hpp"
#include "GamePiece.cpp"

using namespace std;

class ChessBoard {

public:
    int chessBoard[64];                // the actual game board
    std::map<int, GamePiece *> pieces; // a hashmap to keep track of the game pieces
    int gamePieceCount[15];            // the number of a particual game piece on the board
    int turn;                          // to keep track on the player whose turn it is

    //void makePieces();
    //void setGamePieceCounts();
    //void setGamePiecesOnBoard();

    ChessBoard() {
        turn = 0;               // white plays first always
        makePieces();           // make the game peices
        setGamePieceCounts();   // set the number of game peices
        setGamePiecesOnBoard(); // set the pieces on the board
    }

    /*
     * move the piece from initial to destination if possible
     */
    bool moveGamePieceToDestination(int initial, int piece, int destination, int currentPlayer) {
        int flag = 0;
        // make sure the initial position is not empty
        if (chessBoard[initial] != nil) { 
            // make sure that it is the current player's piece
            if (pieces[chessBoard[initial]]->player == currentPlayer) {
                // make sure that the desitnation is empty or has oponents piece(kill)
                if ((chessBoard[destination] == nil) ||
                    (pieces[chessBoard[destination]]->player != currentPlayer)) {
                    // check if the move is a valid move for the piece player is trying to move
                    if (pieces[chessBoard[initial]]->checkMoveValidity(initial, destination, chessBoard)) {
                        // remove the piece from destinaton if it exists
                        if (chessBoard[destination] != nil) {
                            killPieceAtDestination(destination);
                        }
                        // move the game piece and return true
                        chessBoard[destination] = chessBoard[initial];
                        chessBoard[initial] = nil;
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
    void killPieceAtDestination(int destination) {
        gamePieceCount[chessBoard[destination]]--;
    }


    /*
     * Make game pieces and add them to the map
     */
    void makePieces() {

        pieces[whitePawn] = new Pawn(WHITE);
        pieces[blackPawn] = new Pawn(BLACK);

        pieces[whiteKinght]	= new Knight(WHITE);
        pieces[blackKinght]	= new Knight(BLACK);

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
        // initialize everythinig with -1
        for (int i = 0; i < 15; i++) {
            gamePieceCount[i] = -1;
        }

        // white pieces
        gamePieceCount[whitePawn] = 8;
        gamePieceCount[whiteBishop] = 2;
        gamePieceCount[whiteKinght] = 2;
        gamePieceCount[whiteRook] = 2;
        gamePieceCount[whiteQueen] = 1;
        gamePieceCount[whiteKing] = 1;

        // black pieces
        gamePieceCount[blackPawn] = 8;
        gamePieceCount[blackBishop] = 2;
        gamePieceCount[blackKinght] = 2;
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

        // set black pieces
        chessBoard[a1] = blackRook;
        chessBoard[b1] = blackKinght;
        chessBoard[c1] = blackBishop;
        chessBoard[d1] = blackQueen;
        chessBoard[e1] = blackKing;
        chessBoard[f1] = blackBishop;
        chessBoard[g1] = blackKinght;
        chessBoard[h1] = blackRook;
        for (int i = 8; i <=15; i++) {
            chessBoard[i] = blackPawn;
        }

        // set white pieces
        chessBoard[a8] = whiteRook;
        chessBoard[b8] = whiteKinght;
        chessBoard[c8] = whiteBishop;
        chessBoard[d8] = whiteQueen;
        chessBoard[e8] = whiteKing;
        chessBoard[f8] = whiteBishop;
        chessBoard[g8] = whiteKinght;
        chessBoard[h8] = whiteRook;
        for (int i = 48; i <=55; i++) {
            chessBoard[i] = whitePawn;
        }

        // set empty spaces
        for (int i = 16; i <= 47; i++) {
            chessBoard[i] = nil;
        }
        
    }


    /*
     * Prints the chess board
     */
    void print() {
        cout << " - - - - - - - - " << endl;
        for (int i = 0; i < 8; i++) {
            cout << "|";
            for (int j = 0; j < 8; j++) {
                switch (chessBoard[i * 8 + j]) {
                    case whitePawn:
                        cout << "P|";
                        break;
                    case whiteKinght:
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
                        cout << "C|";
                        break;
                    case blackPawn:
                        cout << "p|";
                        break;
                    case blackKinght:
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
                        cout << "c|";
                        break;
                    default:
                        cout << " |";
                        break;
                }
            }
            cout << "  " << i + 1 << endl;
        }
        cout << " - - - - - - - - " << endl
             << " a b c d e f g h " << endl;
    }


    /*
     * destructor
     */
    ~ChessBoard();

};