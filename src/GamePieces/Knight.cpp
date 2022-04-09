#include "GameSetup.hpp"
#include "GamePiece.cpp"

class Knight: public GamePiece {

    public:
        Knight() {
            player = 0;
        }

        Knight(int player) {
            GamePiece::player = player;
        }

        virtual bool checkMoveValidity(int orgin, int dest, int* board);


        ~Knight();


};