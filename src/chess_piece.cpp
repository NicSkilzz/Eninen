#include "chess_piece.hpp"

#include <wx/wx.h>

#include <array>
#include <cmath>
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

const bool Piece::check_move(ChessMove* move) const {
  int new_rank = this->get_rank() + move->get_rank_change();
  int new_file = this->get_file() + move->get_file_change();

  // board boundaries
  if (new_rank > 7 || new_rank < 0 || new_file > 7 || new_file < 0) {
    return false;
  }

  Piece* target_field = this->board->access_field(new_rank, new_file);

  // target field is of opposite color
  if (target_field != nullptr &&
      target_field->get_color() == this->get_color()) {
    return false;
  }

  // Pawn only capturing diagonally
  if (this->type == PAWN) {
    if (this->has_been_moved && std::abs(this->current_rank - new_rank) == 2) {
      return false;
    }

    // Diagonal Move
    if (std::abs(this->current_rank - new_rank) ==
        std::abs(this->current_file - new_file)) {

      // Aiming at empty square
      if (target_field == nullptr && this->get_en_passant_pawn() == nullptr) {
        return false;
      }

      // En passant
      Piece* on_passant_pawn = this->get_en_passant_pawn();
      std::cout << on_passant_pawn << std::endl;
      if (on_passant_pawn != nullptr &&
          this->get_file() + move->get_file_change() !=
              on_passant_pawn->get_file()) {
        return false;
      }
      std::cout << "3" << std::endl;

      // Running into other piece (straight move)
    } else if (target_field != nullptr) {
      return false;
    }
  }

  // King special moves
  if (this->type == KING) {
    if (this->has_been_moved && std::abs(this->current_file - new_file) == 2) {
      return false;
    }
    // Rochade
    if (std::abs(this->current_file - new_file) == 2) {
      int targeted_rook_file = this->current_file - new_file > 0 ? 0 : 7;
      int targeted_rook_rank = this->color == WHITE ? 0 : 7;
      Piece* rochade_target =
          this->board->access_field(targeted_rook_rank, targeted_rook_file);
      if (rochade_target != nullptr && rochade_target->get_type() == ROOK &&
          !rochade_target->get_has_been_moved()) {
        int small_file =
            std::min(rochade_target->get_file(), this->current_file);
        int big_file = std::max(rochade_target->get_file(), this->current_file);
        for (int file = small_file + 1; file < big_file; file++) {
          if (this->board->access_field(this->current_rank, file) != nullptr) {
            return false;
          }
        }
        move->set_rochade(rochade_target);
      } else {
        return false;
      }
    }
  }

  // Checks ...

  // Check if piece on trajectory
  vector<std::array<int, 2>> trajectory;
  // jump
  if (this->type != KNIGHT) {
    // straight rank
    if (current_rank == new_rank) {
      int direction_factor = new_file < current_file ? -1 : 1;
      for (int file_change = 1; file_change < std::abs(new_file - current_file);
           file_change++) {
        trajectory.push_back(
            {current_rank, current_file + direction_factor * file_change});
      }
      // straight file
    } else if (current_file == new_file) {
      int direction_factor = new_rank < current_rank ? -1 : 1;
      for (int rank_change = 1; rank_change < std::abs(new_rank - current_rank);
           rank_change++) {
        trajectory.push_back(
            {current_rank + direction_factor * rank_change, current_file});
      }
      // diagonal
    } else if (std::abs(current_rank - new_rank) ==
               std::abs(current_file - new_file)) {
      int rank_factor = new_rank < current_rank ? -1 : 1;
      int file_factor = new_file < current_file ? -1 : 1;
      for (int change = 1; change < std::abs(new_rank - current_rank);
           change++) {
        trajectory.push_back({current_rank + rank_factor * change,
                              current_file + file_factor * change});
      }
    }
  }

  for (int i = 0; i < trajectory.size(); i++) {
    Piece* on_trajectory =
        this->board->access_field(trajectory[i][0], trajectory[i][1]);
    if (on_trajectory != nullptr) {
      return false;
    }
  }

  return true;
}

