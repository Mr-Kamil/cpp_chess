#ifndef UCI_H
#define UCI_H

#include <fstream>
#include "chess_rules.h"
#include "chess_algorithm.h"
#include "help_functions.h"

extern ChessRules chess_rules;
extern std::ofstream log_file;

void manage_input(const std::string &message);

void manage_output(const std::string &message);

void reset_board();

void start_new_game();

void handle_isready();

void identify_engine();

void handle_uci(); 

void log_positions();

void handle_ucinewgame();

void handle_position(std::stringstream &ss);

void handle_go(std::stringstream &ss);

void handle_quit();

void UCI_loop();

#endif // UCI_H
