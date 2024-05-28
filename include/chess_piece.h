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
        check_move
        virtual void setup() = 0;

}