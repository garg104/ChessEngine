#ifndef PV_SPLITTING_H
#define PV_SPLITTING_H

#include "./AlphaBetaPrune.hpp"
#include <glib.h>


ChessBoard* PVSplit(int nThreads, int maxDepth, ChessBoard* board);
ChessBoard* PVSplitting(int nThreads, int maxDepth, ChessBoard* board, int depth, int alpha, int beta, int action);
static void *moveExploration(gpointer thread_data, gpointer user_data);
ChessBoard* alphaBetaMiniMax(struct PruneData* prune, int depth, ChessBoard* board, int alpha, int beta, int action);

struct PruneData {
    int alpha;
    int beta;
    int maxDepth;
    ChessBoard* bestMove;
    int bestMoveIndex;
    GMutex pruneMutex; 
    GMutex resultMutex; 
};  

struct ThreadData{
    ChessBoard *board;
    int depth;
    int action;
    int threadId;
};

#endif