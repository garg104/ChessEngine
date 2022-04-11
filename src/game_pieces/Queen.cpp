#include "Piece.hpp"

class Queen : public GamePiece {

    public:
        Queen() {
            player = 0;
        }

        Queen(int player) {
            GamePiece::player = player;
        }

        virtual bool checkMoveValidity(int initial, int final, int* board) {
            int diff = abs(initial - final);

            // check along diagonals and up-down and left-right
            int jump = 0;
            if (diff % 9 == 0) {
                jump = 9;
            } else if (diff % 8 == 0) {
                jump = 8;
            } else if (diff % 7 == 0) {
                jump = 7;
            } else if (diff / 8 == 0) {
                jump = 1;
            }

            // none of the 4 possible directions
            if (jump == 0) {
                return false;
            }

            // get jump direction
            jump = (initial - final) > 0 ? (0 - jump) : jump;
            // cout << "Jump is " << jump << endl;

            // make sure that the way to the final is clear
            // we do not need to check the final position as it is either epmty or is kill
            for (int i = 1; i < (diff/abs(jump)); i++) {
                // cout << "value at " << initial + (i * jump) << " is " << board[initial + (i * jump)] << endl;
                if (board[initial + (i * jump)] != nil) { // path is blocked
                    return false;
                }
            }
            
            return true;
        }


        ~Queen();
        

};