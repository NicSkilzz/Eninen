#pragma once
#include <wx/wx.h>

#include "board_panel.hpp"
#include "chess_board.hpp"

/**
 * @brief The window that is displayed.
 * Displays the ChessBoardPanel.
 * 
 */
class ChessBoardFrame : public wxFrame {
 public:
  ChessBoardFrame(Board* board);

 private:
  Board* board;
  ChessBoardPanel* board_panel;
};