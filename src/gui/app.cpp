#include "app.hpp"

#include <wx/wx.h>

#include "board_frame.hpp"
#include "chess_board.hpp"

wxIMPLEMENT_APP(wxWidgetsApp);

/**
 * @brief Entrypoint of Application. Creates Board and Frame.
 * Runs in an infinite loop.
 * 
 * @return true 
 * @return false 
 */
bool wxWidgetsApp::OnInit() {
  Board* board = new Board();
  ChessBoardFrame* frame = new ChessBoardFrame(board);
  frame->Show(true);
  return true;
}