#include "uci.h"

ChessRules chess_rules = ChessRules();
ChessAlgorithm chess_algorithm = ChessAlgorithm();
std::ofstream log_file("uci_log.txt");


void manage_output(const std::string &message)
{
    helpers::log_output(message);
    std::cout << message + "\n" << std::endl;
}

void start_new_game() 
{
    chess_rules.set_start_positions();
    chess_rules.set_board_starting_variables();
    chess_rules.clear_move_logs();
}

void handle_isready() 
{   
    manage_output("readyok");
}

void identify_engine() 
{
    manage_output("id name cpp_chess 1.0");
    manage_output("id author Kamil Bylinka");
}

void handle_uci() 
{
    identify_engine();
    manage_output("uciok");
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
        chess_rules.apply_moves_startpos(ss);
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
    // TODO searching parameters

    best_move = chess_algorithm.get_best_move_nega_max(chess_rules, 2);
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

        helpers::log_input(input);

        if (command == "uci") {
            handle_uci();
        }
        else if (command == "isready") {
            handle_isready();
        }
        else if (command == "ucinewgame") {
            handle_ucinewgame();
            helpers::log_graphic_chessboard(chess_rules.get_char_list_board());
        }
        else if (command == "position") {
            handle_position(ss);
            helpers::log_graphic_chessboard(chess_rules.get_char_list_board());
        }
        else if (command == "go") {
            handle_go(ss);
            helpers::log_graphic_chessboard(chess_rules.get_char_list_board());
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
