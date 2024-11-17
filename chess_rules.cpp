#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

typedef uint64_t Bitboard;

std::string bitboard_representation = R"(
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

)";

const Bitboard FILE_A = 0x01'01'01'01'01'01'01'01ULL;
const Bitboard FILE_B = 0x02'02'02'02'02'02'02'02ULL;
const Bitboard FILE_C = 0x04'04'04'04'04'04'04'04ULL;
const Bitboard FILE_D = 0x08'08'08'08'08'08'08'08ULL;
const Bitboard FILE_E = 0x10'10'10'10'10'10'10'10ULL;
const Bitboard FILE_F = 0x20'20'20'20'20'20'20'20ULL;
const Bitboard FILE_G = 0x40'40'40'40'40'40'40'40ULL;
const Bitboard FILE_H = 0x80'80'80'80'80'80'80'80ULL;

const Bitboard RANK_1 = 0x00'00'00'00'00'00'00'FFULL;
const Bitboard RANK_2 = 0x00'00'00'00'00'00'FF'00ULL;
const Bitboard RANK_3 = 0x00'00'00'00'00'FF'00'00ULL;
const Bitboard RANK_4 = 0x00'00'00'00'FF'00'00'00ULL;
const Bitboard RANK_5 = 0x00'00'00'FF'00'00'00'00ULL;
const Bitboard RANK_6 = 0x00'00'FF'00'00'00'00'00ULL;
const Bitboard RANK_7 = 0x00'FF'00'00'00'00'00'00ULL;
const Bitboard RANK_8 = 0xFF'00'00'00'00'00'00'00ULL;

const Bitboard BOUNDARIES = FILE_A | FILE_H | RANK_1 | RANK_8; // 0xFF'81'81'81'81'81'81'FFULL;


Bitboard white_pawns = 0x00'00'00'00'00'00'FF'00ULL;
Bitboard white_knights = 0x00'00'00'00'00'00'00'42ULL;
Bitboard white_rooks = 0x00'00'00'00'00'00'00'81ULL;
Bitboard white_bishops = 0x00'00'00'00'00'00'00'24ULL;
Bitboard white_queens = 0x00'00'00'00'00'00'00'08ULL;
Bitboard white_king = 0x00'00'00'00'00'00'00'10ULL;

Bitboard black_pawns = 0x00'FF'00'00'00'00'00'00ULL;
Bitboard black_knights = 0x42'00'00'00'00'00'00'00ULL;
Bitboard black_rooks = 0x81'00'00'00'00'00'00'00ULL;
Bitboard black_bishops = 0x24'00'00'00'00'00'00'00ULL;
Bitboard black_queens = 0x08'00'00'00'00'00'00'00ULL;
Bitboard black_king = 0x10'00'00'00'00'00'00'00ULL;

Bitboard white_board = white_pawns | white_knights | white_rooks |
                       white_bishops | white_queens | white_king;
Bitboard black_board = black_pawns | black_knights | black_rooks |
                       black_bishops | black_queens | black_king;
Bitboard full_board = white_board | black_board;


const char EMPTY = '0';
const char PAWN_WHITE = 'P', KNIGHT_WHITE = 'N', BISHOP_WHITE = 'B', 
           ROOK_WHITE = 'R', QUEEN_WHITE = 'Q', KING_WHITE = 'K';
const char PAWN_BLACK = 'p', KNIGHT_BLACK = 'n', BISHOP_BLACK = 'b', 
           ROOK_BLACK = 'r', QUEEN_BLACK = 'q', KING_BLACK = 'k';

bool white_king_side_castling = true;
bool white_queen_side_castling = true;

bool black_king_side_castling = true;
bool black_queen_side_castling = true;


bool white_to_move = true;
bool en_passant = false;
Bitboard last_move_begin = 0ULL;
Bitboard last_move_end = 0ULL;


Bitboard white_board_test = 0ULL;
Bitboard black_board_test = 0ULL;

Bitboard enemy_board_test = 0x00'00'00'00'00'08'00'00ULL;
Bitboard allies_board_test = 0x00'00'00'00'00'00'40'00ULL;


