#include "square_panel.hpp"

#include <wx/wx.h>

#include <functional>
#include <iostream>
#include <string>

#include "board_panel.hpp"
#include "chess_piece.hpp"

SquarePanel::SquarePanel(wxWindow* parent, int rank, int file, int color)
    : wxPanel(parent, wxID_ANY), rank(rank), file(file), color(color) {
  // Set inital background color
  this->remove_highlight();

  // Create text that is the piece icon for now
  display_text = new wxStaticText(this, wxID_ANY, " ");
  display_text->SetPosition(wxPoint(0, 0));
  display_text->SetFont(wxFont(33, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                               wxFONTWEIGHT_NORMAL));

  // Add the text element to the panel
  wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
  sizer->Add(display_text, 1,
             wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL);
  SetSizerAndFit(sizer);
  display_text->SetMinSize(wxSize(100, 100));

  // Bind the OnClick method
  display_text->Bind(wxEVT_LEFT_DOWN, [=](wxMouseEvent& event) {
    static_cast<ChessBoardPanel*>(parent)->OnPanelClick(event, rank, file);
  });
}

void SquarePanel::highlight() {
  this->SetBackgroundColour(wxColour(0, 255, 0));
}

void SquarePanel::remove_highlight() {
  if (this->color == WHITE) {
    this->SetBackgroundColour(wxColour(255, 255, 255));
  } else {
    this->SetBackgroundColour(wxColour(0, 0, 0));
  }
}

void SquarePanel::set_piece_type(Piece* piece) {
  std::string piece_str = Piece::get_piece_icon(piece);
  this->display_text->SetLabel(piece_str);
  
  if (piece != nullptr) {
    if (piece->get_color() == WHITE) {
      this->display_text->SetForegroundColour(wxColour(14737632));
    } else {
      this->display_text->SetForegroundColour(wxColour(5263440));
    }
  }
}