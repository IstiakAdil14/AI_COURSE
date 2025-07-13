#include <iostream>
#include <vector>
#include <limits>

using namespace std;

class MinMaxAlphaBeta {
public:
    char max_player = 'X'; // AI
    char min_player = 'O'; // Human

    int min_max(vector<vector<char>> &amp;board, int depth, bool is_maximizing) {
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

    int alpha_beta(vector<vector<char>> &amp;board, int depth, bool is_maximizing, int alpha, int beta) {
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
                beta = min(beta, best);
                if (beta <= alpha) break;
            }
            return best;
        }
    }

    pair<int, int> get_best_move(vector<vector<char>> &amp;board, bool is_maximizing) {
        pair<int, int> best_move = {-1, -1};
        int best_value = is_maximizing ? numeric_limits<int>::min() : numeric_limits<int>::max();

        for (auto &move : get_possible_moves(board)) {
            auto new_board = make_move(board, move, is_maximizing ? max_player : min_player);
            int board_value = alpha_beta(new_board, 0, !is_maximizing, numeric_limits<int>::min(), numeric_limits<int>::max());
            if ((is_maximizing && board_value > best_value) || (!is_maximizing && board_value < best_value)) {
                best_value = board_value;
                best_move = move;
            }
        }
        return best_move;
    }

    vector<pair<int, int>> get_possible_moves(vector<vector<char>> &amp;board) {
        vector<pair<int, int>> moves;
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                if (board[row][col] == ' ') {
                    moves.push_back({row, col});
                }
            }
        }
        return moves;
    }

    vector<vector<char>> make_move(vector<vector<char>> &amp;board, pair<int, int> move, char player) {
        vector<vector<char>> new_board = board;
        new_board[move.first][move.second] = player;
        return new_board;
    }

    char check_winner(vector<vector<char>> &amp;board) {
        for (int i = 0; i < 3; ++i) {
            if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') return board[i][0];
            if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') return board[0][i];
        }
        if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') return board[0][0];
        if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') return board[0][2];
        return ' ';
    }

    void print_board(vector<vector<char>> &amp;board) {
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                cout << board[row][col];
                if (col < 2) cout << " | ";
            }
            cout << endl;
            if (row < 2) cout << "---------" << endl;
        }
    }

private:
    bool is_board_full(vector<vector<char>> &amp;board) {
        for (auto &row : board) {
            for (auto &cell : row) {
                if (cell == ' ') return false;
            }
        }
        return true;
    }
};

int main() {
    MinMaxAlphaBeta game;
    vector<vector<char>> board(3, vector<char>(3, ' '));

    while (true) {
        game.print_board(board);
        char winner = game.check_winner(board);
        if (winner != ' ') {
            cout << "\nGame Over! Winner is: " << winner << endl;
            break;
        } else if (game.is_board_full(board)) {
            cout << "\nGame Over! It's a draw." << endl;
            break;
        }

        // Human player's move (O)
        int row, col;
        cout << "Enter your move row (0-2): ";
        cin >> row;
        cout << "Enter your move col (0-2): ";
        cin >> col;
        if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != ' ') {
            cout << "Invalid move. Try again." << endl;
            continue;
        }
        board[row][col] = game.min_player;

        // Check after human move
        winner = game.check_winner(board);
        if (winner != ' ') {
            game.print_board(board);
            cout << "\nGame Over! Winner is: " << winner << endl;
            break;
        } else if (game.is_board_full(board)) {
            game.print_board(board);
