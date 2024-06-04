#include <vector>

enum piece_t {
    PAWN,
    ROOK,
    BISHOP,
    KNIGHT,
    KING,
    QUEEN,
};

typedef enum {
    BLACK,
    WHITE,
} type_t;

class Piece {
    private:
        int color;
        piece_t type;

    protected:
        std::vector<Move*> moves;

    public:
        Piece(int color, piece_t type);
        virtual void setup() = 0;
        const int get_color();
        const int get_type();
};


class Pawn: public Piece {
    public:
        Pawn(int color, piece_t type);
        virtual void setup() override;
};


class Rook: public Piece {
    public:
        Rook(int color, piece_t type);
        virtual void setup() override;
};


class Bishop: public Piece {
    public:
        Bishop(int color, piece_t type);
        virtual void setup() override;
};


class Knight: public Piece {
    public:
        Knight(int color, piece_t type);
        virtual void setup() override;
};


class King: public Piece {
    public:
        King(int color, piece_t type);
        virtual void setup() override;
};


class Queen: public Piece {
    public:
        Queen(int color, piece_t type);
        virtual void setup() override;
};
