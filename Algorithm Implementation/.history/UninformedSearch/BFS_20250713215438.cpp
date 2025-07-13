#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;

// Breadth-First Search (BFS) implementation on a graph using adjacency list
class BFS {
public:
    BFS(const unordered_map<int, vector<int>>& graph) : graph(graph) {}

    void search(int start_node) {
        queue<int> q;
        unordered_set<int> visited;

        q.push(start_node);
        visited.insert(start_node);

        cout << "BFS traversal starting from node " << start_node << ": ";

        while (!q.empty()) {
            int current = q.front();
            q.pop();
            cout << current << " ";

            for (int neighbor : graph.at(current)) {
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
    }

private:
    unordered_map<int, vector<int>> graph;
};

int main() {
    // Example graph as adjacency list
    unordered_map<int, vector<int>> graph = {
        {1, {2, 3}},
        {2, {4}},
        {3, {4, 5}},
