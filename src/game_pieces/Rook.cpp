#include "Piece.hpp"

class Rook : public GamePiece {

    public:
        Rook() {
            player = 0;
        }

        Rook(int player) {
            GamePiece::player = player;
        }

        virtual bool checkMoveValidity(int initial, int final, int* board) {
            int finalRow = final / 8;
            int finalCol = final % 8;
            int initialRow = initial / 8;
            int initialCol = initial % 8;


            if (finalRow > initialRow) {
                // down
                if (finalCol == initialCol) {
                    // direct down
                    for (int i = initialRow + 1; i < finalRow; i++) {
                        if (board[i * 8 + initialCol] != nil) { // path is blocked
                            return false;
                        }
                    }
                    return true;
                } 
            } else if (finalRow == initialRow) {
                // same row
                if (finalCol > initialCol) {
                    // right
                    for (int i = initialCol + 1; i < finalCol; i++) {
                        if (board[(initialRow * 8) + i] != nil) { // path is blocked
                            return false;
                        }
                    }
                    return true;
                } else {
                    // left
                    for (int i = initialCol - 1; i > finalCol; i--) {
                        if (board[(initialRow * 8) + i] != nil) { // path is blocked
                            return false;
                        }
                    }
                    return true;
                }
            } else {
                // up
                if (finalCol == initialCol) {
                    // direct up
                    for (int i = initialRow - 1; i > finalRow; i--) {
                        if (board[i * 8 + initialCol] != nil) { // path is blocked
                            return false;
                        }
                    }
                    return true;
                } 

            }

            return false;
        }


        ~Rook() {
            
        }
        

};