#include <wx/wx.h>
#include "chess_board.hpp"
#include "board_panel.hpp"

class ChessBoardFrame : public wxFrame {
 public:
  ChessBoardFrame(Board* board);

 private:
  ChessBoardPanel* m_chessBoardPanel;
  wxButton* m_button;
  Board* board;
  void OnButtonClick(wxCommandEvent& event);
};