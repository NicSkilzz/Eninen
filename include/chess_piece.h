#include <vector>

typedef enum {
    PAWN,
    ROOK,
    BISHOP,
    KNIGHT,
    KING,
    QUEEN,
} piece_t;

class Piece {
    private:
        int color;
        piece_t type;
        vector<Move*> moves;     

    public:
        Piece(int color, piece_t type);
        virtual void setup() = 0;
        const int get_color();
        const int get_type();
}


class Pawn: public Piece {
    public:
        Pawn(int color, piece_t type);
        virtual void setup() override;
}


class Rook: public Rook {
    public:
        Rook(int color, piece_t type);
        virtual void setup() override;
}


class Bishop: public Bishop {
    public:
        Bishop(int color, piece_t type);
        virtual void setup() override;
}


class Knight: public Knight {
    public:
        Knight(int color, piece_t type);
        virtual void setup() override;
}


class King: public King {
    public:
        Knight(int color, piece_t type);
        virtual void setup() override;
}


class Queen: public Queen {
    public:
        Queen(int color, piece_t type);
        virtual void setup() override;
}