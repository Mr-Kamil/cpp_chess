#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>

typedef uint64_t Bitboard;
// std::string bitboard_representation = R"(
// Bitboard
//             A  B  C  D  E  F  G  H
// bits:    8  0  0  0  0  0  0  0  1  8     bytes: 0x80'00'00'00'00'00'00'00ULL
// bits:    7  0  0  0  0  0  0  1  0  7     bytes: 0x00'40'00'00'00'00'00'00ULL
// bits:    6  0  0  0  0  0  1  0  0  6     bytes: 0x00'00'20'00'00'00'00'00ULL
// bits:    5  0  0  0  0  1  0  0  0  5     bytes: 0x00'00'00'10'00'00'00'00ULL
// bits:    4  0  0  0  1  0  0  0  0  4     bytes: 0x00'00'00'00'08'00'00'00ULL
// bits:    3  0  0  1  0  0  0  0  0  3     bytes: 0x00'00'00'00'00'04'00'00ULL
// bits:    2  0  1  0  0  0  0  0  0  2     bytes: 0x00'00'00'00'00'00'02'00ULL
// bits:    1  1  0  0  0  0  0  0  0  1     bytes: 0x00'00'00'00'00'00'00'01ULL
//             A  B  C  D  E  F  G  H

//            A  B  C  D  E  F  G  H
//         8  r  n  b  q  k  b  n  r  8     
//         7  p  p  p  p  p  p  p  p  7     
//         6  0  0  0  0  0  0  0  0  6     
//         5  0  0  0  0  0  0  0  0  5     
//         4  0  0  0  0  0  0  0  0  4     
//         3  0  0  0  0  0  0  0  0  3     
//         2  P  P  P  P  P  P  P  P  2     
//         1  R  N  B  Q  K  B  N  R  1     
//            A  B  C  D  E  F  G  H

// )";


class ChessRules
{
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

    bool white_to_move;
    bool en_passant;

    std::vector<std::string> move_logs = {};

public:
    ChessRules() 
    {
        this->reset();
    }

public:
    void reset()
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

    this->last_move_begin = 0ULL;
    this->last_move_end = 0ULL;

    this->white_king_side_castling = true;
    this->white_queen_side_castling = true;

    this->black_king_side_castling = true;
    this->black_queen_side_castling = true;

    this->white_to_move = true;
    this->en_passant = false;

    this->move_logs = {};
    }

public:
    Bitboard get_full_board()
    {
        return this->full_board;
    }

public:
    char *get_char_list_board()
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


public:
    void get_bitboards_from_char_list(const char* char_board) 
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


public:
    void print_bitboard_as_bytes(Bitboard board)
    {
        std::cout << "Bitboard in hex: 0x" 
                << std::hex << std::setw(16) << std::setfill('0') 
                << board << std::endl;
    }


public:
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

