#include "GameSetup.hpp"
#include "GamePiece.cpp"

class Pawn : public GamePiece {

    public:
        Pawn() {
            player = 0;
        }

        Pawn(int player) {
            GamePiece::player = player;
        }

        virtual bool checkMoveValidity(int orgin, int dest, int* board);


        ~Pawn();

};