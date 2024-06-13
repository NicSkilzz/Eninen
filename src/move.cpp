#include "move.hpp"

Move::Move(int steps_rank, int steps_file): steps_rank(steps_rank), steps_file(steps_file) {}

const int Move::get_rank_change() { return this->steps_rank; }

const int Move::get_file_change() { return this->steps_file; }
