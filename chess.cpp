#include <iostream>
#include <iomanip>

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