char* get_char_list_board(
    Bitboard white_pawns, Bitboard white_knights, Bitboard white_rooks, 
    Bitboard white_bishops, Bitboard white_queens, Bitboard white_king,
    Bitboard black_pawns, Bitboard black_knights, Bitboard black_rooks, 
    Bitboard black_bishops, Bitboard black_queens, Bitboard black_king
    )
{
    char* char_board = new char[64];

    for (int n = 0; n < 64; ++n) {
        Bitboard position = 1ULL << n;

        if (white_pawns & position) char_board[n] = PAWN_WHITE;
        else if (white_knights & position) char_board[n] = KNIGHT_WHITE;
        else if (white_bishops & position) char_board[n] = BISHOP_WHITE;
        else if (white_rooks & position) char_board[n] = ROOK_WHITE;
        else if (white_queens & position) char_board[n] = QUEEN_WHITE;
        else if (white_king & position) char_board[n] = KING_WHITE;

        else if (black_pawns & position) char_board[n] = PAWN_BLACK;
        else if (black_knights & position) char_board[n] = KNIGHT_BLACK;
        else if (black_bishops & position) char_board[n] = BISHOP_BLACK;
        else if (black_rooks & position) char_board[n] = ROOK_BLACK;
        else if (black_queens & position) char_board[n] = QUEEN_BLACK;
        else if (black_king & position) char_board[n] = KING_BLACK;
        
        else char_board[n] = EMPTY;
    }
    return char_board;
}


void get_bitboards_from_char_list(
    const char* char_board,
    Bitboard &white_pawns, Bitboard &white_knights, Bitboard &white_rooks, 
    Bitboard &white_bishops, Bitboard &white_queens, Bitboard &white_king,
    Bitboard &black_pawns, Bitboard &black_knights, Bitboard &black_rooks, 
    Bitboard &black_bishops, Bitboard &black_queens, Bitboard &black_king
    ) 
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
            case PAWN_WHITE:
                white_pawns |= position;
                break;
            case KNIGHT_WHITE:
                white_knights |= position;
                break;
            case BISHOP_WHITE:
                white_bishops |= position;
                break;
            case ROOK_WHITE:
                white_rooks |= position;
                break;
            case QUEEN_WHITE:
                white_queens |= position;
                break;
            case KING_WHITE:
                white_king |= position;
                break;

            case PAWN_BLACK:
                black_pawns |= position;
                break;
            case KNIGHT_BLACK:
                black_knights |= position;
                break;
            case BISHOP_BLACK:
                black_bishops |= position;
                break;
            case ROOK_BLACK:
                black_rooks |= position;
                break;
            case QUEEN_BLACK:
                black_queens |= position;
                break;
            case KING_BLACK:
                black_king |= position;
                break;

            case EMPTY:
                break;
        }
    }
}


void print_bitboard_as_bytes(Bitboard board)
{
    std::cout << "Bitboard in hex: 0x" 
              << std::hex << std::setw(16) << std::setfill('0') 
              << board << std::endl;
}


void print_graphic_bitboard(Bitboard board)
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


int check_move_occupied(Bitboard move)
{
    Bitboard enemy_board = 0ULL;
    enemy_board = white_to_move ? black_board : white_board;

    if (move & enemy_board_test) {
        return 2;
    } else if (move & allies_board_test) {
        return 1;
    } else {
        return 0;
    }
}


Bitboard slide_piece(
    Bitboard piece_position, int shift, Bitboard boundary_mask, 
    bool single_move=false
    ) 
{
    Bitboard piece_moves = 0ULL;
    Bitboard move = piece_position;

    while (!(move & boundary_mask)) {
        move = (shift > 0) ? (move << shift) : (move >> -shift);
        int move_occupation = check_move_occupied(move);

        if (move_occupation == 1) break; 
        piece_moves |= move;                   
        if (move_occupation == 2) break;
        if (single_move) break;
    }

    return piece_moves;
}


Bitboard generate_all_rooks_moves(Bitboard rook_board) 
{
    Bitboard rooks_moves = 0ULL;

    rooks_moves |= slide_piece(rook_board, -1, FILE_A);
    rooks_moves |= slide_piece(rook_board, 1, FILE_H);
    rooks_moves |= slide_piece(rook_board, -8, RANK_1);
    rooks_moves |= slide_piece(rook_board, 8, RANK_8);

    return rooks_moves;
}


Bitboard generate_all_bishops_moves(Bitboard bishop_board)
{
    Bitboard bishop_moves = 0ULL;

    bishop_moves |= slide_piece(bishop_board, 7, FILE_A | RANK_8);
    bishop_moves |= slide_piece(bishop_board, 9, FILE_H | RANK_8);
    bishop_moves |= slide_piece(bishop_board, -9, RANK_1 | FILE_H);
    bishop_moves |= slide_piece(bishop_board, -7, RANK_1 | FILE_A);

    return bishop_moves;
}


