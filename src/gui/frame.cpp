#include <wx/wx.h>
#include "../../include/chess_board.hpp"
#include "../../include/chess_piece.hpp"
// #include "../../include/moves.hpp"

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
EVT_PAINT(ChessBoardFrame::OnPaint)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(wxWidgetsApp);

bool wxWidgetsApp::OnInit() {
  Board* board = new Board();
  ChessBoardFrame* frame = new ChessBoardFrame(board);
  frame->Show(true);
  return true;
}

ChessBoardFrame::ChessBoardFrame(Board* board)
    : wxFrame(NULL, wxID_ANY, "Chess Board", wxDefaultPosition, wxSize(800, 800)): board(board) {}

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

      dc.DrawRectangle(col * squareSize, row * squareSize, squareSize,
                       squareSize);
      dc.SetFont(wxFont(40, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
      dc.DrawLabel("h", wxRect(col * squareSize + squareSize / 4, row * squareSize + squareSize / 4, squareSize,
                       squareSize));
      isWhite = !isWhite;
    }
    isWhite = !isWhite;
  }
}