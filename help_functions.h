#ifndef HELP_FUNCTIONS_H
#define HELP_FUNCTIONS_H

#include "chess_rules.h"
#include "uci.h"

namespace helpers {

void log_bitboard_as_bytes(Bitboard board);

void log_graphic_bitboard(Bitboard board);

void log_graphic_chessboard(const std::string &board_str);

void log_board(const std::string &message);

void log_input(const std::string &message);

void log_output(const std::string &message);

void const print_moves_string_(std::vector<std::string> &moves);

} // helpers

#endif // HELP_FUNCTIONS_H