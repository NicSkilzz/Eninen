#pragma once
#include "chess_piece.h"

Piece::Piece(int color, piece_t type): color(color), type(type) {
    this->setup();
}

Pawn::Pawn(int color, piece_t type): Piece(color, type) {}
    
void Pawn::setup() {
    this->moves.push_back(new Move(1, 0));
    this->moves.push_back(new Move(2, 0));      //First step
}


Rook::Rook(int color, piece_t type): Piece(color, type) {}
    
void Rook::setup() {
    for (unsigned i = 1; i < BOARD_LENGTH - 1; i++) {
        this->moves.push_back(new Move(0, i));
        this->moves.push_back(new Move(0, -i));
        this->moves.push_back(new Move(i, 0));
        this->moves.push_back(new Move(-i, 0));
    }
}


Bishop::Bishop(int color, piece_t type): Piece(color, type) {}
    
void Bishop::setup() {
    for (unsigned i = 1; i < BOARD_LENGTH - 1; i++) {
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
    this->moves.push_back(new Move(0, 2));      //Rochade1
    this->moves.push_back(new Move(0, -2));      //Rochade2
}


Queen::Queen(int color, piece_t type): Piece(color, type) {}
    
void Queen::setup() {
    for (unsigned i = 1; i < BOARD_LENGTH - 1; i++) {
        this->moves.push_back(new Move(0, i));
        this->moves.push_back(new Move(0, -i));
        this->moves.push_back(new Move(i, 0));
        this->moves.push_back(new Move(-i, 0));
    }

    for (unsigned i = 0; i < BOARD_LENGTH - 1; i++) {
        this->moves.push_back(new Move(i, i));
        this->moves.push_back(new Move(i, -i));
        this->moves.push_back(new Move(-i, i));
        this->moves.push_back(new Move(-i, -i));
    }
}