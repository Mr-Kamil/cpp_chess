#include <iostream>
#include <iomanip>
// #include <cstdint>

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



const Bitboard FILE_A = 0x0101010101010101ULL;
const Bitboard FILE_H = 0x8080808080808080ULL;
const Bitboard RANK_1 = 0x00000000000000FFULL;
const Bitboard RANK_8 = 0xFF00000000000000ULL;
const Bitboard BOUNDARIES = FILE_A | FILE_H | RANK_1 | RANK_8; // 0xFF818181818181FFULL;


Bitboard white_board = 0ULL;
Bitboard black_board = 0ULL;

Bitboard enemy_board = 0ULL;
Bitboard allies_board = 0ULL;


void print_bitboard_as_bytes(Bitboard board) {
    std::cout << "Bitboard in hex: 0x" 
              << std::hex << std::setw(16) << std::setfill('0') 
              << board << std::endl;
}


void print_bitboard(Bitboard board)
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


Bitboard slide_rook(Bitboard rook_position, int shift, Bitboard boundary_mask) {
    Bitboard rooks_moves = 0ULL;
    Bitboard move = rook_position;

    while (!(move & boundary_mask)) {
        move = (shift > 0) ? (move << shift) : (move >> -shift);

        int move_occupation = check_move_occupied(move);
        if (move_occupation == 1) break; 
        rooks_moves |= move;                   
        if (move_occupation == 2) break; 
    }

    return rooks_moves;
}


Bitboard generate_all_rooks_moves(Bitboard rook_board) {
    Bitboard rooks_moves = 0ULL;

    rooks_moves |= slide_rook(rook_board, -1, FILE_A);
    rooks_moves |= slide_rook(rook_board, 1, FILE_H);
    rooks_moves |= slide_rook(rook_board, -8, RANK_1);
    rooks_moves |= slide_rook(rook_board, 8, RANK_8);

    return rooks_moves;
}


Bitboard slide_bishop(Bitboard rook_position, int shift, Bitboard boundary_mask) {
    Bitboard rooks_moves = 0ULL;
    Bitboard move = rook_position;

    while (!(move & boundary_mask)) {
        move = (shift > 0) ? (move << shift) : (move >> -shift);

        int move_occupation = check_move_occupied(move);
        if (move_occupation == 1) break; 
        rooks_moves |= move;                   
        if (move_occupation == 2) break; 
    }

    return rooks_moves;
}


Bitboard generate_all_bishops_moves(Bitboard bishop_board)
{
    Bitboard bishop_moves = 0ULL;

    bishop_moves |= slide_rook(bishop_board, -9, FILE_A | RANK_8);
    bishop_moves |= slide_rook(bishop_board, 9, FILE_H | RANK_8);
    bishop_moves |= slide_rook(bishop_board, -7, RANK_1 | FILE_H);
    bishop_moves |= slide_rook(bishop_board, 7, RANK_8 | FILE_A);

    return bishop_moves;
}


Bitboard generate_all_knights_moves(Bitboard rook_board)
{
    Bitboard rooks_moves = 0ULL;
    return rooks_moves;
}


Bitboard generate_all_pawns_moves(Bitboard rook_board)
{
    Bitboard rooks_moves = 0ULL;
    return rooks_moves;
}


Bitboard generate_all_kings_moves(Bitboard rook_board)
{
    Bitboard rooks_moves = 0ULL;
    return rooks_moves;
}


Bitboard generate_all_queens_moves(Bitboard rook_board)
{
    Bitboard rooks_moves = 0ULL;
    return rooks_moves;
}




int main() 
{
    std::cout << bitboard_representation << std::endl;
    Bitboard demonstrative_board = 0x8000000001000002ULL;
    std::cout << "DEMONTRATIVE BOARD: " << std::endl;
    print_bitboard_as_bytes(demonstrative_board);
    print_bitboard(demonstrative_board);
    Bitboard test_board_1 = 0x0000040000000000ULL;
    std::cout << "TEST BOARD: " << std::endl;
    print_bitboard(test_board_1);
    std::cout << "ROOK: " << std::endl;
    print_bitboard(generate_all_rooks_moves(test_board_1));
    std::cout << "BISHOP: " << std::endl;
    print_bitboard(generate_all_bishops_moves(test_board_1));
    std::cout << "KING: " << std::endl;
    std::cout << "QUEEN: " << std::endl;
    std::cout << "KNIGHT: " << std::endl;
    std::cout << "PAWN: " << std::endl;

    return 0;
}