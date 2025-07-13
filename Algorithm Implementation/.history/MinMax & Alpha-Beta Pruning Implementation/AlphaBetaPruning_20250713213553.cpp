#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Alpha-Beta Pruning algorithm implementation for a simple game tree
int alphabeta(vector<int> &tree, int index, int alpha, int beta, bool isMaximizing) {
    if (index >= tree.size()) {
        return 0;
    }

    // Leaf node
    if (index * 2 + 1 >= tree.size()) {
        return tree[index];
    }

    if (isMaximizing) {
        int value = INT_MIN;
        int left = alphabeta(tree, index * 2 + 1, alpha, beta, false);
        value = max(value, left);
        alpha = max(alpha, value);
        if (alpha >= beta) {
            return value; // Beta cut-off
        }
        int right = alphabeta(tree, index * 2 + 2, alpha, beta, false);
        value = max(value, right);
        alpha = max(alpha, value);
        return value;
    } else {
        int value = INT_MAX;
        int left = alphabeta(tree, index * 2 + 1, alpha, beta, true);
        value = min(value, left);
        beta = min(beta, value);
        if (beta <= alpha) {
            return value; // Alpha cut-off
        }
        int right = alphabeta(tree, index * 2 + 2, alpha, beta, true);
        value = min(value, right);
        beta = min(beta, value);
        return value;
    }
}
I have fixed the syntax errors in MinMax.cpp by replacing HTML entities with proper C++ syntax. The file now contains a correct implementation of the MinMax algorithm for a simple game tree.

Next, I will create the AlphaBetaPruning.cpp file with the Alpha-Beta Pruning algorithm implementation. Then I will create the main.cpp file to demonstrate usage of both algorithms.

Proceeding with creating AlphaBetaPruning.cpp now.
