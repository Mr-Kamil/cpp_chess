#ifndef CHESS_ALGORITHM_H
#define CHESS_ALGORITHM_H

#include "chess_rules.h"


class ChessAlgorithm 
{
    static constexpr int PAWN_VALUE = 1;
    static constexpr int KNIGHT_VALUE = 3;
    static constexpr int BISHOP_VALUE = 3;
    static constexpr int ROOK_VALUE = 5;
    static constexpr int QUEEN_VALUE = 9;
    static constexpr int KING_VALUE = 1000;

    static constexpr int checkmate = 1000;

    public:
        std::string get_best_move_nega_max(
            ChessRules &chess_rules, int depth
        ) const;

        int find_nega_max_move_alpha_beta(
            ChessRules &chess_rules, int depth, int &max_depth, 
            int turn_multiplier, int alpha, int beta
        ) const;

        int score_material(ChessRules &chess_rules) const;
};

#endif // CHESS_ALGORITHM_H
