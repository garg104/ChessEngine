#include "Piece.hpp"

class Bishop : public GamePiece {

    public:
        Bishop() {
            player = 0;
        }

        Bishop(int player) {
            GamePiece::player = player;
        }

        virtual bool checkMoveValidity(int initial, int final, int* board) {
            int finalRow = final / 8;
            int finalCol = final % 8;
            int initialRow = initial / 8;
            int initialCol = initial % 8;


            if (finalRow > initialRow) {
                // down
                if (finalCol > initialCol) {
                    // down right
                    int nextCol = initialCol + 1;
                    int nextRow = initialRow + 1;
                    while (nextCol < 8 && nextRow < 8) {    
                        if ((nextRow * 8) + nextCol == final) {
                            return true;
                        }

                        if (board[(nextRow * 8) + nextCol] != nil) {
                            return false;
                        }

                        nextCol++;
                        nextRow++;
                    }

                    return false; 
                } else {
                    // down left
                    int nextCol = initialCol - 1;
                    int nextRow = initialRow + 1;
                    while (nextCol >= 0 && nextRow < 8) {    
                        if ((nextRow * 8) + nextCol == final) {
                            return true;
                        }

                        if (board[(nextRow * 8) + nextCol] != nil) {
                            return false;
                        }

                        nextCol--;
                        nextRow++;
                    }

                    return false;

                }     
            } else if (finalRow < initialRow) {
                // up
                if (finalCol > initialCol) {
                    // up right
                    int nextCol = initialCol + 1;
                    int nextRow = initialRow - 1;
                    while (nextCol < 8 && nextRow >= 0) {
                        if ((nextRow * 8) + nextCol == final) {
                            return true;
                        }

                        if (board[(nextRow * 8) + nextCol] != nil) {
                            return false;
                        }

                        nextCol++;
                        nextRow--;
                    }

                    return false; 
                } else {
                    // up left
                    int nextCol = initialCol - 1;
                    int nextRow = initialRow - 1;
                    while (nextCol >= 0 && nextRow >= 0) {    
                        if ((nextRow * 8) + nextCol == final) {
                            return true;
                        }

                        if (board[(nextRow * 8) + nextCol] != nil) {
                            return false;
                        }

                        nextCol--;
                        nextRow--;
                    }

                    return false;

                }

            }

            
            return false;
        }


        ~Bishop() {
            
        }


};