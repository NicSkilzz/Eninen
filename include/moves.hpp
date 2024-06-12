#pragma once
#include "chess_piece.hpp"
#include "chess_board.hpp"

class Board;

class Move {
    private:
        int steps_rank;
        int steps_file;

    public:
        Move(int steps_rank, int steps_file);
        const int get_rank_change();
        const int get_file_change();
};
