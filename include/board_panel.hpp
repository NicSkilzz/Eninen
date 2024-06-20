#pragma once
#include <wx/wx.h>

#include <vector>

#include "chess_board.hpp"
#include "chess_piece.hpp"
#include "square_panel.hpp"

/**
 * @brief A large wxPanel that displays a given chess board.
 * Manages gui and click events for piece movement.
 *
 */
class ChessBoardPanel : public wxPanel {
 public:
  ChessBoardPanel(wxWindow* parent, Board* board);
  void OnPanelClick(wxMouseEvent& event, int rank, int file);

 private:
  /**
   * @brief Highlight the squares the given piece
   * can move to.
   *
   * @param piece Piece to highlight moves for.
   */
  void highlight_possible_moves(Piece* piece);
  /**
   * @brief Remove highlights from all squares. Typically
   * called after move was made.
   *
   */
  void reset_highlights();
  /**
   * @brief Effecively move the currently selected piece
   * in the Board instance of this class to the desired
   * location and bring changes to ui.
   * 
   * @param rank Target rank for the selected piece.
   * @param file Target file for the selected piece.
   */
  void move_seleced_piece_to(int rank, int file);
  /**
   * @brief Store, that this piece has been clicked. Important
   * for moving pieces.
   * 
   * @param rank Clicked rank.
   * @param file Clicked file.
   */
  void select_panel(int rank, int file);
  /**
   * @brief Update ui according to changes in the Board instance
   * of this class.
   *
   */
  void update_board();
  Board* board;
  SquarePanel* square_panels[8][8];
  Piece* selected_piece;
  std::vector<SquarePanel*> highlighted_panels;
};