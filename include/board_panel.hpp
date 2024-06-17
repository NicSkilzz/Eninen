#pragma once
#include <wx/wx.h>

#include "chess_board.hpp"
#include "square_panel.hpp"
#include "chess_piece.hpp"
#include <vector>

class ChessBoardPanel : public wxPanel {
 public:
  ChessBoardPanel(wxWindow* parent, Board* board);

 private:
  void OnPanelClick(wxMouseEvent& event, int rank, int file);
  void highlightPossibleMoves(int sourceRank, int sourceFile);
  void resetHighlights();
  void selectPanel(int rank, int file);
  void updateBoard();
  Board* board;
  SquarePanel* squarePanels[8][8];
  SquarePanel* selectedPanel;
  std::vector<SquarePanel*> highlightedPanels;
  Piece* selectedPiece;
};