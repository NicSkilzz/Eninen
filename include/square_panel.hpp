#pragma once
#include <wx/wx.h>

#include "chess_piece.hpp"

class SquarePanel : public wxPanel {
 public:
  SquarePanel(wxWindow* parent);
  void setPieceType(Piece* piece);

 private:
  wxStaticText* displayText;
};