Bitboard generate_all_knights_moves(Bitboard knights_board)
{
    Bitboard knights_moves = 0ULL;

    knights_moves |= slide_piece(knights_board, 15, RANK_8 | RANK_7 | FILE_A, true);
    knights_moves |= slide_piece(knights_board, 17, RANK_8 | RANK_7 | FILE_H, true);
    knights_moves |= slide_piece(knights_board, 6, RANK_8 | FILE_A | FILE_B, true);
    knights_moves |= slide_piece(knights_board, 10, RANK_8 | FILE_G | FILE_H, true);
    knights_moves |= slide_piece(knights_board, -15, RANK_1 | RANK_2 | FILE_H, true);
    knights_moves |= slide_piece(knights_board, -17, RANK_1 | RANK_2 | FILE_H, true);
    knights_moves |= slide_piece(knights_board, -6, FILE_H | FILE_G | RANK_1, true);
    knights_moves |= slide_piece(knights_board, -10, FILE_A | FILE_B | RANK_1, true);

    return knights_moves;
}


Bitboard generate_all_queens_moves(Bitboard queen_board)
{
    Bitboard queens_moves = generate_all_bishops_moves(
        queen_board) | generate_all_rooks_moves(queen_board);
    return queens_moves;
}


Bitboard make_queen_side_castling(Bitboard king_board, bool white_to_move=true)
{
    Bitboard queen_castling = 0ULL;
    Bitboard queen_castling_squares = 0ULL;

    if (white_to_move) {
        queen_castling_squares = 0x00'00'00'00'00'00'00'0EULL;
    } else {
        queen_castling_squares = 0x0E'00'00'00'00'00'00'00ULL;
    }

    if (!(queen_castling_squares & full_board)) {
        if (white_to_move && white_queen_side_castling) {
            queen_castling = 0x00'00'00'00'00'00'00'04ULL;
        } else if (black_queen_side_castling) {
            queen_castling = 0x04'00'00'00'00'00'00'00ULL;
        }
    }

    return queen_castling;
}


Bitboard make_king_side_castling(Bitboard king_board, bool white_to_move)
{
    Bitboard king_castling = 0ULL;
    Bitboard king_castling_squares = 0ULL;

    if (white_to_move) {
        king_castling_squares = 0x00'00'00'00'00'00'00'60ULL;
    } else {
        king_castling_squares = 0x60'00'00'00'00'00'00'00ULL;
    }

    if (!(king_castling_squares & full_board)) {
        if (white_to_move && white_king_side_castling) {
            king_castling = 0x00'00'00'00'00'00'00'40ULL;
        } else if (black_king_side_castling) {
            king_castling = 0x40'00'00'00'00'00'00'00ULL;
        }
    }

    return king_castling;
}


Bitboard generate_all_kings_moves(Bitboard king_board, bool white_to_move=true)
{
    Bitboard king_moves = 0ULL;

    king_moves |= slide_piece(king_board, -1, FILE_A, true);
    king_moves |= slide_piece(king_board, 1, FILE_H, true);
    king_moves |= slide_piece(king_board, -8, RANK_1, true);
    king_moves |= slide_piece(king_board, 8, RANK_8, true);

    king_moves |= make_queen_side_castling(king_board, white_to_move);
    king_moves |= make_king_side_castling(king_board, white_to_move);

    return king_moves;
}


Bitboard slide_pawn(Bitboard pawn_position, int shift, Bitboard boundary_mask) 
{
    Bitboard pawns_moves = 0ULL;
    Bitboard move = pawn_position;

    if (!(move & boundary_mask)) {
        move = (shift > 0) ? (move << shift) : (move >> -shift);

        int move_occupation = check_move_occupied(move);
        if (!((move_occupation == 1) || (move_occupation == 2))) {
            pawns_moves |= move;                   
        } 
    }
    return pawns_moves;
}


Bitboard slide_double_pawn(Bitboard pawn_position, int shift) 
{
    Bitboard pawns_moves = 0ULL;
    Bitboard move_double = pawn_position;
    Bitboard square_passed = pawn_position;

    move_double = (shift > 0) ? (move_double << shift) : (move_double >> -shift);
    square_passed = (shift > 0) ? (move_double << (shift - 8)) : (move_double >> (-shift + 8));

    int move_double_occupation = check_move_occupied(move_double);
    int square_passed_occupation = check_move_occupied(square_passed);

    if (!(move_double_occupation | square_passed_occupation)) {
        pawns_moves |= move_double;                   
    }

    return pawns_moves;
}


