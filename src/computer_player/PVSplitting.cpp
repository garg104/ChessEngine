#include "PVSplitting.hpp"
#include <climits>


/*
 *
 * Use of Glib library for thread managment
 * https://www.freedesktop.org/software/gstreamer-sdk/data/docs/latest/glib/glib-Thread-Pools.html
 * 
 */


/*
 * "In PV Splitting, starting with the child nodes of the root node, the leftmost 
 * child node’s sub tree is searched first and then the remaining child nodes are
 * then searched. This is done recursively. That is when searching the leftmost
 * sub tree, the leftmost child node is expanded into its children first. Among 
 * its children, the leftmost child’s sub tree is again searched first before 
 * searching the remaining children in parallel."
 * 
 * from - https://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.218.405&rep=rep1&type=pdf
 */
ChessBoard* PVSplit(int nThreads, int maxDepth, ChessBoard* board) {
    return PVSplitting(nThreads, maxDepth, board,  1, -INT_MAX, INT_MAX, 1);
}

ChessBoard* PVSplitting(int nThreads, int maxDepth, ChessBoard* board, int depth, int alpha, int beta, int action) {
    // if maximum depth is reached
    // action 1 is maximizing which is black and action 0 is minimizing with is also white
    // get action of the child node
    int childAction = (action == 1 ? 0 : 1);
    if (depth >= maxDepth) {
        return board;
    }
    vector<ChessBoard*> possibleMoves = board->getAllPossibleMoves(action);

    struct PruneData* prune = new struct PruneData;

    prune->bestMove = PVSplitting(nThreads, maxDepth, possibleMoves[0], depth + 1, alpha, beta, childAction);
    prune->bestMoveIndex = 0;
    if (childAction == 1) {
        prune->beta = prune->bestMove->evaluate(BLACK);
    } else {
        prune->alpha = prune->bestMove->evaluate(WHITE);
    }

    // evalute other children
    if (prune->alpha <= prune->beta) {
        // not pruned
        prune->maxDepth = maxDepth;
        g_mutex_init(&prune->pruneMutex);
        g_mutex_init(&prune->resultMutex);

        // start execution on threads
        GThreadPool* pool = g_thread_pool_new((GFunc) &moveExploration, prune, nThreads, false, NULL);
        struct ThreadData* data = (struct ThreadData*) malloc(sizeof(struct ThreadData) *possibleMoves.size());
        for (int i = 1; i < possibleMoves.size(); i++) {
            data[i].threadId = i;
            data[i].board = possibleMoves[i];
            data[i].depth = depth + 1;
            data[i].action = childAction;
            g_thread_pool_push(pool, &data[i], NULL);
        }
        // wait for all the threads to finish and then free the data
        g_thread_pool_free(pool, false, true);
        free(data);
    }

    // get the final result
    ChessBoard* finalResult = new ChessBoard;
    *finalResult = *possibleMoves[prune->bestMoveIndex];

    // free the memory
    for (int i = 0; i < possibleMoves.size(); i++) {
        delete possibleMoves[i];
    }
    free(prune);

    return finalResult;
}



static void *moveExploration(gpointer thread_data, gpointer user_data) {
    struct ThreadData *data = (struct ThreadData*)thread_data;
    struct PruneData *prune = (struct PruneData*)user_data;

    g_mutex_lock(&prune->pruneMutex);
    int alpha = prune->alpha;
    int beta = prune->beta;
    g_mutex_unlock(&prune->pruneMutex);

    ChessBoard *tempMove = alphaBetaMiniMax(prune, data->depth, data->board, prune->alpha, prune->beta, data->action);
    if (tempMove == NULL) {
        return NULL;
    }

    g_mutex_lock(&prune->resultMutex);
    if (prune->bestMove == NULL || isMoveBetterThan(tempMove, prune->bestMove, data->action)) {
        // replace the current bestMove with the better one
        prune->bestMove = tempMove;
        prune->bestMoveIndex = data->threadId;
        // update alpha-beta by gettting scores
        if (data->action == 1) {
            // Black
            g_mutex_lock(&prune->pruneMutex);
            beta = tempMove->evaluate(BLACK);
            g_mutex_unlock(&prune->pruneMutex);
        } else {
            // White
            g_mutex_lock(&prune->pruneMutex);
            alpha = tempMove->evaluate(WHITE);
            g_mutex_unlock(&prune->pruneMutex);
        }
    }
    g_mutex_unlock(&prune->resultMutex);

    return NULL;
}


ChessBoard* alphaBetaMiniMax(struct PruneData* prune, int depth, ChessBoard* board, int alpha, int beta, int action) {
    g_mutex_lock(&prune->pruneMutex);
    if (prune->alpha > prune->beta) {
        g_mutex_unlock(&prune->pruneMutex);
        return NULL;
    }
    g_mutex_unlock(&prune->pruneMutex);
    if (depth >= prune->maxDepth) {
        return board;
    }
    vector<ChessBoard*> possibleMoves = board->getAllPossibleMoves(action);

    ChessBoard* bestMove = NULL;
    int bestMoveIndex = 0;
    
    // go over all the possible moves
    int childAction = (action == 1 ? 0 : 1);
    for (int i = 0; i < possibleMoves.size(); i++) {
        // make tree
        ChessBoard* tempMove = alphaBetaMiniMax(prune, depth + 1, possibleMoves[i], alpha, beta, childAction);
        // see if the move is the best move or not
        if (tempMove == NULL) {
            // free the memory
            for (int i = 0; i < possibleMoves.size(); i++) {
                delete possibleMoves[i];
            }
            return NULL;
        }
        if (bestMove == NULL || isMoveBetterThan(tempMove, bestMove, action)) {
            // replace the current bestMove with the better one
            bestMove = tempMove;
            bestMoveIndex = i;
            // update alpha-beta by gettting scores
            if (childAction == 1) {
                // Black
                beta = tempMove->evaluate(BLACK);
            } else {
                // White
                alpha = tempMove->evaluate(WHITE);
            }
        }
        // prune
        if (alpha > beta) {
            break;
        }
    }

    // copy the best possible move and return it
    ChessBoard *finalResult = new ChessBoard();
    *finalResult = *possibleMoves[bestMoveIndex];

    // free the memory
    for (int i = 0; i < possibleMoves.size(); i++) {
        delete possibleMoves[i];
    }

    return finalResult;





}


