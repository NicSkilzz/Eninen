#pragma once
#include <wx/wx.h>
#include "chess_board.hpp"
#include "square_panel.hpp"

class ChessBoardPanel : public wxPanel {
 public:
  ChessBoardPanel(wxWindow* parent, Board* board);

 private:
  void OnPanelClick(wxMouseEvent& event, int rank, int file);
  Board* board;
  SquarePanel* squarePanels[8][8];
};