#include <wx/wx.h>
#include <string>
#include <iostream>
#include "../../include/chess_board.hpp"
#include "../../include/board_panel.hpp"
#include "../../include/chess_piece.hpp"

using std::string;

BEGIN_EVENT_TABLE(ChessBoardPanel, wxPanel)
EVT_PAINT(ChessBoardPanel::OnPaint)
END_EVENT_TABLE()

ChessBoardPanel::ChessBoardPanel(wxWindow* parent, Board* board)
    : wxPanel(parent, wxID_ANY), board(board) {}

void ChessBoardPanel::OnPaint(wxPaintEvent& event) {
  wxPaintDC dc(this);
  wxBrush whiteBrush(*wxWHITE_BRUSH);
  wxBrush blackBrush(*wxBLACK_BRUSH);

  int squareSize = 100;
  bool isWhite = true;

  for (int row = 0; row < 8; ++row) {
    for (int col = 0; col < 8; ++col) {
      if (isWhite) {
        dc.SetBrush(whiteBrush);
      } else {
        dc.SetBrush(blackBrush);
      }
      string piece_str = " ";
      wxColour piece_color;
      Piece* piece_ptr = this->board->access_field(row, col);
      if (piece_ptr != nullptr) {
        switch (piece_ptr->get_type()) {
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
        if (piece_ptr->get_color() == WHITE) {
          piece_color = wxColour(14737632);
        } else {
          piece_color = wxColour(5263440);
        }
      }

      dc.DrawRectangle(col * squareSize, row * squareSize, squareSize,
                       squareSize);
      dc.SetTextForeground(piece_color);
      dc.SetFont(wxFont(50, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                        wxFONTWEIGHT_NORMAL));
      dc.DrawLabel(piece_str, wxRect(col * squareSize + squareSize / 5,
                                     row * squareSize + squareSize / 6,
                                     squareSize, squareSize));
      isWhite = !isWhite;
    }
    isWhite = !isWhite;
  }
}