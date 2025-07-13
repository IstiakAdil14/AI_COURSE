#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

// Depth-First Search (DFS) implementation on a graph using adjacency list
class DFS {
public:
    DFS(const unordered_map<int, vector<int>>& graph) : graph(graph) {}

    void search(int start_node) {
        unordered_set<int> visited;
        cout << "DFS traversal starting from node " << start_node << ": ";
        dfs_helper(start_node, visited);
        cout << endl;
    }

private:
    unordered_map<int, vector<int>> graph;

    void dfs_helper(int node, unordered_set<int>& visited) {
        if (visited.find(node) != visited.end()) return;
        visited.insert(node);
        cout << node << " ";

        for (int neighbor : graph.at(node)) {
            dfs_helper(neighbor, visited);
        }
    }
};

int main() {
    // Example graph as adjacency list
    unordered_map<int, vector<int>> graph = {
        {1, {2, 3}},
        {2, {4}},
        {3, {4, 5}},
        {4, {6}},
        {5, {}},
        {6, {}}
    };

    DFS dfs(graph);
    dfs.search(1);

    return 0;
}
