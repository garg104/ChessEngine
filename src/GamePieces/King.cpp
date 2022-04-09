#include "GameSetup.hpp"
#include "GamePiece.cpp"

class King : public GamePiece {

    public:
        King() {
            player = 0;
        }

        King(int player) {
            GamePiece::player = player;
        }

        virtual bool checkMoveValidity(int orgin, int dest, int* board);


        ~King();


};