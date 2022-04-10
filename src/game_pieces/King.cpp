#include "Piece.hpp"

class King : public GamePiece {

    public:
        King() {
            player = 0;
        }

        King(int player) {
            GamePiece::player = player;
        }

        virtual bool checkMoveValidity(int initial, int final, int* board) {
            // king can move any direction by 1 (no castling)
            if ((abs(initial - final) == 1) ||
                (abs(initial - final) == 7) ||
                (abs(initial - final) == 8) ||
                (abs(initial - final) == 9)) {
                return true;
            }
            return false;
        }


        ~King();


};
