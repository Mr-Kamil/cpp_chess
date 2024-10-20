#include <iostream>
// #include <cstdint>

typedef uint64_t Bitboard;

/*
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
*/


const Bitboard FILE_A = 0x0101010101010101ULL;
const Bitboard FILE_H = 0x8080808080808080ULL;
const Bitboard RANK_1 = 0x00000000000000FFULL;
const Bitboard RANK_8 = 0xFF00000000000000ULL;



Bitboard white_board = 0ULL;
Bitboard black_board = 0ULL;

Bitboard enemy_board = 0ULL;
Bitboard allies_board = 0ULL;

Bitboard test_board = 0x8000000001000001ULL;


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


Bitboard generate_all_rooks_moves(Bitboard rook_board)
{
    Bitboard rooks_moves = 0ULL;
    Bitboard move;
    int move_occupation;

    move = rook_board;
    while (!(move & FILE_A)) {
        move >>= 1;
        move_occupation = check_move_occupied(move);

        if (move_occupation == 1) {
            break;
        }
        rooks_moves |= move;
        if (move_occupation == 2) {
            break;
        }
    }

    move = rook_board;
    while (!(move & FILE_H)) {
        move <<= 1;
        move_occupation = check_move_occupied(move);

        if (move_occupation == 1) {
            break;
        }
        rooks_moves |= move;
        if (move_occupation == 2) {
            break;
        }
    }

    move = rook_board;
    while (!(move & RANK_1)) {
        move >>= 8;
        move_occupation = check_move_occupied(move);

        if (move_occupation == 1) {
            break;
        }
        rooks_moves |= move;
        if (move_occupation == 2) {
            break;
        }
    }

    move = rook_board;
    while (!(move & RANK_8)) {
        move <<= 8;
        move_occupation = check_move_occupied(move);

        if (move_occupation == 1) {
            break;
        }
        rooks_moves |= move;
        if (move_occupation == 2) {
            break;
        }
    }

    return rooks_moves;
}


Bitboard generate_all_bishops_moves(Bitboard bishop_board)
{
    Bitboard bishop_moves = 0ULL;
    Bitboard move;
    int move_occupation;
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
    std::cout << std::endl;
    // print_bitboard(test_board);
    std::cout << std::endl;
    Bitboard test_board_1 = 0x0000040000000000ULL;
    print_bitboard(test_board_1);
    print_bitboard(generate_all_rooks_moves(test_board_1));


    return 0;
}