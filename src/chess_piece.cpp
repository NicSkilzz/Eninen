#include "chess_piece.hpp"

#include <wx/wx.h>

#include <iostream>
#include <vector>

#include "macros.hpp"
#include "move.hpp"

using std::vector;

Piece::Piece(int color, piece_t type, Board* board)
    : color(color), type(type), board(board) {
  this->current_rank = 0;
  this->current_file = 0;
}

wxBitmap Piece::get_piece_bitmap(Piece* piece) {
  // No piece -> no bitmap
  wxBitmap bitmap(60, 60, 32);
  if (piece == nullptr) {
    return bitmap;
  }

  // Piece -> access .png
  std::string path_to_bitmap = "./../assets/";
  std::string color_prefix = piece->get_color() == WHITE ? "w_" : "b_";
  std::string type_suffix;
  switch (piece->get_type()) {
    case PAWN:
      type_suffix = "pawn";
      break;
    case QUEEN:
      type_suffix = "queen";
      break;
    case ROOK:
      type_suffix = "rook";
      break;
    case BISHOP:
      type_suffix = "bishop";
      break;
    case KNIGHT:
      type_suffix = "knight";
      break;
    case KING:
      type_suffix = "king";
      break;

    default:
      break;
  }
  path_to_bitmap.append(color_prefix).append(type_suffix).append(".png");
  wxString wx_path_to_bitmap(path_to_bitmap);
  wxBitmap piece_bitmap(wx_path_to_bitmap, wxBITMAP_TYPE_PNG);
  return piece_bitmap;
}

std::string Piece::get_piece_text(Piece* piece) {
  std::string piece_str = " ";
  if (piece == nullptr) {
    piece_str = " ";
  } else {
    switch (piece->get_type()) {
      case PAWN:
        piece_str = "P";
        break;
      case QUEEN:
        piece_str = "Q";
        break;
      case ROOK:
        piece_str = "R";
        break;
      case BISHOP:
        piece_str = "B";
        break;
      case KNIGHT:
        piece_str = "J";
        break;
      case KING:
        piece_str = "K";
        break;

      default:
        break;
    }
  }
  return piece_str;
}

void Piece::set_position(int rank, int file) {
  this->current_rank = rank;
  this->current_file = file;
}

const bool Piece::check_move(Move* move) const {
  int new_rank = this->get_rank() + move->get_rank_change();
  int new_file = this->get_file() + move->get_file_change();

  if (new_rank > 7 || new_rank < 0 || new_file > 7 || new_file < 0) {
    return false;
  }

  Piece* current_field = this->board->access_field(new_rank, new_file);

  if (current_field == nullptr) {
    return true;
  }

  if (current_field->get_color() == this->get_color()) {
    return false;
  }
  // check if king can be targeted

  return true;
}

const vector<Move*> Piece::usable_moves() const {
  vector<Move*> feasableMoves;

  for (unsigned i = 0; i < this->moves.size(); i++) {
    if (this->check_move(this->moves[i]))
      feasableMoves.push_back(this->moves[i]);
  }
  return feasableMoves;
}

const int Piece::get_color() const { return this->color; }
const piece_t Piece::get_type() const { return this->type; }
const int Piece::get_rank() const { return this->current_rank; }
const int Piece::get_file() const { return this->current_file; }

Pawn::Pawn(int color, piece_t type, Board* board) : Piece(color, type, board) {
  this->setup();
}

void Pawn::setup() {
  int i = 1;
  if (this->get_color() == BLACK) i = -1;
  this->moves.push_back(new Move(i * 1, 0));
  this->moves.push_back(new Move(i * 2, 0));  // First step
  this->moves.push_back(new Move(i * 1, 1));
  this->moves.push_back(new Move(i * 1, -1));
}

Rook::Rook(int color, piece_t type, Board* board) : Piece(color, type, board) {
  this->setup();
}

void Rook::setup() {
  for (unsigned i = 1; i < BOARD_LENGTH; i++) {
    this->moves.push_back(new Move(0, i));
    this->moves.push_back(new Move(0, -i));
    this->moves.push_back(new Move(i, 0));
    this->moves.push_back(new Move(-i, 0));
  }
}

Bishop::Bishop(int color, piece_t type, Board* board)
    : Piece(color, type, board) {
  this->setup();
}

void Bishop::setup() {
  for (unsigned i = 1; i < BOARD_LENGTH; i++) {
    this->moves.push_back(new Move(i, i));
    this->moves.push_back(new Move(i, -i));
    this->moves.push_back(new Move(-i, i));
    this->moves.push_back(new Move(-i, -i));
  }
}

Knight::Knight(int color, piece_t type, Board* board)
    : Piece(color, type, board) {
  this->setup();
}

void Knight::setup() {
  this->moves.push_back(new Move(2, 1));
  this->moves.push_back(new Move(2, -1));
  this->moves.push_back(new Move(-2, 1));
  this->moves.push_back(new Move(-2, -1));
  this->moves.push_back(new Move(1, 2));
  this->moves.push_back(new Move(-1, 2));
  this->moves.push_back(new Move(1, -2));
  this->moves.push_back(new Move(-1, -2));
}

King::King(int color, piece_t type, Board* board) : Piece(color, type, board) {
  this->setup();
}

void King::setup() {
  this->moves.push_back(new Move(1, 0));
  this->moves.push_back(new Move(-1, 0));
  this->moves.push_back(new Move(0, 1));
  this->moves.push_back(new Move(0, -1));
  this->moves.push_back(new Move(1, 1));
  this->moves.push_back(new Move(-1, 1));
  this->moves.push_back(new Move(1, -1));
  this->moves.push_back(new Move(-1, -1));
  this->moves.push_back(new Move(0, 2));   // Rochade1
  this->moves.push_back(new Move(0, -2));  // Rochade2
}

Queen::Queen(int color, piece_t type, Board* board)
    : Piece(color, type, board) {
  this->setup();
}

void Queen::setup() {
  for (unsigned i = 1; i < BOARD_LENGTH; i++) {
    this->moves.push_back(new Move(0, i));
    this->moves.push_back(new Move(0, -i));
    this->moves.push_back(new Move(i, 0));
    this->moves.push_back(new Move(-i, 0));
  }

  for (unsigned i = 0; i < BOARD_LENGTH; i++) {
    this->moves.push_back(new Move(i, i));
    this->moves.push_back(new Move(i, -i));
    this->moves.push_back(new Move(-i, i));
    this->moves.push_back(new Move(-i, -i));
  }
}
