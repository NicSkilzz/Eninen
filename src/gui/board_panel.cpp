#include "../../include/board_panel.hpp"

#include <wx/wx.h>

#include <iostream>
#include <string>
#include <vector>

#include "../../include/chess_board.hpp"
#include "../../include/chess_piece.hpp"
#include "../../include/moves.hpp"
#include "../../include/square_panel.hpp"

using std::string;

ChessBoardPanel::ChessBoardPanel(wxWindow* parent, Board* board)
    : wxPanel(parent, wxID_ANY), board(board) {
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
    std::vector<Move*> usableMoves = piece->usable_moves();
    // std::vector<int[2]> targetSquares;
    // for (unsigned i = 0; i < usableMoves.size(); i++) {
    //   targetSquares.push_back([ piece->get_rank(), 0 ]);
    // }
  }
}