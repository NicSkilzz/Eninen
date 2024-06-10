#pragma once
#include "chess_piece.hpp"
#include "moves.hpp"
#include "macros.hpp"

Piece::Piece(int color, piece_t type): color(color), type(type) {
    this->setup();
}

bool Piece::movable() const {
    for (unsigned i = 0; i < this->moves.size(); i++) {
        this->check_move(Move * move);
    }
}

bool Piece::check_move(Move * move) const {
    int new_rank = this->get_rank + move->get_rank_change();
    int new_file = this->get_file + move->get_file_change();

    if (new_rank > 7 || new_rank < 0 || new_file > 7 || new_file < 0) {
        return false;
    }

    Piece * current_field = this->board->board_array[new_rank][new_file];

    if (current_field = nullptr) {
        return true;
    }

    if (current_field->get_color == this->get_color) {
        return false;
    }

    //check if king can be targeted

    return true;
}

int Piece::get_color() const { return this->color; }
int Piece::get_type() const { return this->type; }
int Piece::get_rank() const { return this->rank; }
int Piece::get_file() const { return this->file; }

Pawn::Pawn(int color, piece_t type): Piece(color, type) {}

void Pawn::setup() {
    this->moves.push_back(new Move(1, 0));
    this->moves.push_back(new Move(2, 0));      //First step
    this->moves.push_back(new Move(1, 1));
    this->moves.push_back(new Move(1, -1));
}


Rook::Rook(int color, piece_t type): Piece(color, type) {}

void Rook::setup() {
    for (unsigned i = 1; i < BOARD_LENGTH; i++) {
        this->moves.push_back(new Move(0, i));
        this->moves.push_back(new Move(0, -i));
        this->moves.push_back(new Move(i, 0));
        this->moves.push_back(new Move(-i, 0));
    }
}


Bishop::Bishop(int color, piece_t type): Piece(color, type) {}

void Bishop::setup() {
    for (unsigned i = 1; i < BOARD_LENGTH; i++) {
        this->moves.push_back(new Move(i, i));
        this->moves.push_back(new Move(i, -i));
        this->moves.push_back(new Move(-i, i));
        this->moves.push_back(new Move(-i, -i));
    }
}


Knight::Knight(int color, piece_t type): Piece(color, type) {}

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


King::King(int color, piece_t type): Piece(color, type) {}

void King::setup() {
    this->moves.push_back(new Move(1, 0));
    this->moves.push_back(new Move(-1, 0));
    this->moves.push_back(new Move(0, 1));
    this->moves.push_back(new Move(0, -1));
    this->moves.push_back(new Move(1, 1));
    this->moves.push_back(new Move(-1, 1));
    this->moves.push_back(new Move(1, -1));
    this->moves.push_back(new Move(-1, -1));
    this->moves.push_back(new Move(0, 2));      //Rochade1
    this->moves.push_back(new Move(0, -2));      //Rochade2
}


Queen::Queen(int color, piece_t type): Piece(color, type) {}

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
