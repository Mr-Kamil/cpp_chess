#include <iostream>


typedef uint64_t Bitboard;


Bitboard white_board = 0ULL;
Bitboard black_board = 0ULL;


Bitboard generate_all_rooks_moves(Bitboard rook_board)
{
    Bitboard rooks_moves = 0ULL;
    return rooks_moves;
}


Bitboard generate_all_bishops_moves(Bitboard rook_board)
{
    Bitboard rooks_moves = 0ULL;
    return rooks_moves;
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




void printBitboard(Bitboard board) {
    for (int rank = 7; rank >= 0; --rank) {
        for (int file = 0; file < 8; ++file) {
            if (board & (1ULL << (rank * 8 + file)))
                std::cout << "1 ";
            else
                std::cout << "0 ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}




int main() 
{



    return 0;
}