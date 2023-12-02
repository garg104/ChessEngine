#include "AlphaBetaPrune.hpp"
#include <climits>


ChessBoard* alphaBetaPrune(int maxDepth, ChessBoard* board, int player) {
    return alphaBetaPruning(maxDepth, board, 1, -INT_MAX, INT_MAX, player, player);
}

ChessBoard* alphaBetaPruning(int maxDepth, ChessBoard* board, int depth, int alpha, int beta, int action, int player) {
    // if maximum depth is reached
    // action 1 is maximizing which is black and action 0 is minimizing with is also white
    // get action of the child node
    int childAction = (action == 1 ? 0 : 1);
    if (depth >= maxDepth) {
        return board;
    }
    vector<ChessBoard*> possibleMoves = board->getAllPossibleMoves(action);
    if ((int) possibleMoves.size() == 0) {
        return board;
    }
    ChessBoard* bestMove = NULL;
    int bestMoveIndex = 0;
    
    // go over all the possible moves
    for (int i = 0; i < (int) possibleMoves.size(); i++) {
        // make tree
        int blackPieces = 0;
        int whitePieces = 0;
        for (int j = 0 ; j < 64; j++) {
            ChessBoard* temp = possibleMoves[i];
            if (temp->chessBoard[j] != nil) {
                if (temp->pieces[temp->chessBoard[j]]->player == 0) {
                    whitePieces++;
                } else if (temp->pieces[temp->chessBoard[j]]->player == 1) {
                    blackPieces++;
                }
            }
        }
        if (whitePieces == 0 || blackPieces == 0) {
            bestMove = possibleMoves[i];
            bestMoveIndex = i;
            continue;

        }
        ChessBoard* tempMove = alphaBetaPruning(maxDepth, possibleMoves[i], depth + 1, alpha, beta, childAction, player);
        // see if the move is the best move or not
        if (bestMove == NULL || isMoveBetterThan(tempMove, bestMove, action, player)) {
            // replace the current bestMove with the better one
            bestMove = tempMove;
            bestMoveIndex = i;
            // update alpha-beta by getting scores
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
    for (int i = 0; i < (int) possibleMoves.size(); i++) {
        delete possibleMoves[i];
    }

    return finalResult;
}



