#pragma once

class Move {
 public:
  Move(int steps_rank, int steps_file);
  const int get_rank_change();
  const int get_file_change();

 private:
  int steps_rank;
  int steps_file;
};
