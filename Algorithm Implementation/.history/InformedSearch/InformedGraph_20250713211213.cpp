#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>
#include <set>
#include <limits>
#include <algorithm>

using namespace std;

class InformedGraph {
private:
    unordered_map<string, vector<pair<string, int>>> graph; // graph[node] = [(neighbor, cost), ...]
    unordered_map<string, int> heuristics; // heuristics[node] = h(n)
    unordered_map<string, vector<pair<string, bool>>> and_or_graph; // parent -> [(child, is_and)]

public:
    // Add an undirected edge with a cost
    void addEdge(const string& u, const string& v, int cost = 1) {
        graph[u].push_back({v, cost});
        graph[v].push_back({u, cost});
    }

    // Set heuristic value for a node
    void setHeuristic(const string& node, int value) {
        heuristics[node] = value;
    }

    // Add AND-OR graph edges (parent -> [(child, is_and)])
    void addAndOrEdge(const string& parent, const string& child, bool is_and = true) {
        and_or_graph[parent].push_back({child, is_and});
    }

    // Display the graph
    void iterate() {
        for (const auto& node : graph) {
            cout << node.first << " → [";
            for (size_t i = 0; i < node.second.size(); ++i) {
                cout << "(" << node.second[i].first << ", " << node.second[i].second << ")";
                if (i != node.second.size() - 1) cout << ", ";
            }
            cout << "]" << endl;
        }
    }

    // ------------------------ Best First Search ------------------------
    void bestFirstSearch(const string& start, const string& goal) {
        set<string> visited;
        // priority_queue with pair<heuristic, node>, min-heap
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
        pq.push({getHeuristic(start), start});

        cout << "Best First Search Path: ";
        while (!pq.empty()) {
            auto [h, current] = pq.top();
            pq.pop();

            if (current == goal) {
                cout << current << endl;
                return;
            }

            if (visited.find(current) != visited.end()) continue;
            visited.insert(current);

            cout << current << " → ";

            for (const auto& neighbor : graph[current]) {
                if (visited.find(neighbor.first) == visited.end()) {
                    pq.push({getHeuristic(neighbor.first), neighbor.first});
                }
            }
        }
        cout << "Goal not reachable" << endl;
    }

    // ------------------------ A* Search ------------------------
    void aStarSearch(const string& start, const string& goal) {
        // priority_queue with tuple<f, g, node>, min-heap
        using T = tuple<int, int, string>;
        priority_queue<T, vector<T>, greater<T>> open_set;
        open_set.push({getHeuristic(start), 0, start});

        unordered_map<string, string> came_from;
        unordered_map<string, int> g_cost;
        g_cost[start] = 0;

        while (!open_set.empty()) {
            auto [f, g, current] = open_set.top();
            open_set.pop();

            if (current == goal) {
                vector<string> path = reconstructPath(came_from, current);
                cout << "A* Search Path: ";
                for (size_t i = 0; i < path.size(); ++i) {
                    cout << path[i];
                    if (i != path.size() - 1) cout << " → ";
                }
                cout << endl;
                return;
            }

            for (const auto& neighbor : graph[current]) {
                int new_g = g + neighbor.second;
                if (g_cost.find(neighbor.first) == g_cost.end() || new_g < g_cost[neighbor.first]) {
                    g_cost[neighbor.first] = new_g;
                    int f = new_g + getHeuristic(neighbor.first);
                    open_set.push({f, new_g, neighbor.first});
                    came_from[neighbor.first] = current;
                }
            }
        }
        cout << "Goal not reachable" << endl;
    }

    // ------------------------ AO* Search ------------------------
    void aoStarSearch(const string& start, const string& goal) {
        // priority_queue with pair<cost, node>, min-heap
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> open_set;
        open_set.push({0, start});

        unordered_map<string, int> best_cost;
        best_cost[start] = 0;

        unordered_map<string, string> node_parent;
        node_parent[start] = "";

        while (!open_set.empty()) {
            auto [cost, current] = open_set.top();
            open_set.pop();

            if (current == goal) {
                vector<string> path = reconstructAOPath(node_parent, current);
                cout << "AO* Search Path: ";
                for (size_t i = 0; i < path.size(); ++i) {
                    cout << path[i];
                    if (i != path.size() - 1) cout << " → ";
                }
                cout << endl;
                return;
            }

            for (const auto& neighbor : and_or_graph[current]) {
                const string& child = neighbor.first;
                bool is_and = neighbor.second;
                // For both AND and OR nodes, update if better cost found
                if (best_cost.find(child) == best_cost.end() || cost + 1 < best_cost[child]) {
                    best_cost[child] = cost + 1;
                    open_set.push({cost + 1, child});
                    node_parent[child] = current;
                }
            }
        }
        cout << "Goal not reachable" << endl;
    }

private:
    int getHeuristic(const string& node) {
        if (heuristics.find(node) != heuristics.end()) {
            return heuristics[node];
        }
        return numeric_limits<int>::max();
    }

    vector<string> reconstructPath(unordered_map<string, string>& came_from, string current) {
        vector<string> path;
        path.push_back(current);
        while (came_from.find(current) != came_from.end()) {
            current = came_from[current];
            path.push_back(current);
        }
        reverse(path.begin(), path.end());
        return path;
    }

    vector<string> reconstructAOPath(unordered_map<string, string>& node_parent, string current) {
        vector<string> path;
        path.push_back(current);
        while (node_parent.find(current) != node_parent.end() && !node_parent[current].empty()) {
            current = node_parent[current];
            path.push_back(current);
        }
        reverse(path.begin(), path.end());
        return path;
    }
};
