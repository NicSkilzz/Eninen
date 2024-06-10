#include "../include/chess_board.hpp"
#include "../include/chess_piece.hpp"


Board::Board() {
    for (unsigned i = 0; i < BOARD_LENGTH; i++) {
        for (unsigned j = 0; j < BOARD_LENGTH; j++) {
            this->board_array[i][j] = nullptr;
        }
    }

    for (unsigned i = 0; i < BOARD_LENGTH; i++) {
        this->board_array[1][i] = new Pawn(WHITE, PAWN, this);
        this->board_array[1][i]->setup();

        this->board_array[6][i] = new Pawn(BLACK, PAWN, this);
        this->board_array[6][i]->setup();
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
  this->board_array[rank][1] = new Knight(color, KNIGHT, this);
  this->board_array[rank][2] = new Bishop(color, BISHOP, this);
  this->board_array[rank][3] = new Queen(color, QUEEN, this);
  this->board_array[rank][4] = new King(color, KING, this);
  this->board_array[rank][5] = new Bishop(color, BISHOP, this);
  this->board_array[rank][6] = new Knight(color, KNIGHT, this);
  this->board_array[rank][7] = new Rook(color, ROOK, this);
}

Piece* Board::access_field(int rank, int file) {
    return this->board_array[rank][file];
}

void Board::remove_piece(int rank, int file) {
    delete this->board_array[rank][file];
    this->board_array[rank][file] = nullptr;
}

void Board::move_piece(int source_rank, int source_file, int target_rank, int target_file) {
    this->board_array[target_rank][target_file] = this->board_array[source_rank][source_file];
    this->board_array[source_rank][source_file] = nullptr;
}

void Board::set_piece(int rank, int file, Piece * piece) {
    if (piece == nullptr) {
        return;
    }
    this->board_array[rank][file] = piece;

    return;
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
