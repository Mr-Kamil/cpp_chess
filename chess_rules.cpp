#include "chess_rules.h"

/*
Bitboard
            A  B  C  D  E  F  G  H
bits:    8  0  0  0  0  0  0  0  1  8     bytes: 0x80'00'00'00'00'00'00'00ULL
bits:    7  0  0  0  0  0  0  1  0  7     bytes: 0x00'40'00'00'00'00'00'00ULL
bits:    6  0  0  0  0  0  1  0  0  6     bytes: 0x00'00'20'00'00'00'00'00ULL
bits:    5  0  0  0  0  1  0  0  0  5     bytes: 0x00'00'00'10'00'00'00'00ULL
bits:    4  0  0  0  1  0  0  0  0  4     bytes: 0x00'00'00'00'08'00'00'00ULL
bits:    3  0  0  1  0  0  0  0  0  3     bytes: 0x00'00'00'00'00'04'00'00ULL
bits:    2  0  1  0  0  0  0  0  0  2     bytes: 0x00'00'00'00'00'00'02'00ULL
bits:    1  1  0  0  0  0  0  0  0  1     bytes: 0x00'00'00'00'00'00'00'01ULL
            A  B  C  D  E  F  G  H

           A  B  C  D  E  F  G  H
        8  r  n  b  q  k  b  n  r  8     
        7  p  p  p  p  p  p  p  p  7     
        6  0  0  0  0  0  0  0  0  6     
        5  0  0  0  0  0  0  0  0  5     
        4  0  0  0  0  0  0  0  0  4     
        3  0  0  0  0  0  0  0  0  3     
        2  P  P  P  P  P  P  P  P  2     
        1  R  N  B  Q  K  B  N  R  1     
           A  B  C  D  E  F  G  H
*/


ChessRules::ChessRules()
{
    this->set_new_game();
}

void ChessRules::set_new_game()
{
    this->move_logs = {};
    this->set_start_positions();
    this->set_board_starting_variables();
}

void ChessRules::set_start_positions()
{
    this->white_pawns = 0x00'00'00'00'00'00'FF'00ULL;
    this->white_knights = 0x00'00'00'00'00'00'00'42ULL;
    this->white_rooks = 0x00'00'00'00'00'00'00'81ULL;
    this->white_bishops = 0x00'00'00'00'00'00'00'24ULL;
    this->white_queens = 0x00'00'00'00'00'00'00'08ULL;
    this->white_king = 0x00'00'00'00'00'00'00'10ULL;

    this->black_pawns = 0x00'FF'00'00'00'00'00'00ULL;
    this->black_knights = 0x42'00'00'00'00'00'00'00ULL;
    this->black_rooks = 0x81'00'00'00'00'00'00'00ULL;
    this->black_bishops = 0x24'00'00'00'00'00'00'00ULL;
    this->black_queens = 0x08'00'00'00'00'00'00'00ULL;
    this->black_king = 0x10'00'00'00'00'00'00'00ULL;

    this->white_board = white_pawns | white_knights | white_rooks |
                        white_bishops | white_queens | white_king;
    this->black_board = black_pawns | black_knights | black_rooks |
                        black_bishops | black_queens | black_king;
    this->full_board = white_board | black_board;
}

void ChessRules::clear_board()
{
    this->white_pawns = 0x00'00'00'00'00'00'00'00ULL;
    this->white_knights = 0x00'00'00'00'00'00'00'00ULL;
    this->white_rooks = 0x00'00'00'00'00'00'00'00ULL;
    this->white_bishops = 0x00'00'00'00'00'00'00'00ULL;
    this->white_queens = 0x00'00'00'00'00'00'00'00ULL;
    this->white_king = 0x00'00'00'00'00'00'00'00ULL;

    this->black_pawns = 0x00'00'00'00'00'00'00'00ULL;
    this->black_knights = 0x00'00'00'00'00'00'00'00ULL;
    this->black_rooks = 0x00'00'00'00'00'00'00'00ULL;
    this->black_bishops = 0x00'00'00'00'00'00'00'00ULL;
    this->black_queens = 0x00'00'00'00'00'00'00'00ULL;
    this->black_king = 0x00'00'00'00'00'00'00'00ULL;

    this->set_board_starting_variables();
    this->clear_move_logs();
}

void ChessRules::set_board_starting_variables()
{
    this->last_move_begin = 0ULL;
    this->last_move_end = 0ULL;

    this->white_king_side_castling = true;
    this->white_queen_side_castling = true;

    this->black_king_side_castling = true;
    this->black_queen_side_castling = true;

    this->white_to_move = true;
    this->en_passant_square = -1;

    this->halfmove_clock = 0;
    this->fullmove_number = 0;
}

void ChessRules::clear_move_logs()
{
    this->move_logs.clear();
}

void ChessRules::add_move_log(const std::string &move_log)
{
    this->move_logs.push_back(move_log);
}

void ChessRules::delete_last_log_move()
{
    this->move_logs.pop_back();
}

Bitboard ChessRules::get_full_board()
{
    return this->full_board;
}

