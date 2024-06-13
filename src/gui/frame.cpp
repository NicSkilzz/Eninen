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

  m_chessBoardPanel = new ChessBoardPanel(this, this->board);
  m_chessBoardPanel->SetSize(800, 800);
  m_chessBoardPanel->SetPosition(wxPoint(0, 0));
  m_chessBoardPanel->SetBackgroundColour(wxColour(100, 150, 200));
}
