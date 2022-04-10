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

       // virtual bool checkMoveValidity(int orgin, int dest, int* myboard);

        ~GamePiece();
};


class Pawn : public GamePiece {
    public:
        Pawn() {
            player = 0;
        }

        Pawn(int player) {
            GamePiece::player = player;
        }

        //virtual bool checkMoveValidity(int orgin, int dest, int* board);

        ~Pawn();

};

class Bishop : public GamePiece {

    public:
        Bishop() {
            player = 0;
        }

        Bishop(int player) {
            GamePiece::player = player;
        }

        //virtual bool checkMoveValidity(int orgin, int dest, int* board);


        ~Bishop();


};


class Knight: public GamePiece {

    public:
        Knight() {
            player = 0;
        }

        Knight(int player) {
            GamePiece::player = player;
        }

        //virtual bool checkMoveValidity(int orgin, int dest, int* board);


        ~Knight();


};


class Rook : public GamePiece {

    public:
        Rook() {
            player = 0;
        }

        Rook(int player) {
            GamePiece::player = player;
        }

        //virtual bool checkMoveValidity(int orgin, int dest, int* board);


        ~Rook();

};

class Queen : public GamePiece {

    public:
        Queen() {
            player = 0;
        }

        Queen(int player) {
            GamePiece::player = player;
        }

       // virtual bool checkMoveValidity(int orgin, int dest, int* board);


        ~Queen();

};

class King : public GamePiece {

    public:
        King() {
            player = 0;
        }

        King(int player) {
            GamePiece::player = player;
        }

       // virtual bool checkMoveValidity(int orgin, int dest, int* board);


        ~King();


};


