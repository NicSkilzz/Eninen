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

  // Create bitmaps to later on display the piece .pngs
  wxBitmap bitmap(60, 60, 32);
  display_bitmap = new wxStaticBitmap(this, wxID_ANY, bitmap, wxPoint(50, 50));
  display_bitmap->SetPosition(wxPoint(0, 0));

  // Add the bitmap element to the panel
  wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
  sizer->Add(display_bitmap, 1,
             wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL);
  SetSizerAndFit(sizer);
  display_bitmap->SetMinSize(wxSize(100, 100));

  // Bind the OnClick method
  display_bitmap->Bind(wxEVT_LEFT_DOWN, [=](wxMouseEvent& event) {
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
    this->SetBackgroundColour(wxColour(118, 150, 86));
  }
}

void SquarePanel::set_piece_type(Piece* piece) {
  wxBitmap piece_bitmap = Piece::get_piece_bitmap(piece);
  this->display_bitmap->SetBitmap(piece_bitmap);
  this->display_bitmap->Refresh();
}