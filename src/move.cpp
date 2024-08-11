#include "move.hpp"

ChessMove::ChessMove(Piece* piece, int steps_rank, int steps_file): piece(piece), steps_rank(steps_rank), steps_file(steps_file) {}

Piece* ChessMove::get_piece() { return this->piece; }

const int ChessMove::get_rank_change() { return this->steps_rank; }

const int ChessMove::get_file_change() { return this->steps_file; }

Piece* ChessMove::get_rochade_rook() { return this->rochade_rook; }

void ChessMove::set_rochade(Piece* target_rook) {
    this->rochade_rook = target_rook;
}