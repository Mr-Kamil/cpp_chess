#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>


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

}

void apply_move_fen(const std::string &fen)
{

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