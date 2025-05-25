#ifndef CHESS_RULES_H
#define CHESS_RULES_H

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>

typedef uint64_t Bitboard;
class ChessAlgorithm;

class ChessRules
{
    friend class ChessAlgorithm;

    static constexpr Bitboard FILE_A = 0x01'01'01'01'01'01'01'01ULL;
    static constexpr Bitboard FILE_B = 0x02'02'02'02'02'02'02'02ULL;
    static constexpr Bitboard FILE_C = 0x04'04'04'04'04'04'04'04ULL;
    static constexpr Bitboard FILE_D = 0x08'08'08'08'08'08'08'08ULL;
    static constexpr Bitboard FILE_E = 0x10'10'10'10'10'10'10'10ULL;
    static constexpr Bitboard FILE_F = 0x20'20'20'20'20'20'20'20ULL;
    static constexpr Bitboard FILE_G = 0x40'40'40'40'40'40'40'40ULL;
    static constexpr Bitboard FILE_H = 0x80'80'80'80'80'80'80'80ULL;

    static constexpr Bitboard RANK_1 = 0x00'00'00'00'00'00'00'FFULL;
    static constexpr Bitboard RANK_2 = 0x00'00'00'00'00'00'FF'00ULL;
    static constexpr Bitboard RANK_3 = 0x00'00'00'00'00'FF'00'00ULL;
    static constexpr Bitboard RANK_4 = 0x00'00'00'00'FF'00'00'00ULL;
    static constexpr Bitboard RANK_5 = 0x00'00'00'FF'00'00'00'00ULL;
    static constexpr Bitboard RANK_6 = 0x00'00'FF'00'00'00'00'00ULL;
    static constexpr Bitboard RANK_7 = 0x00'FF'00'00'00'00'00'00ULL;
    static constexpr Bitboard RANK_8 = 0xFF'00'00'00'00'00'00'00ULL;

    static constexpr Bitboard BOUNDARIES = FILE_A | FILE_H | RANK_1 | RANK_8;

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

    std::string next_move;

    ChessRules();

    void set_new_game();

    void set_start_positions();

    void clear_board();

    void set_board_starting_variables();

    void clear_move_logs();

    void add_move_log(const std::string &move_log);

    void delete_last_log_move();

    int check_square_occupation(Bitboard &move) const;

    Bitboard slide_piece(
        const Bitboard &piece_position, int shift, 
        const Bitboard &boundary_mask, bool single_move=false
    );

    Bitboard generate_all_pawns_moves(const Bitboard &pawn_board);

    Bitboard generate_all_knights_moves(const Bitboard &knights_board);

    Bitboard generate_all_rooks_moves(const Bitboard &rook_board);

    Bitboard generate_all_bishops_moves(const Bitboard &bishop_board);

    Bitboard generate_all_queens_moves(const Bitboard &queen_board);
    
    Bitboard generate_queen_side_castling_move(const Bitboard &king_board);

    Bitboard generate_king_side_castling_move(const Bitboard &king_board);

    Bitboard generate_all_kings_moves(const Bitboard &king_board);

    Bitboard slide_pawn(
        const Bitboard &pawn_position, int shift, const Bitboard &boundary_mask
    );

    Bitboard slide_double_pawn(const Bitboard &pawn_position, int shift);
    
    Bitboard capture_pawn(
        const Bitboard &pawn_position, int shift, const Bitboard &boundary_mask
    );
    
    Bitboard generate_en_passant_move(const Bitboard &pawn_position);

    void check_en_passant_moves();

    void clear_bit(uint64_t &bitboard, int square) const;

    void set_bit(uint64_t &bitboard, int square) const;

    void update_all_moves_str(
        std::vector<std::string> &all_moves_str, 
        Bitboard start_square, Bitboard &moves_end_squares
    );

    Bitboard get_full_board() const;

    char *get_char_list_board() const;

    bool check_is_move_str_valid(std::string &move);

    std::pair<int, int> move_to_square_indices(const std::string &move);

    void apply_moves_startpos(std::stringstream &moves);

    void apply_move_startpos(const std::string &move);

    void append_piece_or_empty(
        std::string &position, int &empty_count, const char &piece
    ) const;

    std::string generate_current_fen() const;

    void apply_move_fen(const std::string &fen);

    std::vector<std::string> get_all_moves_str(
        std::vector<std::string> &all_moves_str
    );

    Bitboard get_all_moves_end();

    void validate_moves_str(std::vector<std::string> &all_moves_str);

    std::vector<std::string> get_all_valid_moves_str();

    void undo_move();

    int bitboard_to_index(Bitboard &bitboard) const;

    std::string index_to_square(int index) const;

    std::string bitboards_to_move(
        Bitboard move_begin, Bitboard move_end
    ) const;
};

#endif // CHESS_RULES_H
