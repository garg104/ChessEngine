#include "GameSetup.hpp"
#include "GamePiece.cpp"

class Rook : public GamePiece {

    public:
        Rook() {
            player = 0;
        }

        Rook(int player) {
            GamePiece::player = player;
        }

        virtual bool checkMoveValidity(int orgin, int dest, int* board);


        ~Rook();

};