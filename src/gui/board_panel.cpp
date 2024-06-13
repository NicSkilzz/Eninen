#include "board_panel.hpp"

#include <wx/wx.h>

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

void ChessBoardPanel::resetHighlights() {
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

void ChessBoardPanel::OnPanelClick(wxMouseEvent& event, int rank, int file) {
  this->resetHighlights();
  if (this->board->access_field(rank, file) != nullptr) {
    Piece* piece = this->board->access_field(rank, file);
    std::cout << "Possible Moves: " << piece->usable_moves().size()
              << std::endl;
    for (int i = 0; i < piece->usable_moves().size(); i++) {
      std::cout << "Move: " << i << std::endl;
      int rankChange = piece->usable_moves()[i]->get_rank_change();
      int fileChange = piece->usable_moves()[i]->get_file_change();
      std::cout << "Rank and File Change: " << rankChange << " - " << fileChange
                << std::endl;
      int new_rank = rank + rankChange;
      int new_file = file + fileChange;
      if (new_rank > 7 || new_rank < 0 || new_file > 7 || new_file < 0) {
        std::cout << "Illegal Move: Breaking Board barrier" << std::endl;
      } else {
        this->squarePanels[rank + rankChange][file + fileChange]
            ->SetBackgroundColour(wxColour(0, 255, 0));
      }
    }
  } else {
    std::cout << "Empty Field" << std::endl;
  }
  std::cout << std::endl;
}