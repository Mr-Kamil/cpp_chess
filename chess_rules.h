#ifndef CHESS_RULES_H
#define CHESS_RULES_H

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>


typedef uint64_t Bitboard;

class ChessRules
{
    const Bitboard FILE_A;
    const Bitboard FILE_B;
    const Bitboard FILE_C;
    const Bitboard FILE_D;
    const Bitboard FILE_E;
    const Bitboard FILE_F;
    const Bitboard FILE_G;
    const Bitboard FILE_H;

    const Bitboard RANK_1;
    const Bitboard RANK_2;
    const Bitboard RANK_3;
    const Bitboard RANK_4;
    const Bitboard RANK_5;
    const Bitboard RANK_6;
    const Bitboard RANK_7;
    const Bitboard RANK_8;

    const Bitboard BOUNDARIES ;

    static constexpr char EMPTY = '0';
    static constexpr char PAWN_WHITE = 'P', 
                          KNIGHT_WHITE = 'N', 
                          BISHOP_WHITE = 'B', 
                          ROOK_WHITE = 'R', 
                          QUEEN_WHITE = 'Q', 
                          KING_WHITE = 'K';
    static constexpr char PAWN_BLACK = 'p', 
                          KNIGHT_BLACK = 'n', 
                          BISHOP_BLACK = 'b', 
                          ROOK_BLACK = 'r', 
                          QUEEN_BLACK = 'q', 
                          KING_BLACK = 'k';

    Bitboard white_pawns;
    Bitboard white_knights;
    Bitboard white_rooks;
    Bitboard white_bishops;
    Bitboard white_queens;
    Bitboard white_king;

    Bitboard black_pawns;
    Bitboard black_knights;
    Bitboard black_rooks;
    Bitboard black_bishops;
    Bitboard black_queens;
    Bitboard black_king;

    Bitboard white_board;
    Bitboard black_board;
    Bitboard full_board;

    Bitboard last_move_begin;
    Bitboard last_move_end;


    bool white_king_side_castling;
    bool white_queen_side_castling;

    bool black_king_side_castling;
    bool black_queen_side_castling;

public:
    bool white_to_move;
    int en_passant_square; // -1 means no en passant

    int halfmove_clock;
    int fullmove_number;

    std::vector<std::string> move_logs;
    
    const int PAWN_VALUE;
    const int KNIGHT_VALUE;
    const int BISHOP_VALUE;
    const int ROOK_VALUE;
    const int QUEEN_VALUE;
    const int KING_VALUE;

    const int checkmate;

    std::string next_move;

public:
    ChessRules();

public:
    void set_start_positions();

public:
    void reset();

public: 
    void update_board_variables();

public:
    void clear_move_logs();

private: 
    void add_move_log(std::string move_log);

private: 
    void delete_last_log_move();

public:
    Bitboard get_full_board();

public:
    char *get_char_list_board();

public:
    void get_bitboards_from_char_list(const char* char_board) ;

public:
    void print_bitboard_as_bytes(Bitboard board);

public:
    void print_graphic_bitboard(Bitboard board);

public: 
    void print_graphic_chessboard(const std::string &board_str);

private:
    int check_square_occupation(Bitboard move);

private:
    Bitboard slide_piece(
        Bitboard piece_position, int shift, Bitboard boundary_mask, 
        bool single_move=false
        );

public:
    Bitboard generate_all_rooks_moves(Bitboard rook_board);

public:
    Bitboard generate_all_bishops_moves(Bitboard bishop_board);

private:
    Bitboard generate_all_knights_moves(Bitboard knights_board);

public:
    Bitboard generate_all_queens_moves(Bitboard queen_board);

private:
    Bitboard generate_queen_side_castling_move(Bitboard king_board);

private:
    Bitboard generate_king_side_castling_move(Bitboard king_board);

private:
    Bitboard generate_all_kings_moves(Bitboard king_board);

private:
    Bitboard slide_pawn(Bitboard pawn_position, int shift, Bitboard boundary_mask) ;

private:
    Bitboard slide_double_pawn(Bitboard pawn_position, int shift);

private:
    Bitboard capture_pawn(Bitboard pawn_position, int shift, Bitboard boundary_mask);

private:
    Bitboard generate_en_passant_move(Bitboard pawn_position);

private:
    Bitboard en_passant_move_old(Bitboard pawn_position);

private:
    void check_en_passant_moves();

public:
    bool check_is_move_str_valid(std::string &move);

private:
    Bitboard generate_all_pawns_moves(Bitboard pawn_board);

private:
    void clear_bit(uint64_t &bitboard, int square);

private:
    void set_bit(uint64_t &bitboard, int square);

public:
    std::pair<int, int> move_to_square_indices(const std::string &move);

public:
    void apply_move_startpos(const std::string &move);

void append_piece_or_empty(std::string &position, int &empty_count, char piece);

public:
    std::string generate_current_fen();

public:
    void apply_move_fen(const std::string &fen);

private:
    void update_all_moves_str(std::vector<std::string> &all_moves_str, 
    Bitboard start_square, Bitboard moves_end_squares);

public:
    std::vector<std::string> get_all_moves_str(std::vector<std::string> &all_moves_str);

public:
    Bitboard get_all_moves_end();

public:
    void validate_moves_str(std::vector<std::string> &all_moves_str);

public:
    std::vector<std::string> get_all_valid_moves_str();

public:
    void undo_move();

private:
    int _bitboard_to_index(Bitboard bitboard);

private:
    std::string _index_to_square(int index);

public:
    std::string bitboards_to_move(Bitboard move_begin, Bitboard move_end);

public:
    std::string get_best_move_nega_max(int depth);

public:
    int find_nega_max_move_alpha_beta(
        int depth, int max_depth, int turn_multiplier, int alpha, int beta
        );

public:
    int score_material();
};

#endif // CHESS_RULES_H
