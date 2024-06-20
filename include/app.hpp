#pragma once
#include <wx/wx.h>

/**
 * @brief This is what is executed when the program is started.
 * Runs the frame and the chess game in an infinite loop.
 * 
 */
class wxWidgetsApp : public wxApp {
 public:
  virtual bool OnInit();
};