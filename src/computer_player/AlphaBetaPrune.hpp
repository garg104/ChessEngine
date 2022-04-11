#ifndef ALPHA_BETA_PRUNE_H
#define ALPHA_BETA_PRUNE_H

#include "../ChessBoard.cpp"


bool isMoveBetterThan(ChessBoard* tempMove, ChessBoard* bestMove, int action) {
    // return true;
    return (action == 1) ? (tempMove->evaluate(BLACK) > bestMove->evaluate(BLACK)) : (tempMove->evaluate(WHITE) < bestMove->evaluate(WHITE));
}

ChessBoard* alphaBetaPrune(int maxDepth, ChessBoard* board);
ChessBoard* alphaBetaPruning(int maxDepth, ChessBoard* board, int depth, int alpha, int beta, int action);

#endif