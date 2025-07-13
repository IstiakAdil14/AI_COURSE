#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <algorithm>

using namespace std;

struct Node
{
    int x, y;
    int g, h;
    Node *parent;

    Node(int x, int y, int g, int h, Node *parent = nullptr)
        : x(x), y(y), g(g), h(h), parent(parent) {}

    int f() const
    {
        return g + h;
    }

    bool operator>(const Node &other) const
    {
        return f() > other.f();
    }
};

int heuristic(int x1, int y1, int x2, int y2)
{
    // Manhattan distance
    return abs(x1 - x2) + abs(y1 - y2);
}

vector<Node *> get_neighbors(Node *current, vector<vector<int>> &grid, Node *goal)
{
    vector<Node *> neighbors;
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    int rows = grid.size();
    int cols = grid[0].size();

    for (int i = 0; i < 4; ++i)
    {
        int nx = current->x + dx[i];
        int ny = current->y + dy[i];

        if (nx >= 0 && ny >= 0 && nx < rows && ny < cols && grid[nx][ny] == 0)
        {
            int g = current->g + 1;
            int h = heuristic(nx, ny, goal->x, goal->y);
            neighbors.push_back(new Node(nx, ny, g, h, current));
        }
    }
    return neighbors;
}

void print_path(Node *node)
{
    if (!node)
        return;
    print_path(node->parent);
    cout << "(" << node->x << "," << node->y << ") ";
}

void a_star_search(vector<vector<int>> &grid, pair<int, int> start, pair<int, int> end)
{
    priority_queue<Node *, vector<Node *>, function<bool(Node *, Node *)>> openList(
        [](Node *a, Node *b)
        { return a->f() > b->f(); });

    Node *startNode = new Node(start.first, start.second, 0,
                               heuristic(start.first, start.second, end.first, end.second));
    Node *goalNode = new Node(end.first, end.second, 0, 0);

    openList.push(startNode);
    unordered_map<string, bool> visited;

    while (!openList.empty())
    {
        Node *current = openList.top();
        openList.pop();

        string key = to_string(current->x) + "," + to_string(current->y);
        if (visited[key])
            continue;
        visited[key] = true;

        if (current->x == goalNode->x && current->y == goalNode->y)
        {
            cout << "Path: ";
            print_path(current);
            cout << "\nTotal cost: " << current->g << "\n";
            return;
        }

        for (auto neighbor : get_neighbors(current, grid, goalNode))
        {
            openList.push(neighbor);
        }
    }

    cout << "No path found\n";
}
