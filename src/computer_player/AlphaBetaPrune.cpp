#include "AlphaBetaPrune.hpp"


ChessBoard* alphaBetaPrune(int maxDepth, ChessBoard* board) {
    return alphaBetaPruning(maxDepth, board, 1, -INT_MAX, INT_MAX, 1);
}

ChessBoard* alphaBetaPruning(int maxDepth, ChessBoard* board, int depth, int alpha, int beta, int action) {
    // if maximum depth is reached
    if (depth >= maxDepth) {
        return board;
    }

    // get action of the child node
    int childAction = (action == 1 ? 0 : 1);


    // action 1 is maximizing which is black and action 0 is minimizing with is also white
    vector<ChessBoard*> possibleMoves = board->getAllPossibleMoves(action);
    ChessBoard* bestMove = NULL;
    int bestMoveIndex = 0;
    
    // go over all the possible moves
    for (int i = 0; i < possibleMoves.size(); i++) {
        // make tree
        ChessBoard* tempMove = alphaBetaPruning(maxDepth, possibleMoves[i], depth + 1, alpha, beta, childAction);

        // see if the move is the best move or not
        if (bestMove == NULL || isMoveBetterThan(tempMove, bestMove, action)) {
            // replace the current bestMove with the better one
            bestMove = tempMove;
            bestMoveIndex = i;

            // update alpha-beta by gettting scores
            if (childAction == 1) {
                // Black
                // beta = tempMove->evaluate(BLACK);
            } else {
                // White
                // alpha = tempMove->evaluate(WHITE);
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