char* ChessRules::get_char_list_board()
{
    char* char_board = new char[64];

    for (int n = 0; n < 64; ++n) {
        Bitboard position = 1ULL << n;

        if (this->white_pawns & position) char_board[n] = this->PAWN_WHITE;
        else if (this->white_knights & position) char_board[n] = this->KNIGHT_WHITE;
        else if (this->white_bishops & position) char_board[n] = this->BISHOP_WHITE;
        else if (this->white_rooks & position) char_board[n] = this->ROOK_WHITE;
        else if (this->white_queens & position) char_board[n] = this->QUEEN_WHITE;
        else if (this->white_king & position) char_board[n] = this->KING_WHITE;

        else if (this->black_pawns & position) char_board[n] = this->PAWN_BLACK;
        else if (this->black_knights & position) char_board[n] = this->KNIGHT_BLACK;
        else if (this->black_bishops & position) char_board[n] = this->BISHOP_BLACK;
        else if (this->black_rooks & position) char_board[n] = this->ROOK_BLACK;
        else if (this->black_queens & position) char_board[n] = this->QUEEN_BLACK;
        else if (this->black_king & position) char_board[n] = this->KING_BLACK;
        
        else char_board[n] = this->EMPTY;
    }
    return char_board;
}

void ChessRules::get_bitboards_from_char_list(const char* char_board) 
{
    white_pawns = 0ULL;
    white_knights = 0ULL;
    white_rooks = 0ULL;
    white_bishops = 0ULL;
    white_queens = 0ULL;
    white_king = 0ULL;

    black_pawns = 0ULL;
    black_knights = 0ULL;
    black_rooks = 0ULL;
    black_bishops = 0ULL;
    black_queens = 0ULL;
    black_king = 0ULL;

    for (int n = 0; n < 64; ++n) {
        Bitboard position = 1ULL << n;

        switch (char_board[n]) {
            case this->PAWN_WHITE:
                white_pawns |= position;
                break;
            case this->KNIGHT_WHITE:
                white_knights |= position;
                break;
            case this->BISHOP_WHITE:
                white_bishops |= position;
                break;
            case this->ROOK_WHITE:
                white_rooks |= position;
                break;
            case this->QUEEN_WHITE:
                white_queens |= position;
                break;
            case this->KING_WHITE:
                white_king |= position;
                break;

            case this->PAWN_BLACK:
                black_pawns |= position;
                break;
            case this->KNIGHT_BLACK:
                black_knights |= position;
                break;
            case this->BISHOP_BLACK:
                black_bishops |= position;
                break;
            case this->ROOK_BLACK:
                black_rooks |= position;
                break;
            case this->QUEEN_BLACK:
                black_queens |= position;
                break;
            case this->KING_BLACK:
                black_king |= position;
                break;

            case EMPTY:
                break;
        }
    }
}

void ChessRules::print_bitboard_as_bytes(Bitboard board)
{
    std::cout << "Bitboard in hex: 0x" 
            << std::hex << std::setw(16) << std::setfill('0') 
            << board << std::endl;
}

