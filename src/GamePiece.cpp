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

        virtual bool checkMoveValidity(int orgin, int dest, int* myboard) {
            return true;
        };

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

        virtual bool checkMoveValidity(int origin, int dest, int* board) {
            return true;
        }
        
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

        virtual bool checkMoveValidity(int orgin, int dest, int* board) {
            return true;
        }


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

        virtual bool checkMoveValidity(int orgin, int dest, int* board) {
            return true;
        }


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

        virtual bool checkMoveValidity(int orgin, int dest, int* board) {
            return true;
        }


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

        virtual bool checkMoveValidity(int orgin, int dest, int* board) {
            return true;
        }


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

        virtual bool checkMoveValidity(int orgin, int dest, int* board) {
            return true;
        }


        ~King();


};


