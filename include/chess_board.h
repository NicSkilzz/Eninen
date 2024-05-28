class Board {

    private:
        Piece* board_array[8][8];

    public:
        Board();
        Piece* access_field(int rank, int file);
        void remove_piece(int rank, int file);
        void move_piece(int source_rank, int source_file, int target_rank, int target_file);
        void set_piece(int rank, int file, Piece * piece);
        
}