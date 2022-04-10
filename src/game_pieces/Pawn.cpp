#include "Piece.hpp"

class Pawn : public GamePiece {

    public:
        Pawn() {
            player = 0;
        }

        Pawn(int player) {
            GamePiece::player = player;
        }

        virtual bool checkMoveValidity(int origin, int dest, int* board) {
            return true;
        }
        

        ~Pawn();
        

};