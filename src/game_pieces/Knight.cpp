#include "Piece.hpp"

class Knight: public GamePiece {

    public:
        Knight() {
            player = 0;
        }

        Knight(int player) {
            GamePiece::player = player;
        }

        virtual bool checkMoveValidity(int initial, int final, int* board) {
            int finalRow = final / 8;
            int finalCol = final % 8;
            int initialRow = initial / 8;
            int initialCol = initial % 8;

            // move along row and then one cross column
            if ((finalRow >= 0 && finalRow <= 7) && 
                (abs(finalRow - initialRow) == 2)) {
                if ((finalCol >= 0 && finalCol <= 7) && 
                    (abs(finalCol - initialCol) == 1)) {
                    return true;
                }
            }

            // move along col and then one cross row
            if ((finalCol >= 0 && finalCol <= 7) && 
                (abs(finalCol - initialCol) == 2)) {
                if ((finalRow >= 0 && finalRow <= 7) && 
                    (abs(finalRow - initialRow) == 1)) {
                    return true;
                }
            }

            return false;
        }


        ~Knight() {
            
        }


};