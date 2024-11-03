#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

typedef uint64_t Bitboard;

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


void reset_board()
{

}


void start_new_game() 
{

}

std::pair<int, int> move_to_square_indices(const std::string &move)
{
    int source = (move[0] - 'a') + (8 - (move[1] - '1' + 1)) * 8;
    int target = (move[2] - 'a') + (8 - (move[3] - '1' + 1)) * 8;
    return {source, target};
}

void clear_bit(uint64_t &bitboard, int square)
{
    bitboard &= ~(1ULL << square);
}

void set_bit(uint64_t &bitboard, int square)
{
    bitboard |= (1ULL << square);
}

void apply_move_startpos(const std::string &move)
{
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

void apply_move_fen(const std::string &fen)
{
    white_pawns = white_knights = white_bishops = white_rooks = white_queens = white_king = 0;
    black_pawns = black_knights = black_bishops = black_rooks = black_queens = black_king = 0;

    std::istringstream ss(fen);
    std::string position;
    ss >> position;

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

    white_board = white_pawns | white_knights | white_bishops | white_rooks | white_queens | white_king;
    black_board = black_pawns | black_knights | black_bishops | black_rooks | black_queens | black_king;
    full_board = white_board | black_board;
}

void get_best_move()
{

}

void identify_engine() 
{
    std::cout << "id name TryChess 0.1\n";
    std::cout << "id author Kamil Bylinka\n";
}

void handle_isready() 
{
    std::cout << "readyok\n";
}

void handle_uci() 
{
    identify_engine();
    std::cout << "uciok\n";
}

void handle_ucinewgame() 
{
    start_new_game();
    std::cout << "New game initialized\n";
}

void handle_position(std::stringstream &ss) 
{
    std::string subcommand;
    ss >> subcommand;

    if (subcommand == "startpos") {
        reset_board();
        std::string moves;
        if (ss >> moves && moves == "moves") {
            std::string move;
            while (ss >> move) {
                apply_move_startpos(move);
            }
        }
    } else if (subcommand == "fen") {
        std::string fen;
        std::getline(ss, fen);
        apply_move_fen(fen);
    }
}

void handle_go(std::stringstream &ss) 
{
    std::string searchCommand;
    ss >> searchCommand;
    get_best_move();

    std::cout << "bestmove xXxX" << std::endl;
}

void handle_quit()
{
    std::cout << "Exiting..." << std::endl;
}

void UCI_loop() {
    std::string input, command;

    while (true) {
        std::getline(std::cin, input); 
        std::stringstream ss(input);
        ss >> command;

        if (command == "uci") {
            handle_uci();
        }
        else if (command == "isready") {
            handle_isready();
        }
        else if (command == "ucinewgame") {
            handle_ucinewgame();
        }
        else if (command == "position") {
            handle_position(ss);
        }
        else if (command == "go") {
            handle_go(ss);
        }
        else if (command == "quit") {
            handle_quit();
            break;
        }
    }
}