void ChessRules::print_graphic_bitboard(Bitboard board)
{
    for (int rank = 7; rank >= 0; --rank) {
        for (int file = 0; file < 8; ++file) {
            if (board & (1ULL << (rank * 8 + file)))
                std::cout << "1  ";
            else
                std::cout << "0  ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void ChessRules::print_graphic_chessboard(const std::string &board_str) 
{
    for (int rank = 7; rank >= 0; --rank) {
        for (int file = 0; file < 8; ++file) {
            int square = rank * 8 + file; 
            std::cout << board_str[square] << "  ";
        }
        std::cout << "\n";
    }
}

int ChessRules::check_square_occupation(Bitboard move)
{
    Bitboard enemy_board, allies_board = 0ULL;
    enemy_board = this->white_to_move ? this->black_board : this->white_board;
    allies_board = this->white_to_move ? this->white_board : this->black_board;

    if (move & enemy_board) {
        return 2;
    } else if (move & allies_board) {
        return 1;
    } else {
        return 0;
    }
}

Bitboard ChessRules::slide_piece(
    Bitboard piece_position, int shift, Bitboard boundary_mask, bool single_move) 
{
    Bitboard piece_moves = 0ULL;
    Bitboard move = piece_position;

    while (!(move & boundary_mask)) {
        move = (shift > 0) ? (move << shift) : (move >> -shift);
        int move_occupation = check_square_occupation(move);

        if (move_occupation == 1) break; 
        piece_moves |= move;                   
        if (move_occupation == 2) break;
        if (single_move) break;
        if (move == 0ULL) break;
    }

    return piece_moves;
}

Bitboard ChessRules::generate_all_rooks_moves(Bitboard rook_board) 
{
    Bitboard rooks_moves = 0ULL;

    rooks_moves |= slide_piece(rook_board, -1, this->FILE_A);
    rooks_moves |= slide_piece(rook_board, 1, this->FILE_H);
    rooks_moves |= slide_piece(rook_board, -8, this->RANK_1);
    rooks_moves |= slide_piece(rook_board, 8, this->RANK_8);

    return rooks_moves;
}

Bitboard ChessRules::generate_all_bishops_moves(Bitboard bishop_board)
{
    Bitboard bishop_moves = 0ULL;

    bishop_moves |= slide_piece(bishop_board, 7, this->FILE_A | this->RANK_8);
    bishop_moves |= slide_piece(bishop_board, 9, this->FILE_H | this->RANK_8);
    bishop_moves |= slide_piece(bishop_board, -7, this->RANK_1 | this->FILE_H);
    bishop_moves |= slide_piece(bishop_board, -9, this->RANK_1 | this->FILE_A);

    return bishop_moves;
}

Bitboard ChessRules::generate_all_knights_moves(Bitboard knights_board)
{
    Bitboard knights_moves = 0ULL;

    knights_moves |= slide_piece(knights_board, 15, this->RANK_8 | this->RANK_7 | this->FILE_A, true);
    knights_moves |= slide_piece(knights_board, 17, this->RANK_8 | this->RANK_7 | this->FILE_H, true);
    knights_moves |= slide_piece(knights_board, 6, this->RANK_8 | this->FILE_A | this->FILE_B, true);
    knights_moves |= slide_piece(knights_board, 10, this->RANK_8 | this->FILE_G | this->FILE_H, true);
    knights_moves |= slide_piece(knights_board, -15, this->RANK_1 | this->RANK_2 | this->FILE_H, true);
    knights_moves |= slide_piece(knights_board, -17, this->RANK_1 | this->RANK_2 | this->FILE_H, true);
    knights_moves |= slide_piece(knights_board, -6, this->FILE_H | this->FILE_G | this->RANK_1, true);
    knights_moves |= slide_piece(knights_board, -10, this->FILE_A | this->FILE_B | this->RANK_1, true);

    return knights_moves;
}

Bitboard ChessRules::generate_all_queens_moves(Bitboard queen_board)
{
    Bitboard queens_moves = generate_all_bishops_moves(
        queen_board) | generate_all_rooks_moves(queen_board);
    return queens_moves;
}

Bitboard ChessRules::generate_queen_side_castling_move(Bitboard king_board)
{
    Bitboard queen_castling = 0ULL;
    Bitboard queen_castling_squares = 0ULL;

    if (this->white_to_move) {
        queen_castling_squares = 0x00'00'00'00'00'00'00'0EULL;
    } else {
        queen_castling_squares = 0x0E'00'00'00'00'00'00'00ULL;
    }

    if (!(queen_castling_squares & this->full_board)) {
        if (this->white_to_move && this->white_queen_side_castling) {
            queen_castling = 0x00'00'00'00'00'00'00'04ULL;
        } else if (this->black_queen_side_castling) {
            queen_castling = 0x04'00'00'00'00'00'00'00ULL;
        }
    }

    return queen_castling;
}

Bitboard ChessRules::generate_king_side_castling_move(Bitboard king_board)
{
    Bitboard king_castling = 0ULL;
    Bitboard king_castling_squares = 0ULL;

    if (this->white_to_move) {
        king_castling_squares = 0x00'00'00'00'00'00'00'60ULL;
    } else {
        king_castling_squares = 0x60'00'00'00'00'00'00'00ULL;
    }

    if (!(king_castling_squares & this->full_board)) {
        if (this->white_to_move && this->white_king_side_castling) {
            king_castling = 0x00'00'00'00'00'00'00'40ULL;
        } else if (this->black_king_side_castling) {
            king_castling = 0x40'00'00'00'00'00'00'00ULL;
        }
    }

    return king_castling;
}

Bitboard ChessRules::generate_all_kings_moves(Bitboard king_board)
{
    Bitboard king_moves = 0ULL;

    king_moves |= slide_piece(king_board, -1, this->FILE_A, true);
    king_moves |= slide_piece(king_board, 1, this->FILE_H, true);
    king_moves |= slide_piece(king_board, -8, this->RANK_1, true);
    king_moves |= slide_piece(king_board, 8, this->RANK_8, true);
    king_moves |= slide_piece(king_board, 7, this->FILE_A | this->RANK_8, true);
    king_moves |= slide_piece(king_board, 9, this->FILE_H | this->RANK_8, true);
    king_moves |= slide_piece(king_board, -7, this->RANK_1 | this->FILE_H, true);
    king_moves |= slide_piece(king_board, -9, this->RANK_1 | this->FILE_A, true);

    king_moves |= generate_queen_side_castling_move(king_board);
    king_moves |= generate_king_side_castling_move(king_board);

    return king_moves;
}

Bitboard ChessRules::slide_pawn(Bitboard pawn_position, int shift, Bitboard boundary_mask) 
{
    Bitboard pawns_moves = 0ULL;
    Bitboard move = pawn_position;

    if (!(move & boundary_mask)) {
        move = (shift > 0) ? (move << shift) : (move >> -shift);

        int move_occupation = check_square_occupation(move);
        if (!((move_occupation == 1) || (move_occupation == 2))) {
            pawns_moves |= move;                   
        } 
    }
    return pawns_moves;
}

Bitboard ChessRules::slide_double_pawn(Bitboard pawn_position, int shift) 
{
    Bitboard pawns_moves = 0ULL;
    Bitboard move_double = pawn_position;
    Bitboard square_passed = pawn_position;

    move_double = (shift > 0) ? (move_double << shift) : (move_double >> -shift);
    square_passed = (shift > 0) ? (square_passed << (8)) : (square_passed >> (8));

    int move_double_occupation = check_square_occupation(move_double);
    int square_passed_occupation = check_square_occupation(square_passed);

    if (!(move_double_occupation || square_passed_occupation)) {
        pawns_moves |= move_double;                   
    }

    return pawns_moves;
}

Bitboard ChessRules::capture_pawn(Bitboard pawn_position, int shift, Bitboard boundary_mask) 
{
    Bitboard pawns_moves = 0ULL;
    Bitboard move = pawn_position;

    if (!(move & boundary_mask)) {
        move = (shift > 0) ? (move << shift) : (move >> -shift);

        int move_occupation = check_square_occupation(move);                
        if (move_occupation == 2) {
            pawns_moves |= move;                   
        }
    }

    return pawns_moves;
}

Bitboard ChessRules::generate_en_passant_move(Bitboard pawn_position) 
{
    Bitboard en_passant_move_board = 0ULL;

    if (this->en_passant_square >= 0) { 
        Bitboard en_passant_target = (1ULL << this->en_passant_square);

        if (this->white_to_move) {
            if (pawn_position & (en_passant_target >> 9)) {
                en_passant_move_board |= en_passant_target;
            } else if (pawn_position & (en_passant_target >> 7)) {
                en_passant_move_board |= en_passant_target;
            }
        } else {
            if (pawn_position & (en_passant_target << 9)) {
                en_passant_move_board |= en_passant_target;
            } else if (pawn_position & (en_passant_target << 7)) {
                en_passant_move_board |= en_passant_target;
            }
        }
    }

    return en_passant_move_board;
}

Bitboard ChessRules::en_passant_move_old(Bitboard pawn_position) 
{
    Bitboard en_passant_move = 0ULL;
    Bitboard pawns_start_squares = 0ULL;

    if (this->white_to_move) {
        pawns_start_squares = RANK_5;
    } else {
        pawns_start_squares = RANK_4;
    }

    if (this->en_passant_square && (pawn_position & pawns_start_squares)) {
        if ((pawn_position << 1) == last_move_end) {
            if (this->white_to_move) {
                en_passant_move = pawn_position << 9;
            } else {
                en_passant_move = pawn_position >> 7;
            }
        } else if ((pawn_position >> 1) == last_move_end) {
            if (this->white_to_move) {
                en_passant_move = pawn_position << 7;
            } else {
                en_passant_move = pawn_position >> 9;
            }
        }
    }
    return en_passant_move;
}

void ChessRules::check_en_passant_moves()
{

}

bool ChessRules::check_is_move_str_valid(std::string &move)
{       
    Bitboard temporary_white_pawns = this->white_pawns;
    Bitboard temporary_white_knights = this->white_knights;
    Bitboard temporary_white_rooks = this->white_rooks;
    Bitboard temporary_white_bishops = this->white_bishops;
    Bitboard temporary_white_queens = this->white_queens;
    Bitboard temporary_white_king = this->white_king;

    Bitboard temporary_black_pawns = this->black_pawns;
    Bitboard temporary_black_knights = this->black_knights;
    Bitboard temporary_black_rooks = this->black_rooks;
    Bitboard temporary_black_bishops = this->black_bishops;
    Bitboard temporary_black_queens = this->black_queens;
    Bitboard temporary_black_king = this->black_king;

    bool valid;
    Bitboard all_moves_end_board;
    Bitboard king_position;

    this->apply_move_startpos(move);
    all_moves_end_board = this->get_all_moves_end();

    this->white_to_move = !this->white_to_move;
    king_position = this->white_to_move ? this->white_king : this->black_king;
    valid = !(king_position & all_moves_end_board);

    this->white_pawns = temporary_white_pawns;
    this->white_knights = temporary_white_knights;
    this->white_rooks = temporary_white_rooks;
    this->white_bishops = temporary_white_bishops;
    this->white_queens = temporary_white_queens;
    this->white_king = temporary_white_king;

    this->black_pawns = temporary_black_pawns;
    this->black_knights = temporary_black_knights;
    this->black_rooks = temporary_black_rooks;
    this->black_bishops = temporary_black_bishops;
    this->black_queens = temporary_black_queens;
    this->black_king = temporary_black_king;

    this->white_board = this->white_pawns | this->white_knights | 
                        this->white_bishops | this->white_rooks | 
                        this->white_queens | this->white_king;
    this->black_board = this->black_pawns | this->black_knights | 
                        this->black_bishops | this->black_rooks | 
                        this->black_queens | this->black_king;
    this->full_board = this->white_board | this->black_board;

    this->move_logs.pop_back();

    return valid;
}

Bitboard ChessRules::generate_all_pawns_moves(Bitboard pawn_board)
{
    Bitboard pawns_moves = 0ULL;

    if (this->white_to_move) {
        pawns_moves |= slide_pawn(pawn_board, 8, this->RANK_8);
        pawns_moves |= capture_pawn(pawn_board, 7, this->RANK_8 | this->FILE_A);
        pawns_moves |= capture_pawn(pawn_board, 9, this->RANK_8 | this->FILE_H);
        if(pawn_board & this->RANK_2) {
            pawns_moves |= slide_double_pawn(pawn_board, 16);
        }
    } else {
        pawns_moves |= slide_pawn(pawn_board, -8, this->RANK_1);
        pawns_moves |= capture_pawn(pawn_board, -7, this->RANK_1 | this->FILE_H);
        pawns_moves |= capture_pawn(pawn_board, -9, this->RANK_1 | this->FILE_A);
        if(pawn_board & this->RANK_7) {
            pawns_moves |= slide_double_pawn(pawn_board, -16);
        }
    }
    pawns_moves |= generate_en_passant_move(pawn_board);

    return pawns_moves;
}

void ChessRules::clear_bit(uint64_t &bitboard, int square)
{
    bitboard &= ~(1ULL << square);
}

void ChessRules::set_bit(uint64_t &bitboard, int square)
{
    bitboard |= (1ULL << square);
}

std::pair<int, int> ChessRules::move_to_square_indices(const std::string &move)
{
    int source = (move[0] - 'a') + ((move[1] - '1') * 8);
    int target = (move[2] - 'a') + ((move[3] - '1') * 8);
    return {source, target};
}

void ChessRules::apply_moves_startpos(std::stringstream &ss)
{
    // e.g: position startpos moves [e2e4 e7e5 g1f3 b8c6 a7b8q]

    this->clear_board();
    std::string moves;
    if (ss >> moves && moves == "moves") {
        std::string move;
        while (ss >> move) {
            this->apply_move_startpos(move);
        }
    }
}

void ChessRules::apply_move_startpos(const std::string &move)
{
    std::pair<int, int> indicases = this->move_to_square_indices(move);
    int source = indicases.first;
    int target = indicases.second;

    char promotion_piece = '\0';
    if (move.length() == 5) {
        promotion_piece = move[4];
    }

    if (((0x10'00'00'00'00'00'00'00ULL) & (1ULL << target)) || 
        ((0x10'00'00'00'00'00'00'00ULL) & (1ULL << source))) {
        black_king_side_castling = false;
        black_queen_side_castling = false;
    }
    if (((0x80'00'00'00'00'00'00'00ULL) & (1ULL << target)) || 
        ((0x80'00'00'00'00'00'00'00ULL) & (1ULL << source))) {
        black_king_side_castling = false;
    }
    if (((0x01'00'00'00'00'00'00'00ULL) & (1ULL << target)) || 
        ((0x01'00'00'00'00'00'00'00ULL) & (1ULL << source))) {
        black_queen_side_castling = false;
    }


    if (((0x00'00'00'00'00'00'00'10ULL) & (1ULL << target)) || 
        ((0x00'00'00'00'00'00'00'10ULL) & (1ULL << source))) {
        white_king_side_castling = false;
        white_queen_side_castling = false;
    }
    if (((0x80'00'00'00'00'00'00'00ULL) & (1ULL << target)) || 
        ((0x80'00'00'00'00'00'00'00ULL) & (1ULL << source))) {
        white_king_side_castling = false;
    }
    if (((0x01'00'00'00'00'00'00'00ULL) & (1ULL << target)) || 
        ((0x01'00'00'00'00'00'00'00ULL) & (1ULL << source))) {
        white_queen_side_castling = false;
    }

    // clear target square
    uint64_t end_piece_mask = (1ULL << target);
    if (this->white_board & end_piece_mask) {
        if (this->white_pawns & end_piece_mask) {
            clear_bit(this->white_pawns, target);
        } else if (this->white_knights & end_piece_mask) {
            clear_bit(this->white_knights, target);
        } else if (this->white_bishops & end_piece_mask) {
            clear_bit(this->white_bishops, target);
        } else if (this->white_rooks & end_piece_mask) {
            clear_bit(this->white_rooks, target);
        } else if (this->white_queens & end_piece_mask) {
            clear_bit(this->white_queens, target);
        } else if (this->white_king & end_piece_mask) {
            clear_bit(this->white_king, target);
        }
    } else if (this->black_board & end_piece_mask) {
        if (this->black_pawns & end_piece_mask) {
            clear_bit(this->black_pawns, target);
        } else if (this->black_knights & end_piece_mask) {
            clear_bit(this->black_knights, target);
        } else if (this->black_bishops & end_piece_mask) {
            clear_bit(this->black_bishops, target);
        } else if (this->black_rooks & end_piece_mask) {
            clear_bit(this->black_rooks, target);
        } else if (this->black_queens & end_piece_mask) {
            clear_bit(this->black_queens, target);
        } else if (this->black_king & end_piece_mask) {
            clear_bit(this->black_king, target);
        }
    }

    // set target square
    if (promotion_piece) {
        if (this->white_to_move) {
            switch (promotion_piece) {
                case 'q':
                    this->white_queens |= (1ULL << target);
                    break;
                case 'r':
                    this->white_rooks |= (1ULL << target);
                    break;
                case 'b':
                    this->white_bishops |= (1ULL << target);
                    break;
                case 'n':
                    this->white_knights |= (1ULL << target);
                    break;
            }
        } else {
            switch (promotion_piece) {
                case 'q':
                    this->black_queens |= (1ULL << target);
                    break;
                case 'r':
                    this->black_rooks |= (1ULL << target);
                    break;
                case 'b':
                    this->black_bishops |= (1ULL << target);
                    break;
                case 'n':
                    this->black_knights |= (1ULL << target);
                    break;
            }
        }
    } else {
        uint64_t start_piece_mask = (1ULL << source);
        if (this->white_board & start_piece_mask) {
            if (this->white_pawns & start_piece_mask) {
                set_bit(this->white_pawns, target);
            } else if (this->white_knights & start_piece_mask) {
                set_bit(this->white_knights, target);
            } else if (this->white_bishops & start_piece_mask) {
                set_bit(this->white_bishops, target);
            } else if (this->white_rooks & start_piece_mask) {
                set_bit(this->white_rooks, target);
            } else if (this->white_queens & start_piece_mask) {
                set_bit(this->white_queens, target);
            } else if (this->white_king & start_piece_mask) {
                set_bit(this->white_king, target);
            } 
        } else if (this->black_board & start_piece_mask) {
            if (this->black_pawns & start_piece_mask) {
                set_bit(this->black_pawns, target);
            } else if (this->black_knights & start_piece_mask) {
                set_bit(this->black_knights, target);
            } else if (this->black_bishops & start_piece_mask) {
                set_bit(this->black_bishops, target);
            } else if (this->black_rooks & start_piece_mask) {
                set_bit(this->black_rooks, target);
            } else if (this->black_queens & start_piece_mask) {
                set_bit(this->black_queens, target);
            } else if (this->black_king & start_piece_mask) {
                set_bit(this->black_king, target);
            }
        }
    }
    
    // clear source square
    uint64_t start_piece_mask = (1ULL << source);
    if (this->white_board & start_piece_mask) {
        if (this->white_pawns & start_piece_mask) {
            clear_bit(this->white_pawns, source);
        } else if (this->white_knights & start_piece_mask) {
            clear_bit(this->white_knights, source);
        } else if (this->white_bishops & start_piece_mask) {
            clear_bit(this->white_bishops, source);
        } else if (this->white_rooks & start_piece_mask) {
            clear_bit(this->white_rooks, source);
        } else if (this->white_queens & start_piece_mask) {
            clear_bit(this->white_queens, source);
        } else if (this->white_king & start_piece_mask) {
            clear_bit(this->white_king, source);
        } 
    } else if (this->black_board & start_piece_mask) {
        if (this->black_pawns & start_piece_mask) {
            clear_bit(this->black_pawns, source);
        } else if (this->black_knights & start_piece_mask) {
            clear_bit(this->black_knights, source);
        } else if (this->black_bishops & start_piece_mask) {
            clear_bit(this->black_bishops, source);
        } else if (this->black_rooks & start_piece_mask) {
            clear_bit(this->black_rooks, source);
        } else if (this->black_queens & start_piece_mask) {
            clear_bit(this->black_queens, source);
        } else if (this->black_king & start_piece_mask) {
            clear_bit(this->black_king, source);
        }
    }

    this->white_board = this->white_pawns | this->white_knights | 
                        this->white_bishops | this->white_rooks | 
                        this->white_queens | this->white_king;
    this->black_board = this->black_pawns | this->black_knights | 
                        this->black_bishops | this->black_rooks | 
                        this->black_queens | this->black_king;
    this->full_board = this->white_board | this->black_board;
    this->white_to_move = !(this->white_to_move);

    std::string fen = this->generate_current_fen();
    this->add_move_log(fen);
}

void ChessRules::append_piece_or_empty(std::string &position, int &empty_count, char piece) 
{
    if (empty_count > 0) {
        position += std::to_string(empty_count);
        empty_count = 0;
    }
    position += piece;
}

std::string ChessRules::generate_current_fen()
{
    std::ostringstream fen;
    std::string position;
    
    for (int rank = 7; rank >= 0; --rank) {
        int empty_count = 0;
        for (int file = 0; file < 8; ++file) {
            Bitboard piece_mask = (1ULL << (rank * 8 + file));

            if (this->white_pawns & piece_mask) {
                this->append_piece_or_empty(position, empty_count, 'P');
            } else if (this->white_knights & piece_mask) {
                this->append_piece_or_empty(position, empty_count, 'N');
            } else if (this->white_bishops & piece_mask) {
                this->append_piece_or_empty(position, empty_count, 'B');
            } else if (this->white_rooks & piece_mask) {
                this->append_piece_or_empty(position, empty_count, 'R');
            } else if (this->white_queens & piece_mask) {
                this->append_piece_or_empty(position, empty_count, 'Q');
            } else if (this->white_king & piece_mask) {
                this->append_piece_or_empty(position, empty_count, 'K');
            } else if (this->black_pawns & piece_mask) {
                this->append_piece_or_empty(position, empty_count, 'p');
            } else if (this->black_knights & piece_mask) {
                this->append_piece_or_empty(position, empty_count, 'n');
            } else if (this->black_bishops & piece_mask) {
                this->append_piece_or_empty(position, empty_count, 'b');
            } else if (this->black_rooks & piece_mask) {
                this->append_piece_or_empty(position, empty_count, 'r');
            } else if (this->black_queens & piece_mask) {
                this->append_piece_or_empty(position, empty_count, 'q');
            } else if (this->black_king & piece_mask) {
                this->append_piece_or_empty(position, empty_count, 'k');
            } else {
                empty_count++;
            }
        }

        if (empty_count > 0) {
            position += std::to_string(empty_count);
        }

        if (rank > 0)
            position += '/';
    }

    fen << position << " " << (this->white_to_move ? "w" : "b") << " ";

    std::string castling;
    if (this->white_king_side_castling)
        castling += "K";
    if (this->white_queen_side_castling)
        castling += "Q";
    if (this->black_king_side_castling)
        castling += "k";
    if (this->black_queen_side_castling)
        castling += "q";
    
    fen << (!castling.empty() ? castling : "-") << " ";

    if (this->en_passant_square == -1)
        fen << "-";
    else
        fen << static_cast<char>('a' + this->en_passant_square % 8)
            << static_cast<char>('1' + 7 - this->en_passant_square / 8);

    fen << " " << this->halfmove_clock << " " << this->fullmove_number;

    return fen.str();
}

void ChessRules::apply_move_fen(const std::string &fen)
{
    // e.g: position fen [rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1]
    this->clear_board();

    std::istringstream ss(fen);
    std::string position, active_color, castling, en_passant, halfmove_str, fullmove_str;
    ss >> position >> active_color >> castling >> en_passant >> halfmove_str >> fullmove_str;

    int rank = 0, file = 0;

    for (char c : position) {
        if (c == '/') {
            rank++;
            file = 0;
        } else if (isdigit(c)) {
            file += c - '0';
        } else {
            Bitboard piece_mask = (1ULL << (63 - (rank * 8 + (7 - file))));
            switch (c) {
                case 'P': this->white_pawns |= piece_mask; break;
                case 'N': this->white_knights |= piece_mask; break;
                case 'B': this->white_bishops |= piece_mask; break;
                case 'R': this->white_rooks |= piece_mask; break;
                case 'Q': this->white_queens |= piece_mask; break;
                case 'K': this->white_king |= piece_mask; break;
                case 'p': this->black_pawns |= piece_mask; break;
                case 'n': this->black_knights |= piece_mask; break;
                case 'b': this->black_bishops |= piece_mask; break;
                case 'r': this->black_rooks |= piece_mask; break;
                case 'q': this->black_queens |= piece_mask; break;
                case 'k': this->black_king |= piece_mask; break;
            }
            file++;
        }
    }

    this->white_to_move = (active_color == "w");

    if (castling.find('K') != std::string::npos) {
        this->white_king_side_castling = true; 
    } else {
        this->white_king_side_castling = false;
        }
    if (castling.find('Q') != std::string::npos) {
        this->white_queen_side_castling = true; 
    } else {
        this->white_queen_side_castling = false;
        }
    if (castling.find('k') != std::string::npos) {
        this->black_king_side_castling = true; 
    } else {
        this->black_king_side_castling = false;
        }
    if (castling.find('q') != std::string::npos) {
        this->black_queen_side_castling = true; 
    } else {
        this->black_queen_side_castling = false;    
        }

    if (en_passant == "-") {
        this->en_passant_square = -1;
    } else {
        int en_passant_file = en_passant[0] - 'a';
        int en_passant_rank = en_passant[1] - '1';
        this->en_passant_square = (8 * (7 - en_passant_rank)) + en_passant_file;
    }

    this->halfmove_clock = std::stoi(halfmove_str);
    this->fullmove_number = std::stoi(fullmove_str);

    this->white_board = white_pawns | white_knights | white_rooks |
                        white_bishops | white_queens | white_king;
    this->black_board = black_pawns | black_knights | black_rooks |
                        black_bishops | black_queens | black_king;
    this->full_board = white_board | black_board;

    this->add_move_log(fen);
}

void ChessRules::update_all_moves_str(std::vector<std::string> &all_moves_str, 
Bitboard start_square, Bitboard moves_end_squares)
{
    for (int index = 0; index < 64; index++) {
        if (moves_end_squares & (1ULL << index)) {
            all_moves_str.push_back(this->bitboards_to_move(start_square, 1ULL << index));
        }
    }
}

std::vector<std::string> ChessRules::get_all_moves_str(std::vector<std::string> &all_moves_str)
{
    int index = 0;
    Bitboard moves = 0ULL;
    all_moves_str.clear();

    while (index < 64) {
        moves = 0ULL;

        if (this->white_to_move) {
            if (this->white_board & (1ULL << index)) {
                if (this->white_pawns & (1ULL << index)) {
                    moves = this->generate_all_pawns_moves(1ULL << index);
                } else if (this->white_rooks & (1ULL << index)) {
                    moves = this->generate_all_rooks_moves(1ULL << index);
                } else if (this->white_knights & (1ULL << index)) {
                    moves = this->generate_all_knights_moves(1ULL << index);
                } else if (this->white_bishops & (1ULL << index)) {
                    moves = this->generate_all_bishops_moves(1ULL << index);
                } else if (this->white_queens & (1ULL << index)) {
                    moves = this->generate_all_queens_moves(1ULL << index);
                } else if (this->white_king & (1ULL << index)) {
                    moves = this->generate_all_kings_moves(1ULL << index);
                }
            }
        } else {
            if (this->black_board & (1ULL << index)) {
                if (this->black_pawns & (1ULL << index)) {
                    moves = this->generate_all_pawns_moves(1ULL << index);
                } else if (this->black_rooks & (1ULL << index)) {
                    moves = this->generate_all_rooks_moves(1ULL << index);
                } else if (this->black_knights & (1ULL << index)) {
                    moves = this->generate_all_knights_moves(1ULL << index);
                } else if (this->black_bishops & (1ULL << index)) {
                    moves = this->generate_all_bishops_moves(1ULL << index);
                } else if (this->black_queens & (1ULL << index)) {
                    moves = this->generate_all_queens_moves(1ULL << index);
                } else if (this->black_king & (1ULL << index)) {
                    moves = this->generate_all_kings_moves(1ULL << index);
                }
            }
        }

        this->update_all_moves_str(all_moves_str, 1ULL << index, moves);
        index++;
    }
    return all_moves_str;
}

Bitboard ChessRules::get_all_moves_end()
{
    Bitboard all_moves_end_board;
    int index = 0;
    Bitboard moves = 0ULL;

    while (index < 64) {
        moves = 0ULL;

        if (this->white_to_move) {
            if (this->white_board & (1ULL << index)) {
                if (this->white_pawns & (1ULL << index)) {
                    moves = this->generate_all_pawns_moves(1ULL << index);
                } else if (this->white_rooks & (1ULL << index)) {
                    moves = this->generate_all_rooks_moves(1ULL << index);
                } else if (this->white_knights & (1ULL << index)) {
                    moves = this->generate_all_knights_moves(1ULL << index);
                } else if (this->white_bishops & (1ULL << index)) {
                    moves = this->generate_all_bishops_moves(1ULL << index);
                } else if (this->white_queens & (1ULL << index)) {
                    moves = this->generate_all_queens_moves(1ULL << index);
                } else if (this->white_king & (1ULL << index)) {
                    moves = this->generate_all_kings_moves(1ULL << index);
                }
            }
        } else {
            if (this->black_board & (1ULL << index)) {
                if (this->black_pawns & (1ULL << index)) {
                    moves = this->generate_all_pawns_moves(1ULL << index);
                } else if (this->black_rooks & (1ULL << index)) {
                    moves = this->generate_all_rooks_moves(1ULL << index);
                } else if (this->black_knights & (1ULL << index)) {
                    moves = this->generate_all_knights_moves(1ULL << index);
                } else if (this->black_bishops & (1ULL << index)) {
                    moves = this->generate_all_bishops_moves(1ULL << index);
                } else if (this->black_queens & (1ULL << index)) {
                    moves = this->generate_all_queens_moves(1ULL << index);
                } else if (this->black_king & (1ULL << index)) {
                    moves = this->generate_all_kings_moves(1ULL << index);
                }
            }
        }

        all_moves_end_board |= moves;
        index++;
    }
    return all_moves_end_board;
}

void ChessRules::validate_moves_str(std::vector<std::string> &all_moves_str)
{
    for (int i = all_moves_str.size() - 1; i >= 0; --i) {
        if (!this->check_is_move_str_valid(all_moves_str[i])) {
            all_moves_str.erase(all_moves_str.begin() + i);
        }
    }
}

std::vector<std::string> ChessRules::get_all_valid_moves_str()
{
    std::vector<std::string> all_moves_str;
    
    this->get_all_moves_str(all_moves_str);
    this->validate_moves_str(all_moves_str);

    return all_moves_str;
}

void ChessRules::undo_move()
{
    if (this->move_logs.size() > 1) {
        this->delete_last_log_move();
        this->apply_move_fen(this->move_logs.back());
        this->delete_last_log_move();
    } else {
        this->set_start_positions();
        this->set_board_starting_variables();
        this->clear_move_logs();
    }
}

int ChessRules::bitboard_to_index(Bitboard bitboard) 
{
    int index = 0;

    while (bitboard != 0) {
        if (bitboard & 1) {
            return index;
        }
        bitboard >>= 1;
        index++;
    }
    return -1;
}

std::string ChessRules::index_to_square(int index) 
{
    int file = index % 8;
    int rank = index / 8;
    char file_char = 'a' + file;
    char rank_char = '1' + rank;
    return std::string() + file_char + rank_char;
}

std::string ChessRules::bitboards_to_move(Bitboard move_begin, Bitboard move_end) 
{
    int begin_index = bitboard_to_index(move_begin);
    int end_index = bitboard_to_index(move_end);

    std::string begin_square = index_to_square(begin_index);
    std::string end_square = index_to_square(end_index);

    return begin_square + end_square;
}
