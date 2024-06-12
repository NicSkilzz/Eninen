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

void ChessBoardPanel::OnPanelClick(wxMouseEvent& event, int rank, int file) {
  if (this->board->access_field(rank, file) != nullptr) {
    Piece* piece = this->board->access_field(rank, file);
    // for (int i = 0; i < piece->usable_moves().size(); i++) {
    //   abc = piece->usable_moves()[i];
    //   this->squarePanels[rank + move->get_rank_change()][file +
    //   move->get_file_change()]->SetBackgroundColour(wxColour(0, 255, 0));
    // }
  }
}