#pragma once
#include <vector>
#include "chess_board.hpp"
#include "move.hpp"

#include <string>
#include <wx/wx.h>

class Board;
class ChessMove;

enum piece_t {
    PAWN,
    ROOK,
    BISHOP,
    KNIGHT,
    KING,
    QUEEN,
};

class Piece {
    private:
        int color;
        piece_t type;

    protected:
        std::vector<ChessMove*> moves;
        Board * board;
        int current_rank;
        int current_file;
        bool has_been_moved = false;

    public:
        Piece(int color, piece_t type, Board * board);
        virtual void setup() = 0;
        virtual void set_en_passant_pawn(Piece* pawn);
        virtual Piece* get_en_passant_pawn() const;

        const int get_color() const;
        const piece_t get_type() const;
        const int get_rank() const;
        const int get_file() const;
        void set_has_been_moved();
        const bool get_has_been_moved() const;
        void set_position(int rank, int file);
        static std::string get_piece_text(Piece* piece);
        static wxBitmap get_piece_bitmap(Piece* piece);

        const std::vector<ChessMove*> get_usable_moves() const;
        const bool check_move(ChessMove * move) const;
};


class Pawn: public Piece {
    public:
        Pawn(int color, piece_t type, Board * board);
        virtual void setup() override;
        void set_en_passant_pawn(Piece* pawn);
        Piece* get_en_passant_pawn() const;

    private:
        Piece* en_passant_pawn;
};


class Rook: public Piece {
    public:
        Rook(int color, piece_t type, Board * board);
        virtual void setup() override;
};


class Bishop: public Piece {
    public:
        Bishop(int color, piece_t type, Board * board);
        virtual void setup() override;
};


class Knight: public Piece {
    public:
        Knight(int color, piece_t type, Board * board);
        virtual void setup() override;
};


class King: public Piece {
    public:
        King(int color, piece_t type, Board * board);
        virtual void setup() override;
};


class Queen: public Piece {
    public:
        Queen(int color, piece_t type, Board * board);
        virtual void setup() override;
};
