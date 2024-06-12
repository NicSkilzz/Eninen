#include "../../include/app.hpp"

#include <wx/wx.h>

#include "../../include/board_frame.hpp"
#include "../../include/move.hpp"

wxIMPLEMENT_APP(wxWidgetsApp);

bool wxWidgetsApp::OnInit() {
  Board* board = new Board();
  ChessBoardFrame* frame = new ChessBoardFrame(board);
  frame->Show(true);
  return true;
}