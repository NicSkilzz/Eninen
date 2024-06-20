#include <wx/wx.h>

#include <iostream>
#include <string>

#include "board_frame.hpp"
#include "chess_board.hpp"
#include "move.hpp"

ChessBoardFrame::ChessBoardFrame(Board* board)
    : wxFrame(NULL, wxID_ANY, "Chess Board", wxDefaultPosition,
              wxSize(800, 800)) {
  this->board = board;

  board_panel = new ChessBoardPanel(this, this->board);
  board_panel->SetSize(800, 800);
  board_panel->SetPosition(wxPoint(0, 0));
  board_panel->SetBackgroundColour(wxColour(100, 150, 200));
}
