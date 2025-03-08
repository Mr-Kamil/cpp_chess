#ifndef HELP_FUNCTIONS_H
#define HELP_FUNCTIONS_H

#include "chess_rules.h"
#include "uci.h"

namespace helpers {

void log_bitboard_as_bytes(Bitboard board);

void log_graphic_bitboard(Bitboard board);

void log_graphic_chessboard(const std::string &board_str);

void log_board(const std::string &message);

} // helpers

#endif // HELP_FUNCTIONS_H