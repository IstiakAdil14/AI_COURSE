#include <iostream>
#include <vector>
#include <limits>

using namespace std;

class MinMaxAlphaBeta {
public:
    char max_player = 'X'; // AI
    char min_player = 'O'; // Human

    int min_max(vector<vector<char>> &board, int depth, bool is_maximizing) {
        char winner = check_winner(board);
        if (winner == max_player) return 1;
        else if (winner == min_player) return -1;
        else if (is_board_full(board)) return 0;

        if (is_maximizing) {
            int best = numeric_limits<int>::min();
            for (auto &move : get_possible_moves(board)) {
                auto new_board = make_move(board, move, max_player);
                best = max(best, min_max(new_board, depth + 1, false));
            }
            return best;
        } else {
            int best = numeric_limits<int>::max();
            for (auto &move : get_possible_moves(board)) {
                auto new_board = make_move(board, move, min_player);
                best = min(best, min_max(new_board, depth + 1, true));
            }
            return best;
        }
    }

    int alpha_beta(vector<vector<char>> &board, int depth, bool is_maximizing, int alpha, int beta) {
        char winner = check_winner(board);
        if (winner == max_player) return 1;
        else if (winner == min_player) return -1;
        else if (is_board_full(board)) return 0;

        if (is_maximizing) {
            int best = numeric_limits<int>::min();
            for (auto &move : get_possible_moves(board)) {
                auto new_board = make_move(board, move, max_player);
                best = max(best, alpha_beta(new_board, depth + 1, false, alpha, beta));
                alpha = max(alpha, best);
                if (beta <= alpha) break;
            }
            return best;
        } else {
            int best = numeric_limits<int>::max();
            for (auto &move : get_possible_moves(board)) {
                auto new_board = make_move(board, move, min_player);
                best = min(best, alpha_beta(new_board, depth + 1, true, alpha, beta));
