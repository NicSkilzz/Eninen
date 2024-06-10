#include <wx/wx.h>

#include <string>

#include "../../include/chess_board.hpp"

using std::string;

class wxWidgetsApp : public wxApp {
 public:
  virtual bool OnInit();
};

class ChessBoardFrame : public wxFrame {
 public:
  ChessBoardFrame(Board* board);

 private:
  void OnPaint(wxPaintEvent& event);
  Board* board;
  wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(ChessBoardFrame, wxFrame)
    EVT_PAINT(ChessBoardFrame::OnPaint) wxEND_EVENT_TABLE()
        wxIMPLEMENT_APP(wxWidgetsApp);

bool wxWidgetsApp::OnInit() {
  Board* board = new Board();
  ChessBoardFrame* frame = new ChessBoardFrame(board);
  frame->Show(true);
  return true;
}

ChessBoardFrame::ChessBoardFrame(Board* board)
    : wxFrame(NULL, wxID_ANY, "Chess Board", wxDefaultPosition,
              wxSize(800, 800)) {
  this->board = board;
}

void ChessBoardFrame::OnPaint(wxPaintEvent& event) {
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
                               row * squareSize + squareSize / 6, squareSize,
                               squareSize));
      isWhite = !isWhite;
    }
    isWhite = !isWhite;
  }
}