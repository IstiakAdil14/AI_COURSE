#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

class Graph
{
    unordered_map<string, vector<pair<string, int>>> adj;
    unordered_map<string, int> h;

public:
    void addEdge(string u, string v, int cost)
    {
        adj[u].push_back({v, cost});
        adj[v].push_back({u, cost});
    }

    void setHeuristic(string node, int value)
    {
        h[node] = value;
    }

    void bestFirst(string start, string goal)
    {
        set<string> visited;
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;
        pq.push({h[start], start});

        cout << "Best First Path: ";
        while (!pq.empty())
        {
            string curr = pq.top().second;
            pq.pop();
            if (visited.count(curr))
                continue;
            visited.insert(curr);
            cout << curr << (curr == goal ? "\n" : " -> ");
            if (curr == goal)
                return;
            for (auto [n, _] : adj[curr])
                pq.push({h[n], n});
        }
        cout << "Goal not reachable\n";
    }

    void aStar(string start, string goal)
    {
        priority_queue<tuple<int, int, string>, vector<tuple<int, int, string>>, greater<>> pq;
        unordered_map<string, int> g{{start, 0}};
        unordered_map<string, string> prev;
        pq.push({h[start], 0, start});

        while (!pq.empty())
        {
            auto [f, cost, curr] = pq.top();
            pq.pop();
            if (curr == goal)
                break;
            for (auto [n, w] : adj[curr])
            {
                int newG = cost + w;
                if (!g.count(n) || newG < g[n])
                {
                    g[n] = newG;
                    pq.push({newG + h[n], newG, n});
                    prev[n] = curr;
                }
            }
        }

        if (!prev.count(goal))
        {
            cout << "Goal not reachable\n";
            return;
        }
        vector<string> path;
        for (string at = goal; at != start; at = prev[at])
            path.push_back(at);
        path.push_back(start);
        reverse(path.begin(), path.end());
        cout << "A* Path: ";
        for (auto &node : path)
            cout << node << (node == goal ? "\n" : " -> ");
    }
};

int main()
{
    Graph g;
    g.addEdge("A", "B", 1);
    g.addEdge("A", "C", 3);
    g.addEdge("B", "D", 3);
    g.addEdge("C", "D", 1);
    g.addEdge("B", "E", 6);
    g.addEdge("D", "E", 1);

    g.setHeuristic("A", 7);
    g.setHeuristic("B", 6);
    g.setHeuristic("C", 2);
    g.setHeuristic("D", 1);
    g.setHeuristic("E", 0);

    g.bestFirst("A", "E");
    g.aStar("A", "E");

    return 0;
}
