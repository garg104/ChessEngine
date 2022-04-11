#ifndef ALPHA_BETA_PRUNE_H
#define ALPHA_BETA_PRUNE_H

#include "../GameSetup.hpp"
#include "../ChessBoard.cpp"


bool isMoveBetterThan(ChessBoard* tempMove, ChessBoard* bestMove, int player);

ChessBoard* alphaBetaPrune(int maxDepth, ChessBoard* board);
ChessBoard* alphaBetaPruning(int maxDepth, ChessBoard* board, int depth, int alpha, int beta, int action)

#endif