#pragma once
#include "chess_piece.hpp"

class Piece;

class ChessMove {
 public:
  ChessMove(Piece* piece, int steps_rank, int steps_file);
  Piece* get_piece();
  const int get_rank_change();
  const int get_file_change();
  Piece* get_rochade_rook();
  void set_rochade(Piece* target_rook);

 private:
  int steps_rank;
  int steps_file;
  Piece* piece;
  Piece* rochade_rook = nullptr;
};
