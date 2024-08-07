#pragma once
#include "chess_piece.hpp"
#include "macros.hpp"

class Piece;

class Board {
 private:
  Piece* board_array[BOARD_LENGTH][BOARD_LENGTH];
  int current_player = WHITE;

 public:
  Board();
  Piece* access_field(int rank, int file);
  void remove_piece(int rank, int file);
  const bool get_current_player() const;
  void move_piece(int source_rank, int source_file, int target_rank,
                  int target_file);
  void set_piece(int rank, int file, Piece* piece);
  void clean_up();
  void setup_rank(int color);
};
