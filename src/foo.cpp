#include <wx/wx.h>

class ChessBoardFrame : public wxFrame {
public:
    ChessBoardFrame(const wxString& title);

private:
    void OnPaint(wxPaintEvent& event);
    wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(ChessBoardFrame, wxFrame)
EVT_PAINT(ChessBoardFrame::OnPaint)
wxEND_EVENT_TABLE()

class wxWidgetsApp: public wxApp {
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(wxWidgetsApp);

bool wxWidgetsApp::OnInit() {
    ChessBoardFrame* frame = new ChessBoardFrame("Chess Board");
    frame->Show(true);
    return true;
}

ChessBoardFrame::ChessBoardFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 800)) {}

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

            dc.DrawRectangle(col * squareSize, row * squareSize, squareSize, squareSize);
            isWhite = !isWhite;
        }
        isWhite = !isWhite;
    }
}