#include "GameSetup.hpp"
#include "GamePiece.cpp"

class Queen : public GamePiece {

    public:
        Queen() {
            player = 0;
        }

        Queen(int player) {
            GamePiece::player = player;
        }

        virtual bool checkMoveValidity(int orgin, int dest, int* board);


        ~Queen();

};