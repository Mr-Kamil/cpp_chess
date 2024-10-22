#include <iostream>
#include <iomanip>

typedef uint64_t Bitboard;

std::string bitboard_representation = R"(
Bitboard
            A  B  C  D  E  F  G  H
bits:    8  0  0  0  0  0  0  0  0  8     bytes: 0
bits:    7  0  0  0  0  0  0  0  0  7     bytes: 0
bits:    6  0  0  0  0  0  0  0  0  6     bytes: 0
bits:    6  0  0  0  0  0  0  0  0  5     bytes: 0
bits:    4  0  0  0  0  0  0  0  0  4     bytes: 0
bits:    3  0  0  0  0  0  0  0  0  3     bytes: 0
bits:    2  0  0  0  0  0  0  0  0  2     bytes: 0
bits:    1  0  0  0  0  0  0  0  0  1     bytes: 0
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

Bitboard white_board = 0ULL;
Bitboard black_board = 0ULL;

Bitboard enemy_board = 0x00'00'00'00'00'08'00'00ULL;
Bitboard allies_board = 0x00'00'00'00'00'00'40'00ULL;


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
    if (move & enemy_board) {
        return 2;
    } else if (move & allies_board) {
        return 1;
    } else {
        return 0;
    }
}


Bitboard slide_piece(Bitboard piece_position, int shift, Bitboard boundary_mask, bool single_move=false) 
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
    Bitboard queens_moves = generate_all_bishops_moves(queen_board) | generate_all_rooks_moves(queen_board);
    return queens_moves;
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
    return pawns_moves;
}


Bitboard generate_all_kings_moves(Bitboard king_board)
{
    Bitboard king_moves = 0ULL;

    king_moves |= slide_piece(king_board, -1, FILE_A, true);
    king_moves |= slide_piece(king_board, 1, FILE_H, true);
    king_moves |= slide_piece(king_board, -8, RANK_1, true);
    king_moves |= slide_piece(king_board, 8, RANK_8, true);

    return king_moves;
}


int main() 
{
    std::cout << bitboard_representation << std::endl;

    Bitboard demonstrative_board = 0x8000000001000002ULL;
    std::cout << "DEMONTRATIVE BOARD: " << std::endl;
    print_bitboard_as_bytes(demonstrative_board);
    print_graphic_bitboard(demonstrative_board);

    std::cout << "ALLIES BOARD: " << std::endl;
    print_bitboard_as_bytes(allies_board);
    print_graphic_bitboard(allies_board);

    std::cout << "ENEMY BOARD: " << std::endl;
    print_bitboard_as_bytes(enemy_board);
    print_graphic_bitboard(enemy_board);

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

    return 0;
}