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
            int row = initial / 8;
            int column = initial % 8;
            if (row ) {

            }
            
            return false;
        }


        ~Knight();


};