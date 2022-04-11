#include "AlphaBetaPrune.hpp"




ChessBoard* alphaBetaPruning(int maxDepth, ChessBoard* board, int depth, int alpha, int beta, int action) {
    // if maximum depth is reached
    if (depth >= maxDepth) {
        return board;
    }

    // action 1 is maximizing which is black and action 0 is minimizing with is also white
    vector<ChessBoard*> possibleMoves = board->getAllPossibleMoves(action);

    return board;
}

ChessBoard* alphaBetaPrune(int maxDepth, ChessBoard* board) {
    return alphaBetaPruning(maxDepth, board, 1, -INT_MAX, INT_MAX, 1);
}
