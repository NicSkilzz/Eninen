#include <iostream>
#include "chess_board.hpp"
using namespace std;

bool do_move(Board * board, int color);

int main() {
    bool running = true;
    Board board();

    int color;
    while (running) {
        color = WHITE;
        running = do_move(board, color);
        if ((!running) || check_mate()) break;

        color = BLACK;
        running = do_move(board, color);
        if ((!running) || check_mate()) break;
    }
    board.clean_up();
    return 0;
}


bool do_move(Board * board, int color) {
    //check if any piece can move

    //get from field
    //color from field
    //check if piece on from field
    //check where piece can be moved
    //color fields where piece can go
    //get to field
    //check if field in possible fields
    //if yes->move piece, else start over
}
