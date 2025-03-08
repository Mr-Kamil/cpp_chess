#include "help_functions.h"

void helpers::log_bitboard_as_bytes(Bitboard board)
{
    if (log_file.is_open()) {
        log_file << "Bitboard in hex: 0x" 
                 << std::hex << std::setw(16) << std::setfill('0') 
                 << board << std::endl;
    }
}

void helpers::log_graphic_bitboard(Bitboard board)
{
    if (log_file.is_open()) {
        for (int rank = 7; rank >= 0; --rank) {
            for (int file = 0; file < 8; ++file) {
                if (board & (1ULL << (rank * 8 + file)))
                    log_file << "1  ";
                else
                    log_file << "0  ";
            }
            log_file << std::endl;
        }
        log_file << std::endl;
    }
}

void helpers::log_graphic_chessboard(const std::string &board_str) 
{
    if (log_file.is_open()) {
        for (int rank = 7; rank >= 0; --rank) {
            for (int file = 0; file < 8; ++file) {
                int square = rank * 8 + file; 
                log_file << board_str[square] << "  ";
            }
            log_file << "\n";
        }
    }
}

void helpers::log_board(const std::string &message) 
{
    if (log_file.is_open()) {
        log_file << "BOARD: " << message << std::endl;
    }
}

void helpers::log_input(const std::string &message) 
{
    if (log_file.is_open()) {
        log_file << "\nREAD: " << message << std::endl;
    }
}

void helpers::log_output(const std::string &message) 
{
    if (log_file.is_open()) {
        log_file << "SEND: " << message << std::endl;
    }
}

void const helpers::print_moves_string_(std::vector<std::string> &moves)
{
    std::cout << "Print moves...\n";
    for (const std::string &move : moves) {
        std::cout << move << std::endl;
    }
}
