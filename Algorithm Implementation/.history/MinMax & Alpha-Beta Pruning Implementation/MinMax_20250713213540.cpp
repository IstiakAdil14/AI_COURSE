#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// MinMax algorithm implementation for a simple game tree
int minmax(vector<int> &tree, int index, bool isMaximizing) {
    if (index >= tree.size()) {
        return 0;
    }

    // Leaf node
    if (index * 2 + 1 >= tree.size()) {
        return tree[index];
    }

    if (isMaximizing) {
        int left = minmax(tree, index * 2 + 1, false);
        int right = minmax(tree, index * 2 + 2, false);
        return max(left, right);
    } else {
        int left = minmax(tree, index * 2 + 1, true);
        int right = minmax(tree, index * 2 + 2, true);
        return min(left, right);
    }
}
