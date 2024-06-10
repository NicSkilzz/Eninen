#include <wx/wx.h>

class ChessBoardPanel : public wxPanel {
 public:
  ChessBoardPanel(wxWindow* parent, Board* board);

 protected:
  void OnPaint(wxPaintEvent& event);

 private:
  Board* board;
  DECLARE_EVENT_TABLE()
};