#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

class Graph {
public:
    unordered_map<int, unordered_set<int>> graph;

    // Add undirected edge
    void add_edges(int u, int v) {
        graph[u].insert(v);
        graph[v].insert(u);
    }

    // Print adjacency list
    void iterate() {
        for (const auto& pair : graph) {
            cout << pair.first << " -> : { ";
            for (int neighbor : pair.second) {
                cout << neighbor << " ";
            }
            cout << "}" << endl;
        }
    }

    // BFS
    void bfs(int start) {
        unordered_set<int> visited;
        queue<int> q;
        visited.insert(start);
        q.push(start);

        cout << "BFS traversal starting from node " << start << ": ";
        while (!q.empty()) {
            int vertex = q.front();
            q.pop();
            cout << vertex << " ";

            vector<int> neighbors(graph[vertex].begin(), graph[vertex].end());
            sort(neighbors.begin(), neighbors.end());
            for (int neighbor : neighbors) {
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
    }

    // DFS
    void dfs(int node) {
        unordered_set<int> visited;
        cout << "DFS traversal starting from node " << node << ": ";
        dfs_helper(node, visited);
        cout << endl;
    }

    // Depth-Limited DFS
    bool depth_limited_dfs(int start, int target, int limit) {
        if (start == target) {
            cout << "Target Found!" << endl;
            return true;
        }
        if (limit <= 0) {
            return false;
        }
        for (int neighbor : graph[start]) {
            if (depth_limited_dfs(neighbor, target, limit - 1)) {
                return true;
            }
        }
        return false;
    }

    // Iterative Deepening Search
    bool ids(int start, int target, int max_depth_limit) {
        for (int depth = 0; depth <= max_depth_limit; ++depth) {
            cout << "Depth Level : " << depth << endl;
            bool found = depth_limited_dfs(start, target, depth);
            if (found) {
                cout << "Target Found at depth " << depth << endl;
                return true;
            }
            cout << "Not found in level " << depth << endl;
        }
        cout << "Target not found!" << endl;
        return false;
    }

    // Bidirectional Search
    vector<int> bds(int start, int goal) {
        if (start == goal) {
            return {start};
        }

        queue<int> frontier_start;
        queue<int> frontier_goal;
        frontier_start.push(start);
        frontier_goal.push(goal);

        unordered_map<int, int> visited_by_start;
        unordered_map<int, int> visited_by_goal;
        visited_by_start[start] = -1;
        visited_by_goal[goal] = -1;

        while (!frontier_start.empty() && !frontier_goal.empty()) {
            int result = forward_frontier(frontier_start, visited_by_start, visited_by_goal);
            if (result != -1) {
                return build_path(result, visited_by_start, visited_by_goal);
            }
            result = forward_frontier(frontier_goal, visited_by_goal, visited_by_start);
            if (result != -1) {
                return build_path(result, visited_by_start, visited_by_goal);
            }
        }
        return {};
    }

private:
    void dfs_helper(int node, unordered_set<int>& visited) {
        if (visited.find(node) != visited.end()) return;
        visited.insert(node);
        cout << node << " ";
        for (int neighbor : graph[node]) {
            dfs_helper(neighbor, visited);
        }
    }

    int forward_frontier(queue<int>& frontier, unordered_map<int, int>& visited_by_self, unordered_map<int, int>& visited_by_other) {
        if (frontier.empty()) return -1;
        int current = frontier.front();
        frontier.pop();

        for (int neighbor : graph[current]) {
            if (visited_by_self.find(neighbor) == visited_by_self.end()) {
                visited_by_self[neighbor] = current;
                frontier.push(neighbor);
            }
            if (visited_by_other.find(neighbor) != visited_by_other.end()) {
                return neighbor;
            }
        }
        return -1;
    }

    vector<int> build_path(int meeting_point, unordered_map<int, int>& visited_by_start, unordered_map<int, int>& visited_by_goal) {
        vector<int> path_start;
        int node = meeting_point;
        while (node != -1) {
            path_start.push_back(node);
            node = visited_by_start[node];
        }
        reverse(path_start.begin(), path_start.end());

        vector<int> path_goal;
        node = visited_by_goal[meeting_point];
        while (node != -1) {
            path_goal.push_back(node);
            node = visited_by_goal[node];
        }

        path_start.insert(path_start.end(), path_goal.begin(), path_goal.end());
        return path_start;
    }
};

int main() {
    Graph g;
    g.add_edges(3, 6);
    g.add_edges(6, 0);
    g.add_edges(6, 4);
    g.add_edges(3, 9);
    g.add_edges(9, 5);
    g.add_edges(9, 7);

    g.iterate();

    cout << "BFS: ";
    g.bfs(3);

    cout << "DFS: ";
    g.dfs(3);

    cout << "DLS:" << endl;
    if (!g.depth_limited_dfs(3, 4, 0)) {
        cout << "Target not Found!" << endl;
    }

    cout << "Iterative Deepening Search:" << endl;
    g.ids(3, 7, 2);

    cout << "Bidirectional Search: ";
    vector<int> path = g.bds(3, 7);
    if (!path.empty()) {
        for (int node : path) {
            cout << node << " ";
        }
        cout << endl;
    } else {
        cout << "No matched entries!" << endl;
    }

    return 0;
}