public: 
    void print_graphic_chessboard(const std::string &board_str) 
    {
        for (int rank = 7; rank >= 0; --rank) {
            for (int file = 0; file < 8; ++file) {
                int square = rank * 8 + file; 
                std::cout << board_str[square] << "  ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }

private:
    int check_move_occupied(Bitboard move)
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


private:
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


private:
    Bitboard generate_all_rooks_moves(Bitboard rook_board) 
    {
        Bitboard rooks_moves = 0ULL;

        rooks_moves |= slide_piece(rook_board, -1, this->FILE_A);
        rooks_moves |= slide_piece(rook_board, 1, this->FILE_H);
        rooks_moves |= slide_piece(rook_board, -8, this->RANK_1);
        rooks_moves |= slide_piece(rook_board, 8, this->RANK_8);

        return rooks_moves;
    }


private:
    Bitboard generate_all_bishops_moves(Bitboard bishop_board)
    {
        Bitboard bishop_moves = 0ULL;

        bishop_moves |= slide_piece(bishop_board, 7, this->FILE_A | this->RANK_8);
        bishop_moves |= slide_piece(bishop_board, 9, this->FILE_H | this->RANK_8);
        bishop_moves |= slide_piece(bishop_board, -9, this->RANK_1 | this->FILE_H);
        bishop_moves |= slide_piece(bishop_board, -7, this->RANK_1 | this->FILE_A);

        return bishop_moves;
    }


private:
    Bitboard generate_all_knights_moves(Bitboard knights_board)
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


private:
    Bitboard generate_all_queens_moves(Bitboard queen_board)
    {
        Bitboard queens_moves = generate_all_bishops_moves(
            queen_board) | generate_all_rooks_moves(queen_board);
        return queens_moves;
    }


private:
    Bitboard make_queen_side_castling(Bitboard king_board)
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


private:
    Bitboard make_king_side_castling(Bitboard king_board)
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


private:
    Bitboard generate_all_kings_moves(Bitboard king_board)
    {
        Bitboard king_moves = 0ULL;

        king_moves |= slide_piece(king_board, -1, this->FILE_A, true);
        king_moves |= slide_piece(king_board, 1, this->FILE_H, true);
        king_moves |= slide_piece(king_board, -8, this->RANK_1, true);
        king_moves |= slide_piece(king_board, 8, this->RANK_8, true);

        king_moves |= make_queen_side_castling(king_board);
        king_moves |= make_king_side_castling(king_board);

        return king_moves;
    }


private:
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


private:
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


private:
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


private:
    Bitboard en_passant_move(Bitboard pawn_position) 
    {
        Bitboard en_passant_move = 0ULL;
        Bitboard pawns_start_squares = 0ULL;

        if (this->white_to_move) {
            pawns_start_squares = RANK_5;
        } else {
            pawns_start_squares = RANK_4;
        }

        if (this->en_passant && (pawn_position & pawns_start_squares)) {
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


private:
    Bitboard generate_all_pawns_moves(Bitboard pawn_board)
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
        pawns_moves |= en_passant_move(pawn_board);

        return pawns_moves;
    }


private:
    void clear_bit(uint64_t &bitboard, int square)
    {
        bitboard &= ~(1ULL << square);
    }


private:
    void set_bit(uint64_t &bitboard, int square)
    {
        bitboard |= (1ULL << square);
    }


public:
    std::pair<int, int> move_to_square_indices(const std::string &move)
    {
        int source = (move[0] - 'a') + ((move[1] - '1') * 8);
        int target = (move[2] - 'a') + ((move[3] - '1') * 8);
        // std::cout << source << ' ' << target << std::endl;
        return {source, target};
    }


public:
    void apply_move_startpos(const std::string &move)
    {
        // e.g: position startpos moves [e2e4 e7e5 g1f3 b8c6]
        // std::cout << move << std::endl;
        std::pair<int, int> indicases = move_to_square_indices(move);
        int source = indicases.first;
        int target = indicases.second;
        // std::cout << source << " - " << target << std::endl;
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

        uint64_t start_piece_mask = (1ULL << source);
        // std::cout << start_piece_mask << '=' << end_piece_mask << std::endl;
        if (this->white_board & start_piece_mask) {
            if (this->white_pawns & start_piece_mask) {
                clear_bit(this->white_pawns, source);
                set_bit(this->white_pawns, target);
            } else if (this->white_knights & start_piece_mask) {
                clear_bit(this->white_knights, source);
                set_bit(this->white_knights, target);
            } else if (this->white_bishops & start_piece_mask) {
                clear_bit(this->white_bishops, source);
                set_bit(this->white_bishops, target);
            } else if (this->white_rooks & start_piece_mask) {
                clear_bit(this->white_rooks, source);
                set_bit(this->white_rooks, target);
            } else if (this->white_queens & start_piece_mask) {
                clear_bit(this->white_queens, source);
                set_bit(this->white_queens, target);
            } else if (this->white_king & start_piece_mask) {
                clear_bit(this->white_king, source);
                set_bit(this->white_king, target);
            } 
        } else if (this->black_board & start_piece_mask) {
            if (this->black_pawns & start_piece_mask) {
                clear_bit(this->black_pawns, source);
                set_bit(this->black_pawns, target);
            } else if (this->black_knights & start_piece_mask) {
                clear_bit(this->black_knights, source);
                set_bit(this->black_knights, target);
            } else if (this->black_bishops & start_piece_mask) {
                clear_bit(this->black_bishops, source);
                set_bit(this->black_bishops, target);
            } else if (this->black_rooks & start_piece_mask) {
                clear_bit(this->black_rooks, source);
                set_bit(this->black_rooks, target);
            } else if (this->black_queens & start_piece_mask) {
                clear_bit(this->black_queens, source);
                set_bit(this->black_queens, target);
            } else if (this->black_king & start_piece_mask) {
                clear_bit(this->black_king, source);
                set_bit(this->black_king, target);
            }
        }

        this->white_board = this->white_pawns | this->white_knights | 
                            this->white_bishops | this->white_rooks | 
                            this->white_queens | this->white_king;
        this->black_board = this->black_pawns | this->black_knights | 
                            this->black_bishops | this->black_rooks | 
                            this->black_queens | this->black_king;
        this->full_board = this->white_board | this->black_board;
        this->white_to_move = !this->white_to_move;
    }


public:
    void apply_move_fen(const std::string &fen)
    {
        // e.g: position fen [rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1]

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


private:
    void update_all_moves(std::vector<std::string> &all_moves, Bitboard start, Bitboard ends)
    {
        for (int index = 0; index < 64; index++) {
            if (ends & (1ULL << index)) {
                all_moves.push_back(this->bitboards_to_move(start, 1ULL << index));
            }
        }
    }


public:
    std::vector<std::string> get_all_moves()
    {
        int index = 0;
        Bitboard moves = 0ULL;
        std::vector<std::string> all_moves;
        all_moves.clear();

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

            this->update_all_moves(all_moves, 1ULL << index, moves);
            index++;
        }
        return all_moves;
    }


public:
    std::string get_best_move()
    {
        std::string best_move;
        std::vector<std::string> all_moves;
        
        all_moves = this->get_all_moves();
        // TODO
        best_move = all_moves[0];
        this->white_to_move = !this->white_to_move;

        return best_move;
    }



public:
    void check_is_move_valid()
    {

    }


public:
    void make_move()
    {
        
    }


public:
    void undo_move()
    {

    }


    int bitboard_to_index(Bitboard bb) 
    {
        int index = 0;

        while (bb != 0) {
            if (bb & 1) {
                return index;
            }
            bb >>= 1;
            index++;
        }
        return -1;
    }


    std::string index_to_square(int index) 
    {
        int file = index % 8;
        int rank = index / 8;
        char file_char = 'a' + file;
        char rank_char = '1' + rank;
        return std::string() + file_char + rank_char;
    }


    std::string bitboards_to_move(Bitboard move_begin, Bitboard move_end) 
    {
        int begin_index = bitboard_to_index(move_begin);
        int end_index = bitboard_to_index(move_end);

        std::string begin_square = index_to_square(begin_index);
        std::string end_square = index_to_square(end_index);

        return begin_square + end_square;
    }
};


// int main() 
// {
//     ChessRules chess_rules = ChessRules();
//     std::vector<std::string> all_moves;

//     all_moves = chess_rules.get_all_moves();


//     for (const std::string& move : all_moves) {
//         std::cout << move << std::endl;
//     }


//     std::string startpos_1 = "a7a6";
//     chess_rules.print_graphic_chessboard(chess_rules.get_char_list_board());
//     chess_rules.apply_move_startpos(startpos_1);
//     chess_rules.print_graphic_chessboard(chess_rules.get_char_list_board());
//     chess_rules.reset();
//     std::string startpos_2 = "d2d3";
//     chess_rules.print_graphic_chessboard(chess_rules.get_char_list_board());
//     chess_rules.apply_move_startpos(startpos_2);
//     chess_rules.print_graphic_chessboard(chess_rules.get_char_list_board());

//     return 0;
// }
