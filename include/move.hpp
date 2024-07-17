#pragma once
#include "chess_piece.hpp"

class Piece;

class Move {
 public:
  Move(int steps_rank, int steps_file);
  const int get_rank_change();
  const int get_file_change();
  void set_rochade(Piece* target_rook);

 private:
  int steps_rank;
  int steps_file;
  Piece* rochade_rook = nullptr;
};
