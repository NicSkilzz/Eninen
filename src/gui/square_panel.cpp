#include "../../include/square_panel.hpp"

#include <wx/wx.h>

#include <iostream>
#include <string>

#include "../../include/chess_piece.hpp"

SquarePanel::SquarePanel(wxWindow* parent) : wxPanel(parent, wxID_ANY) {
  displayText = new wxStaticText(this, wxID_ANY, " ");
  displayText->SetPosition(wxPoint(0, 0));
  displayText->SetFont(wxFont(33, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                              wxFONTWEIGHT_NORMAL));
  wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
  sizer->Add(displayText, 1, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL);
  SetSizerAndFit(sizer);
  displayText->SetMinSize(wxSize(50, 50));
}

void SquarePanel::setPieceType(Piece* piece) {
  std::string piece_str = " ";
  if (piece != nullptr) {
    if (piece->get_color() == WHITE) {
      this->displayText->SetForegroundColour(wxColour(14737632));
    } else {
      this->displayText->SetForegroundColour(wxColour(5263440));
    }
    switch (piece->get_type()) {
      case PAWN:
        piece_str = "P";
        break;
      case QUEEN:
        piece_str = "Q";
        break;
      case ROOK:
        piece_str = "R";
        break;
      case BISHOP:
        piece_str = "B";
        break;
      case KNIGHT:
        piece_str = "J";
        break;
      case KING:
        piece_str = "K";
        break;

      default:
        break;
    }
  }
  this->displayText->SetLabel(piece_str);
}