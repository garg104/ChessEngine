#include "Piece.hpp"

class Pawn : public GamePiece {

    public:
        Pawn() {
            player = 0;
        }

        Pawn(int player) {
            GamePiece::player = player;
        }

        virtual bool checkMoveValidity(int initial, int final, int* board) {
            if (player == WHITE) { // white player
                if(board[final] == nil) { // no-kill
                    // white pawn can move up 1 always but can only move 2 up when at start
                    if ((initial - final == 8) ||
                        ((initial - final == 16 && initial / 8 == 6))) {
                            return true;
                    } 
                } else { // kill
                    // white pawn can move diagonal-up 1 
                    if ((initial - final == 7) ||
                        (initial - final == 9)) {
                        return true;
                    }
                }
            } else { // black player
                if (board[final] == nil) { // no-kill
                    // black pawn can move down 1 always but can only move 2 down when at start
                    if ((final - initial == 8) ||
                        ((final - initial == 16 && initial / 8 == 1))) {
                        return true;
                    } 
                } else { // kill
                    // black pawn can move diagonal-down 1
                    if ((final - initial == 7) ||
                        (final - initial == 9 )) {
                        return true;
                    }
                }
            }
            return false;
        }
        

        ~Pawn();
        

};