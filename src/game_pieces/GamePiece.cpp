class GamePiece {
    friend class ChessBoard;

    public:
        int player;
        GamePiece() {
            player = 0;
        }

        int getPlayer() {
            return player;
        }

        virtual bool checkMoveValidity(int origin, int dest, int* board) {
            return false;
        };


        ~GamePiece();
};


