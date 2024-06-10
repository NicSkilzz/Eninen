#include <wx/wx.h>
#include "../../include/app.hpp"
#include "../../include/board_frame.hpp"

wxIMPLEMENT_APP(wxWidgetsApp);

bool wxWidgetsApp::OnInit() {
  Board* board = new Board();
  ChessBoardFrame* frame = new ChessBoardFrame(board);
  frame->Show(true);
  return true;
}