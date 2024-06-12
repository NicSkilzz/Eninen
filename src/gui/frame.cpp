#include <wx/wx.h>

#include <iostream>
#include <string>

#include "../../include/board_frame.hpp"
#include "../../include/chess_board.hpp"

using std::string;

ChessBoardFrame::ChessBoardFrame(Board* board)
    : wxFrame(NULL, wxID_ANY, "Chess Board", wxDefaultPosition,
              wxSize(800, 800)) {
  this->board = board;

  m_chessBoardPanel = new ChessBoardPanel(this, this->board);
  m_chessBoardPanel->SetSize(800, 800);
  m_chessBoardPanel->SetPosition(wxPoint(0, 0));
  m_chessBoardPanel->SetBackgroundColour(wxColour(100, 150, 200));

  // m_button = new wxButton(this, wxID_ANY, "Click Me");
  // m_button->SetSize(50, 30);
  // m_button->SetPosition(wxPoint(100, 0));
  // m_button->SetBackgroundColour(wxColour(100, 100, 100));
  // Bind(wxEVT_BUTTON, &ChessBoardFrame::OnButtonClick, this, m_button->GetId());
}

void ChessBoardFrame::OnButtonClick(wxCommandEvent& event) {
  std::cout << "Hello" << std::endl;
}