Bitboard capture_pawn(Bitboard pawn_position, int shift, Bitboard boundary_mask) 
{
    Bitboard pawns_moves = 0ULL;
    Bitboard move = pawn_position;

    if (!(move & boundary_mask)) {
        move = (shift > 0) ? (move << shift) : (move >> -shift);

        int move_occupation = check_move_occupied(move);                
        if (move_occupation == 2) {
            pawns_moves |= move;                   
        }
    }

    return pawns_moves;
}


Bitboard en_passant_move(Bitboard pawn_position) 
{
    Bitboard en_passant_move = 0ULL;
    Bitboard pawns_start_squares = 0ULL;

    if (white_to_move) {
        pawns_start_squares = RANK_5;
    } else {
        pawns_start_squares = RANK_4;
    }

    if (en_passant && (pawn_position & pawns_start_squares)) {
        if ((pawn_position << 1) == last_move_end) {
            if (white_to_move) {
                en_passant_move = pawn_position << 9;
            } else {
                en_passant_move = pawn_position >> 7;
            }
        } else if ((pawn_position >> 1) == last_move_end) {
            if (white_to_move) {
                en_passant_move = pawn_position << 7;
            } else {
                en_passant_move = pawn_position >> 9;
            }
        }
    }
    return en_passant_move;
}


Bitboard generate_all_pawns_moves(Bitboard pawn_board, bool white_to_move=true)
{
    Bitboard pawns_moves = 0ULL;

    if (white_to_move) {
        pawns_moves |= slide_pawn(pawn_board, 8, RANK_8);
        pawns_moves |= capture_pawn(pawn_board, 7, RANK_8 | FILE_A);
        pawns_moves |= capture_pawn(pawn_board, 9, RANK_8 | FILE_H);
        if(pawn_board & RANK_2) {
            pawns_moves |= slide_double_pawn(pawn_board, 16);
        }
    } else {
        pawns_moves |= slide_pawn(pawn_board, -8, RANK_1);
        pawns_moves |= capture_pawn(pawn_board, -7, RANK_1 | FILE_H);
        pawns_moves |= capture_pawn(pawn_board, -9, RANK_1 | FILE_A);
        if(pawn_board & RANK_7) {
            pawns_moves |= slide_double_pawn(pawn_board, -16);
        }
    }
    pawns_moves |= en_passant_move(pawn_board);

    return pawns_moves;
}


void clear_bit(uint64_t &bitboard, int square)
{
    bitboard &= ~(1ULL << square);
}

void set_bit(uint64_t &bitboard, int square)
{
    bitboard |= (1ULL << square);
}


std::pair<int, int> move_to_square_indices(const std::string &move)
{
    int source = (move[0] - 'a') + (8 - (move[1] - '1' + 1)) * 8;
    int target = (move[2] - 'a') + (8 - (move[3] - '1' + 1)) * 8;
    return {source, target};
}

void apply_move_fen(const std::string &fen)
{
    // e.g: position fen rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1

    bool white_to_move;
    int castling_rights; // Bitwise flags for castling rights: 1 = K, 2 = Q, 4 = k, 8 = q
    int halfmove_clock;
    int fullmove_number;
    int en_passant_square = -1; // -1 indicates no en passant square

    Bitboard white_knights = white_bishops = white_rooks = white_queens = white_king = 0;
    Bitboard black_knights = black_bishops = black_rooks = black_queens = black_king = 0;

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
            Bitboard piece_mask = (1ULL << (56 - (rank * 8 + file)));
            switch (c) {
                case 'P': white_pawns |= piece_mask; break;
                case 'N': white_knights |= piece_mask; break;
                case 'B': white_bishops |= piece_mask; break;
                case 'R': white_rooks |= piece_mask; break;
                case 'Q': white_queens |= piece_mask; break;
                case 'K': white_king |= piece_mask; break;
                case 'p': black_pawns |= piece_mask; break;
                case 'n': black_knights |= piece_mask; break;
                case 'b': black_bishops |= piece_mask; break;
                case 'r': black_rooks |= piece_mask; break;
                case 'q': black_queens |= piece_mask; break;
                case 'k': black_king |= piece_mask; break;
            }
            file++;
        }
    }

    white_to_move = (active_color == "w");

    castling_rights = 0;
    if (castling.find('K') != std::string::npos) castling_rights |= 1;  // White kingside
    if (castling.find('Q') != std::string::npos) castling_rights |= 2;  // White queenside
    if (castling.find('k') != std::string::npos) castling_rights |= 4;  // Black kingside
    if (castling.find('q') != std::string::npos) castling_rights |= 8;  // Black queenside

    if (en_passant == "-") {
        en_passant_square = -1;
    } else {
        int en_passant_file = en_passant[0] - 'a';
        int en_passant_rank = en_passant[1] - '1';
        en_passant_square = (8 * (7 - en_passant_rank)) + en_passant_file;
    }

    halfmove_clock = std::stoi(halfmove_str);
    fullmove_number = std::stoi(fullmove_str);
}

