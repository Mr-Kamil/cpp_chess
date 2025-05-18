#include "help_functions.h"

inline void helpers::write_log(const std::string &message) 
{
    if (log_file.is_open()) {
            log_file << message;
        }
}

void helpers::log_bitboard_as_bytes(const Bitboard &board)
{
    std::stringstream ss;
    
    ss << "Bitboard in hex: 0x" 
       << std::hex << std::setw(16) << std::setfill('0') 
       << board << '\n';

    helpers::write_log(ss.str());
}

void helpers::log_graphic_bitboard(const Bitboard &board)
{
    std::stringstream ss;

    for (int rank = 7; rank >= 0; --rank) {
        for (int file = 0; file < 8; ++file) {
            if (board & (1ULL << (rank * 8 + file)))
                ss << "1  ";
            else
                ss << "0  ";
        }
        ss << '\n';
    }
    ss << '\n';
    
    helpers::write_log(ss.str());
}

void helpers::log_graphic_chessboard(const std::string &board_str) 
{
    std::stringstream ss;

    for (int rank = 7; rank >= 0; --rank) {
        for (int file = 0; file < 8; ++file) {
            int square = rank * 8 + file; 
            ss << board_str[square] << "  ";
        }
        ss << "\n";
    }
    
    helpers::write_log(ss.str());
}

void helpers::log_board(const std::string &message) 
{
    helpers::write_log("BOARD: " + message + '\n');
}

void helpers::log_input(const std::string &message) 
{
    helpers::write_log("\nREAD: " + message + '\n');
}

void helpers::log_output(const std::string &message) 
{
    helpers::write_log("SEND: " + message + '\n');
}

void helpers::print_moves_string(const std::vector<std::string> &moves)
{
    std::cout << "Print moves...\n";
    for (const std::string &move : moves) {
        std::cout << move << '\n';
    }
}
