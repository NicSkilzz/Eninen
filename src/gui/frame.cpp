#include <wx/wx.h>

#include <iostream>
#include <string>

#include "../../include/board_frame.hpp"
#include "../../include/chess_board.hpp"

using std::string;

ChessBoardFrame::ChessBoardFrame(Board* board)
    : wxFrame(NULL, wxID_ANY, "Chess Board", wxDefaultPosition,
              wxSize(800, 900)) {
  this->board = board;
  m_chessBoardPanel = new ChessBoardPanel(this, this->board);
  m_button = new wxButton(this, wxID_ANY, "Click Me");
  Bind(wxEVT_BUTTON, &ChessBoardFrame::OnButtonClick, this, m_button->GetId());
  wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
  sizer->Add(m_button, 0, wxALIGN_CENTER, 10);
  sizer->Add(m_chessBoardPanel, 1, wxEXPAND);
  SetSizer(sizer);
}

void ChessBoardFrame::OnButtonClick(wxCommandEvent& event) {
  std::cout << "Hello" << std::endl;
}
