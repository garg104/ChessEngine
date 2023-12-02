#include "Piece.hpp"

class King : public GamePiece {

    public:
        King() {
            player = 0;
        }

        King(int player) {
            GamePiece::player = player;
        }

        virtual bool checkMoveValidity(int initial, int final, int* board) {
            // king can move any direction by 1 (no castling)
            int finalRow = final / 8;
            int finalCol = final % 8;
            int initialRow = initial / 8;
            int initialCol = initial % 8;

            
            if (finalRow > initialRow) {
                // down
                if (finalCol == initialCol) {
                    // direct down
                    if (finalRow - initialRow == 1) {
                        return true;
                    }
                    
                    return false;
                } else if (finalCol > initialCol) {
                    // down right
                    int nextCol = initialCol + 1;
                    int nextRow = initialRow + 1;
                    if (nextCol == finalCol && nextRow == finalRow) {
                        return true;
                    }
                    
                    return false; 
                } else {
                    // down left
                    int nextCol = initialCol - 1;
                    int nextRow = initialRow + 1;
                    if (nextCol == finalCol && nextRow == finalRow) {
                        return true;
                    }
                    
                    return false;

                }     
            } else if (finalRow == initialRow) {
                // same row
                if (finalCol > initialCol) {
                    // right
                    if (initialCol + 1 == finalCol) {
                        return true;
                    }
                    return false;
                } else {
                    // left
                    if (initialCol - 1 == finalCol) {
                        return true;
                    }
                    return false;
                }
            } else {
                // up
                if (finalCol == initialCol) {
                    // direct up
                    if (finalRow - initialRow == -1) {
                        return true;
                    }
                    
                    return false;
                } else if (finalCol > initialCol) {
                    // up right
                    int nextCol = initialCol + 1;
                    int nextRow = initialRow - 1;
                    if (nextCol == finalCol && nextRow == finalRow) {
                        return true;
                    }
                    
                    return false; 
                } else {
                    // up left
                    int nextCol = initialCol - 1;
                    int nextRow = initialRow - 1;
                    if (nextCol == finalCol && nextRow == finalRow) {
                        return true;
                    }
                    
                    return false;

                }  

            }

            

            
            return false;
        }


        ~King() {
            
        }


};
