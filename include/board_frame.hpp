#pragma once
#include <wx/wx.h>

#include "board_panel.hpp"
#include "chess_board.hpp"

class ChessBoardFrame : public wxFrame {
 public:
  ChessBoardFrame(Board* board);

 private:
  ChessBoardPanel* m_chessBoardPanel;
  wxButton* m_button;
  Board* board;
  void OnButtonClick(wxCommandEvent& event);
};