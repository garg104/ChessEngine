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
            if ((abs(initial - final) == 17) ||
                (abs(initial - final) == 15) ||
                (abs(initial - final) == 10) ||
                (abs(initial - final) == 6)) {
                return true;
            }
            return false;
        }


        ~Knight();


};