const vector<ChessMove*> Piece::get_usable_moves() const {
  vector<ChessMove*> feasableMoves;

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
void Piece::set_has_been_moved() { this->has_been_moved = true; }
const bool Piece::get_has_been_moved() const { return this->has_been_moved; }

void Piece::set_en_passant_pawn(Piece* pawn) {}
Piece* Piece::get_en_passant_pawn() const { return nullptr; }

Pawn::Pawn(int color, piece_t type, Board* board) : Piece(color, type, board) {
  this->setup();
}

void Pawn::setup() {
  int i = 1;
  if (this->get_color() == BLACK) i = -1;
  this->moves.push_back(new ChessMove(this, i * 1, 0));
  this->moves.push_back(new ChessMove(this, i * 2, 0));  // First step
  this->moves.push_back(new ChessMove(this, i * 1, 1));
  this->moves.push_back(new ChessMove(this, i * 1, -1));
}

void Pawn::set_en_passant_pawn(Piece* pawn) { this->en_passant_pawn = pawn; }
Piece* Pawn::get_en_passant_pawn() const { return this->en_passant_pawn; }

Rook::Rook(int color, piece_t type, Board* board) : Piece(color, type, board) {
  this->setup();
}

void Rook::setup() {
  for (unsigned i = 1; i < BOARD_LENGTH; i++) {
    this->moves.push_back(new ChessMove(this, 0, i));
    this->moves.push_back(new ChessMove(this, 0, -i));
    this->moves.push_back(new ChessMove(this, i, 0));
    this->moves.push_back(new ChessMove(this, -i, 0));
  }
}

Bishop::Bishop(int color, piece_t type, Board* board)
    : Piece(color, type, board) {
  this->setup();
}

void Bishop::setup() {
  for (unsigned i = 1; i < BOARD_LENGTH; i++) {
    this->moves.push_back(new ChessMove(this, i, i));
    this->moves.push_back(new ChessMove(this, i, -i));
    this->moves.push_back(new ChessMove(this, -i, i));
    this->moves.push_back(new ChessMove(this, -i, -i));
  }
}

Knight::Knight(int color, piece_t type, Board* board)
    : Piece(color, type, board) {
  this->setup();
}

void Knight::setup() {
  this->moves.push_back(new ChessMove(this, 2, 1));
  this->moves.push_back(new ChessMove(this, 2, -1));
  this->moves.push_back(new ChessMove(this, -2, 1));
  this->moves.push_back(new ChessMove(this, -2, -1));
  this->moves.push_back(new ChessMove(this, 1, 2));
  this->moves.push_back(new ChessMove(this, -1, 2));
  this->moves.push_back(new ChessMove(this, 1, -2));
  this->moves.push_back(new ChessMove(this, -1, -2));
}

King::King(int color, piece_t type, Board* board) : Piece(color, type, board) {
  this->setup();
}

void King::setup() {
  this->moves.push_back(new ChessMove(this, 1, 0));
  this->moves.push_back(new ChessMove(this, -1, 0));
  this->moves.push_back(new ChessMove(this, 0, 1));
  this->moves.push_back(new ChessMove(this, 0, -1));
  this->moves.push_back(new ChessMove(this, 1, 1));
  this->moves.push_back(new ChessMove(this, -1, 1));
  this->moves.push_back(new ChessMove(this, 1, -1));
  this->moves.push_back(new ChessMove(this, -1, -1));
  this->moves.push_back(new ChessMove(this, 0, 2));   // Rochade1
  this->moves.push_back(new ChessMove(this, 0, -2));  // Rochade2
}

Queen::Queen(int color, piece_t type, Board* board)
    : Piece(color, type, board) {
  this->setup();
}

void Queen::setup() {
  for (unsigned i = 1; i < BOARD_LENGTH; i++) {
    this->moves.push_back(new ChessMove(this, 0, i));
    this->moves.push_back(new ChessMove(this, 0, -i));
    this->moves.push_back(new ChessMove(this, i, 0));
    this->moves.push_back(new ChessMove(this, -i, 0));
  }

  for (unsigned i = 0; i < BOARD_LENGTH; i++) {
    this->moves.push_back(new ChessMove(this, i, i));
    this->moves.push_back(new ChessMove(this, i, -i));
    this->moves.push_back(new ChessMove(this, -i, i));
    this->moves.push_back(new ChessMove(this, -i, -i));
  }
}
