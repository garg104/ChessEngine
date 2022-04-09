#include "GameSetup.hpp"
#include "GamePiece.cpp"

class Bishop : public GamePiece {

    public:
        Bishop() {
            player = 0;
        }

        Bishop(int player) {
            GamePiece::player = player;
        }

        virtual bool checkMoveValidity(int orgin, int dest, int* board);


        ~Bishop();


};