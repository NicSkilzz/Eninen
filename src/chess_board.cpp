#include "chess_board.hpp"
#include "chess_piece.hpp"

#include <iostream>

Board::Board() {
    for (unsigned i = 0; i < BOARD_LENGTH; i++) {
        for (unsigned j = 0; j < BOARD_LENGTH; j++) {
            this->board_array[i][j] = nullptr;
        }
    }

    for (unsigned i = 0; i < BOARD_LENGTH; i++) {
        this->board_array[1][i] = new Pawn(WHITE, PAWN, this);
        this->board_array[1][i]->set_position(1, i);
        this->board_array[1][i]->setup();
        this->white_pawns.push_back(this->board_array[1][i]);

        this->board_array[6][i] = new Pawn(BLACK, PAWN, this);
        this->board_array[6][i]->set_position(6, i);
        this->board_array[6][i]->setup();
        this->black_pawns.push_back(this->board_array[6][i]);
    }

    setup_rank(WHITE);
    setup_rank(BLACK);
}

void Board::setup_rank(int color) {
  int rank;
  if (color == WHITE) {
      rank = 0;
  } else {
      rank = 7;
  }

  this->board_array[rank][0] = new Rook(color, ROOK, this);
  this->board_array[rank][0]->set_position(rank, 0);
  this->board_array[rank][1] = new Knight(color, KNIGHT, this);
  this->board_array[rank][1]->set_position(rank, 1);
  this->board_array[rank][2] = new Bishop(color, BISHOP, this);
  this->board_array[rank][2]->set_position(rank, 2);
  this->board_array[rank][3] = new Queen(color, QUEEN, this);
  this->board_array[rank][3]->set_position(rank, 3);
  this->board_array[rank][4] = new King(color, KING, this);
  this->board_array[rank][4]->set_position(rank, 4);
  this->board_array[rank][5] = new Bishop(color, BISHOP, this);
  this->board_array[rank][5]->set_position(rank, 5);
  this->board_array[rank][6] = new Knight(color, KNIGHT, this);
  this->board_array[rank][6]->set_position(rank, 6);
  this->board_array[rank][7] = new Rook(color, ROOK, this);
  this->board_array[rank][7]->set_position(rank, 7);
}

Piece* Board::access_field(int rank, int file) {
    return this->board_array[rank][file];
}

void Board::remove_piece(int rank, int file) {
    delete this->board_array[rank][file];
    this->board_array[rank][file] = nullptr;
}

void Board::execute_move(ChessMove* move) {
    Piece* piece = move->get_piece();
    int source_rank = piece->get_rank();
    int source_file = piece->get_file();
    int target_rank = source_rank + move->get_rank_change();
    int target_file = source_file + move->get_file_change();

    // Player turn logic
    if (this->current_player == WHITE) {
        this->reset_en_passant(WHITE);
        this->current_player = BLACK;
    } else {
        this->reset_en_passant(BLACK);
        this->current_player = WHITE;
    }

    // Set flags
    this->board_array[source_rank][source_file]->set_has_been_moved();

    // Remove captured piece
    if (this->board_array[target_rank][target_file] != nullptr) {
        this->remove_piece(target_rank, target_file);
    }

    // Update internal board array: Move selected piece
    this->board_array[target_rank][target_file] = this->board_array[source_rank][source_file];
    this->board_array[source_rank][source_file] = nullptr;

    // Notify piece object
    this->board_array[target_rank][target_file]->set_position(target_rank, target_file);

    // Rochade
    Piece* rochade_rook = move->get_rochade_rook();
    if (rochade_rook != nullptr) {
        int rook_on_lower_file = rochade_rook->get_file() < source_file ? 1 : -1;
        this->board_array[rochade_rook->get_rank()][target_file + rook_on_lower_file] = rochade_rook;
        this->board_array[rochade_rook->get_rank()][rochade_rook->get_file()] = nullptr;

        rochade_rook->set_position(rochade_rook->get_rank(), target_file + rook_on_lower_file);
    }

    // En passant
    if (piece->get_type() == PAWN && std::abs(move->get_rank_change()) == 2) {
        Piece* on_upper_file = this->board_array[target_rank][target_file + 1];
        Piece* on_lower_file = this->board_array[target_rank][target_file - 1];
        if (on_upper_file != nullptr && on_upper_file->get_type() == PAWN && on_upper_file->get_color() == piece->get_color()) {
            on_upper_file->set_en_passant_pawn(piece);
        }
        if (on_lower_file != nullptr && on_lower_file->get_type() == PAWN && on_lower_file->get_color() == piece->get_color()) {
            on_lower_file->set_en_passant_pawn(piece);
        }
    }
}

void Board::reset_en_passant(int color) {
    if (color == WHITE) {
        for (Piece* pawn : white_pawns) {
            pawn->set_en_passant_pawn(nullptr);
        }
    } else if (color == BLACK) {
        for (Piece* pawn : black_pawns) {
            pawn->set_en_passant_pawn(nullptr);
        }
    }
}

void Board::set_piece(int rank, int file, Piece * piece) {
    if (piece == nullptr) {
        return;
    }
    this->board_array[rank][file] = piece;

    return;
}

const bool Board::get_current_player() const {
    return this->current_player;
}

void Board::clean_up() {
    for (unsigned i = 0; i < BOARD_LENGTH; i++) {
        for (unsigned j = 0; j < BOARD_LENGTH; j++) {
            if (this->board_array[i][j] != nullptr) {
                delete board_array[i][j];
            }
        }
    }
}
