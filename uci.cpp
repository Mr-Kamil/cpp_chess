#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include "chess_rules.cpp"

ChessRules chess_rules = ChessRules();
std::ofstream log_file("uci_log.txt");

void log_bitboard_as_bytes(Bitboard board)
{
    if (log_file.is_open()) {
        log_file << "Bitboard in hex: 0x" 
                 << std::hex << std::setw(16) << std::setfill('0') 
                 << board << std::endl;
    }
}

void log_graphic_bitboard(Bitboard board)
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

void log_graphic_chessboard(const std::string &board_str) 
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

void log_board(const std::string &message) 
{
    if (log_file.is_open()) {
        log_file << "BOARD: " << message << std::endl;
    }
}

void manage_input(const std::string &message) 
{
    if (log_file.is_open()) {
        log_file << "\nREAD: " << message << std::endl;
    }
}

void manage_output(const std::string &message) 
{
    if (log_file.is_open()) {
        log_file << "SEND: " << message << std::endl;
    }
    std::cout << message + "\n" << std::endl;
}

void reset_board()
{
    chess_rules.set_start_positions();
}


void start_new_game() 
{
    chess_rules.set_start_positions();
}


void handle_isready() 
{   
    manage_output("readyok");
}

void identify_engine() 
{
    manage_output("id name TryChess 0.1");
    manage_output("id author Kamil Bylinka");
}

void handle_uci() 
{
    identify_engine();
    manage_output("uciok");
}

void log_positions()
{
    log_graphic_chessboard(chess_rules.get_char_list_board());
}

void handle_ucinewgame() 
{
    start_new_game();
    manage_output("New game initialized");
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
                chess_rules.apply_move_startpos(move);
            }
        }
    } else if (subcommand == "fen") {
        std::string fen;
        std::getline(ss, fen);
        chess_rules.apply_move_fen(fen);
    }
}

void handle_go(std::stringstream &ss) 
{
    std::string search_command;
    std::string best_move;
    
    ss >> search_command;
    // TODO
    best_move = chess_rules.get_best_move_nega_max(3);
    chess_rules.apply_move_startpos(best_move);

    manage_output("bestmove " + best_move);
}

void handle_quit()
{
    manage_output("Exiting...");
}

void UCI_loop()
{
    std::string input, command;

    while (true) {
        std::getline(std::cin, input); 
        std::stringstream ss(input);
        ss >> command;

        manage_input(input);

        if (command == "uci") {
            handle_uci();
        }
        else if (command == "isready") {
            handle_isready();
        }
        else if (command == "ucinewgame") {
            handle_ucinewgame();
            log_positions();
        }
        else if (command == "position") {
            handle_position(ss);
            log_positions();
        }
        else if (command == "go") {
            handle_go(ss);
            log_positions();
        }
        else if (command == "quit") {
            handle_quit();
            break;
        }
    }
}

int main()
{   
    UCI_loop();

    return 0;
}
