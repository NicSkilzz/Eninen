#include "board_panel.hpp"

#include <wx/wx.h>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "chess_board.hpp"
#include "chess_piece.hpp"
#include "move.hpp"
#include "square_panel.hpp"

ChessBoardPanel::ChessBoardPanel(wxWindow* parent, Board* board)
    : wxPanel(parent, wxID_ANY), board(board), selected_piece(nullptr) {
  const int square_size = 100;
  // Create square tiles with set color and piece types
  for (int rank = 0; rank < 8; rank++) {
    for (int file = 0; file < 8; file++) {
      int color = (rank + file) % 2 == 0 ? BLACK : WHITE;
      this->square_panels[rank][file] =
          new SquarePanel(this, rank, file, color);
      this->square_panels[rank][file]->set_piece_type(
          board->access_field(rank, file));

      // position square on panel
      this->square_panels[rank][file]->SetSize(square_size, square_size);
      this->square_panels[rank][file]->SetPosition(
          wxPoint(rank * square_size, file * square_size));
    }
  }
}

void ChessBoardPanel::OnPanelClick(wxMouseEvent& event, int rank, int file) {
  // If user clicks a highlighted panel (possible move) -> execute move
  // Else: Highlight possible moves of piece in the now clicked panel
  if (std::find(
          this->highlighted_panels.begin(), this->highlighted_panels.end(),
          this->square_panels[rank][file]) != this->highlighted_panels.end()) {
    // this->move_seleced_piece_to(rank, file);
    this->execute_move(this->panel_to_move[this->square_panels[rank][file]]);
  } else if (this->board->access_field(rank, file) != nullptr && this->board->access_field(rank, file)->get_color() == board->get_current_player()) {
    this->select_panel(rank, file);
    this->highlight_possible_moves(this->board->access_field(rank, file));
  } else {
    this->reset_highlights();
  }
}

void ChessBoardPanel::execute_move(ChessMove* move) {
  this->board->execute_move(move);
  this->update_board();
  this->reset_highlights();
}

void ChessBoardPanel::highlight_possible_moves(Piece* piece) {
  this->reset_highlights();
  if (piece == nullptr) {
    return;
  }

  std::vector<ChessMove*> usable_moves = piece->get_usable_moves();
  for (int i = 0; i < usable_moves.size(); i++) {
    ChessMove* current_move = usable_moves[i];
    int new_rank = piece->get_rank() + current_move->get_rank_change();
    int new_file = piece->get_file() + current_move->get_file_change();

    SquarePanel* target_panel = this->square_panels[new_rank][new_file];
    target_panel->highlight();
    this->panel_to_move[target_panel] = current_move;
    this->highlighted_panels.push_back(this->square_panels[new_rank][new_file]);
  }
}

void ChessBoardPanel::update_board() {
  for (int rank = 0; rank < 8; rank++) {
    for (int file = 0; file < 8; file++) {
      this->square_panels[rank][file]->set_piece_type(
          board->access_field(rank, file));
    }
  }
}

void ChessBoardPanel::reset_highlights() {
  this->panel_to_move = {};
  this->highlighted_panels = {};
  for (int rank = 0; rank < 8; rank++) {
    for (int file = 0; file < 8; file++) {
      this->square_panels[rank][file]->remove_highlight();
    }
  }
}

void ChessBoardPanel::select_panel(int rank, int file) {
  this->selected_piece = this->board->access_field(rank, file);
}