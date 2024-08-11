#pragma once
#include "chess_piece.hpp"
#include "macros.hpp"

#include <vector>

class ChessMove;
class Piece;

class Board {
 private:
  Piece* board_array[BOARD_LENGTH][BOARD_LENGTH];
  std::vector<Piece*> white_pawns;
  std::vector<Piece*> black_pawns;
  int current_player = WHITE;

 public:
  Board();
  Piece* access_field(int rank, int file);
  void remove_piece(int rank, int file);
  const bool get_current_player() const;
  void execute_move(ChessMove* move);
  void reset_en_passant(int color);
  void set_piece(int rank, int file, Piece* piece);
  void clean_up();
  void setup_rank(int color);
};
