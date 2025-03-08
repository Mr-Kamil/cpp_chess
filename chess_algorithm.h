#ifndef CHESS_ALGORITHM_H
#define CHESS_ALGORITHM_H

#include "chess_rules.h"


class ChessAlgorithm {
    public:
        std::string get_best_move_nega_max(ChessRules& chess_rules, int depth);

        int find_nega_max_move_alpha_beta(
            ChessRules& chess_rules, int depth, int max_depth, 
            int turn_multiplier, int alpha, int beta
        );
        
        int score_material(ChessRules& chess_rules);

    };


#endif // CHESS_ALGORITHM_H
