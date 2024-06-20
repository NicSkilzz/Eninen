#pragma once
#include <wx/wx.h>

#include "chess_piece.hpp"

/**
 * @brief A single square of a chess board. Contains piece
 * depiction and potential highlights.
 * 
 */
class SquarePanel : public wxPanel {
 public:
  SquarePanel(wxWindow* parent, int rank, int file, int color);
  /**
   * @brief Set the piece type object.
   * Updates the displayed icon.
   * 
   * @param piece Pointer to piece, may be nullptr.
   */
  void set_piece_type(Piece* piece);
  /**
   * @brief Highlights this square, by adding
   * a visual hint.
   * 
   */
  void highlight();
  /**
   * @brief Removes highlight and resets square
   * to unhighlighted form.
   * 
   */
  void remove_highlight();

 private:
  wxStaticText* display_text;
  int rank;
  int file;
  int color;
};
