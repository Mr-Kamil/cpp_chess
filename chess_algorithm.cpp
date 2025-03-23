#include "chess_algorithm.h"


std::string ChessAlgorithm::get_best_move_nega_max(
    ChessRules &chess_rules, int depth
) const
{
    chess_rules.next_move = "";
    int turn_multiplier = chess_rules.white_to_move ? 1 : -1;
    int alpha = -this->checkmate;
    int beta = this->checkmate;
    this->find_nega_max_move_alpha_beta(
        chess_rules, depth, depth, turn_multiplier, alpha, beta
    );

    return chess_rules.next_move;
}

int ChessAlgorithm::find_nega_max_move_alpha_beta(
    ChessRules &chess_rules, int depth, int &max_depth, 
    int turn_multiplier, int alpha, int beta
    ) const 
{
    if (depth == 0) {
        return turn_multiplier * this->score_material(chess_rules);
    }

    int max_score = -this->checkmate;
    std::vector<std::string> valid_moves = chess_rules.get_all_valid_moves_str();

    for (int n = 0; n < valid_moves.size(); n++) {
        std::string move = valid_moves[n];

        chess_rules.apply_move_startpos(move);
        int score = -find_nega_max_move_alpha_beta(
            chess_rules, depth - 1, max_depth, -turn_multiplier, -beta, -alpha
            );
        chess_rules.undo_move();

        if (score >= max_score) {
            max_score = score;
            if (depth == max_depth) {
                chess_rules.next_move = move;
            }
        }

        alpha = std::max(alpha, max_score);
        if (alpha >= beta) {
            break;
        }
    }
    return max_score;
}

int ChessAlgorithm::score_material(ChessRules &chess_rules) const
{
    int score = 0;

    auto count_bits = [](Bitboard bitboard) -> int 
    {
        int count = 0;
        while (bitboard) {
            count += bitboard & 1;
            bitboard >>= 1;
        }
        return count;
    };

    score += this->PAWN_VALUE * count_bits(chess_rules.white_pawns);
    score += this->KNIGHT_VALUE * count_bits(chess_rules.white_knights);
    score += this->BISHOP_VALUE * count_bits(chess_rules.white_bishops);
    score += this->ROOK_VALUE * count_bits(chess_rules.white_rooks);
    score += this->QUEEN_VALUE * count_bits(chess_rules.white_queens);
    score += this->KING_VALUE * count_bits(chess_rules.white_king);

    score -= this->PAWN_VALUE * count_bits(chess_rules.black_pawns);
    score -= this->KNIGHT_VALUE * count_bits(chess_rules.black_knights);
    score -= this->BISHOP_VALUE * count_bits(chess_rules.black_bishops);
    score -= this->ROOK_VALUE * count_bits(chess_rules.black_rooks);
    score -= this->QUEEN_VALUE * count_bits(chess_rules.black_queens);
    score -= this->KING_VALUE * count_bits(chess_rules.black_king);

    return score;
}