void apply_move_startpos(const std::string &move)
{
    // e.g: position startpos moves e2e4 e7e5 g1f3 b8c6

    std::pair<int, int> indicases = move_to_square_indices(move);
    int source = indicases.first;
    int target = indicases.second;
    uint64_t piece_mask = (1ULL << source);

    if (white_pawns & piece_mask) {
        clear_bit(white_pawns, source);
        set_bit(white_pawns, target);
    } else if (white_knights & piece_mask) {
        clear_bit(white_knights, source);
        set_bit(white_knights, target);
    } else if (white_bishops & piece_mask) {
        clear_bit(white_bishops, source);
        set_bit(white_bishops, target);
    } else if (white_rooks & piece_mask) {
        clear_bit(white_rooks, source);
        set_bit(white_rooks, target);
    } else if (white_queens & piece_mask) {
        clear_bit(white_queens, source);
        set_bit(white_queens, target);
    } else if (white_king & piece_mask) {
        clear_bit(white_king, source);
        set_bit(white_king, target);
    } else if (black_pawns & piece_mask) {
        clear_bit(black_pawns, source);
        set_bit(black_pawns, target);
    } else if (black_knights & piece_mask) {
        clear_bit(black_knights, source);
        set_bit(black_knights, target);
    } else if (black_bishops & piece_mask) {
        clear_bit(black_bishops, source);
        set_bit(black_bishops, target);
    } else if (black_rooks & piece_mask) {
        clear_bit(black_rooks, source);
        set_bit(black_rooks, target);
    } else if (black_queens & piece_mask) {
        clear_bit(black_queens, source);
        set_bit(black_queens, target);
    } else if (black_king & piece_mask) {
        clear_bit(black_king, source);
        set_bit(black_king, target);
    }

    white_board = white_pawns | white_knights | white_bishops | white_rooks | white_queens | white_king;
    black_board = black_pawns | black_knights | black_bishops | black_rooks | black_queens | black_king;
    full_board = white_board | black_board;
}

int main() 
{
    std::cout << bitboard_representation << std::endl;

    Bitboard demonstrative_board = 0x8000000001000002ULL;
    std::cout << "DEMONTRATIVE BOARD: " << std::endl;
    print_bitboard_as_bytes(demonstrative_board);
    print_graphic_bitboard(demonstrative_board);

    std::cout << "ALLIES BOARD: " << std::endl;
    print_bitboard_as_bytes(allies_board_test);
    print_graphic_bitboard(allies_board_test);

    std::cout << "ENEMY BOARD: " << std::endl;
    print_bitboard_as_bytes(enemy_board_test);
    print_graphic_bitboard(enemy_board_test);

    Bitboard test_board_1 = 0x0000000000000400ULL;
    std::cout << "TEST BOARD: " << std::endl;
    print_bitboard_as_bytes(test_board_1);
    print_graphic_bitboard(test_board_1);

    std::cout << "ROOK: " << std::endl;
    print_graphic_bitboard(generate_all_rooks_moves(test_board_1));

    std::cout << "BISHOP: " << std::endl;
    print_graphic_bitboard(generate_all_bishops_moves(test_board_1));

    std::cout << "KING: " << std::endl;
    print_graphic_bitboard(generate_all_kings_moves(test_board_1));

    std::cout << "QUEEN: " << std::endl;
    print_graphic_bitboard(generate_all_queens_moves(test_board_1));

    std::cout << "KNIGHT: " << std::endl;
    print_graphic_bitboard(generate_all_knights_moves(test_board_1));
    
    std::cout << "PAWN: " << std::endl;
    print_graphic_bitboard(generate_all_pawns_moves(test_board_1));

    std::cout << " CHAR BOARD: " << std::endl;
    char* char_board = get_char_list_board(
        white_pawns, white_knights, white_rooks, 
        white_bishops, white_queens, white_king,
        black_pawns, black_knights, black_rooks, 
        black_bishops, black_queens, black_king
    );
    for (int n = 63; n >= 0; n--) {
        std::cout << ' ' << char_board[n];
        if (n % 8 == 0) std::cout << std::endl;
    }
    delete[] char_board;

    return 0;
}
