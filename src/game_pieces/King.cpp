#include "Piece.hpp"

class King : public GamePiece {

    public:
        King() {
            player = 0;
        }

        King(int player) {
            GamePiece::player = player;
        }

        virtual bool checkMoveValidity(int orgin, int dest, int* board) {
            return true;
        }


        ~King();


};
