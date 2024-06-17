#include "board_panel.hpp"

#include <wx/wx.h>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "chess_board.hpp"
#include "chess_piece.hpp"
#include "move.hpp"
#include "square_panel.hpp"

ChessBoardPanel::ChessBoardPanel(wxWindow* parent, Board* board)
    : wxPanel(parent, wxID_ANY), board(board) {
  // Move* move;
  this->selectedPanel = nullptr;
  this->selectedPiece = nullptr;
  this->highlightedPanels;
  const int squareSize = 100;
  for (int rank = 0; rank < 8; rank++) {
    for (int file = 0; file < 8; file++) {
      this->squarePanels[rank][file] = new SquarePanel(this);
      this->squarePanels[rank][file]->SetSize(squareSize, squareSize);
      this->squarePanels[rank][file]->SetPosition(
          wxPoint(rank * squareSize, file * squareSize));
      this->squarePanels[rank][file]->setPieceType(
          board->access_field(rank, file));
      if ((rank + file) % 2 == 0) {
        this->squarePanels[rank][file]->SetBackgroundColour(wxColour(0, 0, 0));
      } else {
        this->squarePanels[rank][file]->SetBackgroundColour(
            wxColour(255, 255, 255));
      }
      this->squarePanels[rank][file]->Bind(
          wxEVT_LEFT_DOWN, [this, rank, file](wxMouseEvent& event) {
            (this->*(&ChessBoardPanel::OnPanelClick))(event, rank, file);
          });
    }
  }
}

void ChessBoardPanel::updateBoard() {
  for (int rank = 0; rank < 8; rank++) {
    for (int file = 0; file < 8; file++) {
      this->squarePanels[rank][file]->setPieceType(
          board->access_field(rank, file));
    }
  }
}

void ChessBoardPanel::resetHighlights() {
  this->highlightedPanels = {};
  for (int rank = 0; rank < 8; rank++) {
    for (int file = 0; file < 8; file++) {
      if ((rank + file) % 2 == 0) {
        this->squarePanels[rank][file]->SetBackgroundColour(wxColour(0, 0, 0));
      } else {
        this->squarePanels[rank][file]->SetBackgroundColour(
            wxColour(255, 255, 255));
      }
    }
  }
}

void ChessBoardPanel::selectPanel(int rank, int file) {
  this->selectedPanel = this->squarePanels[rank][file];
  this->selectedPiece = this->board->access_field(rank, file);
}

void ChessBoardPanel::highlightPossibleMoves(int sourceRank, int sourceFile) {
  Piece* piece = this->board->access_field(sourceRank, sourceFile);
  std::cout << "Possible Moves: " << piece->usable_moves().size() << std::endl;
  for (int i = 0; i < piece->usable_moves().size(); i++) {
    std::cout << "Move: " << i << std::endl;
    int rankChange = piece->usable_moves()[i]->get_rank_change();
    int fileChange = piece->usable_moves()[i]->get_file_change();
    std::cout << "Rank and File Change: " << rankChange << " - " << fileChange
              << std::endl;
    std::cout << "Source Rank and File: " << sourceRank << " - " << sourceFile
              << std::endl;
    int new_rank = sourceRank + rankChange;
    int new_file = sourceFile + fileChange;
    if (new_rank > 7 || new_rank < 0 || new_file > 7 || new_file < 0) {
      std::cout << "Illegal Move: Breaking Board barrier" << std::endl;
    } else {
      this->squarePanels[sourceRank + rankChange][sourceFile + fileChange]
          ->SetBackgroundColour(wxColour(0, 255, 0));
      this->highlightedPanels.push_back(
          this->squarePanels[sourceRank + rankChange][sourceFile + fileChange]);
    }
  }
}

void ChessBoardPanel::OnPanelClick(wxMouseEvent& event, int rank, int file) {
  Piece* piece = this->board->access_field(rank, file);
  if (this->selectedPanel != nullptr &&
      std::find(this->highlightedPanels.begin(), this->highlightedPanels.end(),
                this->squarePanels[rank][file]) !=
          this->highlightedPanels.end()) {
    std::cout << "Executing move" << std::endl;
    // try to execute move
    int currentPieceRank = this->selectedPiece->get_rank();
    int currentPieceFile = this->selectedPiece->get_file();
    std::cout << "got rank and file of piece" << std::endl;
    this->board->move_piece(currentPieceRank, currentPieceFile, rank, file);
    std::cout << "Moving visually" << std::endl;
    this->updateBoard();
    this->resetHighlights();
  } else {
    // highlight possible moves
    this->resetHighlights();
    this->selectPanel(rank, file);
    if (this->board->access_field(rank, file) != nullptr) {
      this->highlightPossibleMoves(rank, file);
    } else {
      std::cout << "Empty Field" << std::endl;
    }
  }
  std::cout << std::endl;
}