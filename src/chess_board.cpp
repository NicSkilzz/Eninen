#include chess_board.h
#include chess_piece.h


ChessBoard::Board() {
    for (unsigned i = 0; i < 8; i++) {
        for (unsigned j = 0; j < 8; j++) {
            this->board_array[i][j] = nullptr;
        }
    }
    //chess pieces setup
}

Piece* ChessBoard::access_field(int rank, int file) {
    return this->board_array[rank][file];
}

void ChessBoard::remove_piece(int rank, int file) {
    delete this->board_array[rank][file];
    this->board_array[rank][file] = nullptr;
}

void ChessBoard::move_piece(int source_rank, int source_file, int target_rank, int target_file) {
    this->board_array[target_rank][target_file] = this->board_array[source_rank][source_file];
    this->board_array[source_rank][source_file] = nullptr;
}

bool set_piece(int rank, int file, Piece * piece) {
    
    if (piece == nullptr) {
        return false;
    }
    this->board_array[rank][file] = piece;

    return true;
}
