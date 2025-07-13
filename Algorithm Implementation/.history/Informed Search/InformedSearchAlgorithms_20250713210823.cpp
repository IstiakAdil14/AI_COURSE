#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <string>

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
};

struct CompareAStar
{
    bool operator()(Node *a, Node *b)
    {
        return a->f() > b->f();
    }
};

struct CompareGreedy
{
    bool operator()(Node *a, Node *b)
    {
        return a->h > b->h;
    }
};

int heuristic(int x1, int y1, int x2, int y2)
{
    // Manhattan distance
    return abs(x1 - x2) + abs(y1 - y2);
}

vector<Node *> get_neighbors(Node *current, const vector<vector<int>> &grid)
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
            neighbors.push_back(new Node(nx, ny, 0, 0, current));
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

void a_star_search(const vector<vector<int>> &grid, pair<int, int> start, pair<int, int> goal)
{
    priority_queue<Node *, vector<Node *>, CompareAStar> openList;
    unordered_map<string, bool> visited;

    Node *startNode = new Node(start.first, start.second, 0,
                               heuristic(start.first, start.second, goal.first, goal.second));
    openList.push(startNode);

    while (!openList.empty())
    {
        Node *current = openList.top();
        openList.pop();

        string key = to_string(current->x) + "," + to_string(current->y);
        if (visited[key])
            continue;
        visited[key] = true;

        if (current->x == goal.first && current->y == goal.second)
        {
            cout << "A* Path: ";
            print_path(current);
            cout << "\nTotal cost: " << current->g << "\n";
            return;
        }

        for (auto neighbor : get_neighbors(current, grid))
        {
            neighbor->g = current->g + 1;
            neighbor->h = heuristic(neighbor->x, neighbor->y, goal.first, goal.second);
            openList.push(neighbor);
        }
    }

    cout << "A* No path found\n";
}

void greedy_best_first_search(const vector<vector<int>> &grid, pair<int, int> start, pair<int, int> goal)
{
    priority_queue<Node *, vector<Node *>, CompareGreedy> openList;
    unordered_map<string, bool> visited;

    Node *startNode = new Node(start.first, start.second, 0,
                               heuristic(start.first, start.second, goal.first, goal.second));
    openList.push(startNode);

    while (!openList.empty())
    {
        Node *current = openList.top();
        openList.pop();

        string key = to_string(current->x) + "," + to_string(current->y);
        if (visited[key])
            continue;
        visited[key] = true;

        if (current->x == goal.first && current->y == goal.second)
        {
            cout << "Greedy Best-First Path: ";
            print_path(current);
            cout << "\nTotal cost: " << current->g << "\n";
            return;
        }

        for (auto neighbor : get_neighbors(current, grid))
        {
            neighbor->g = current->g + 1;
            neighbor->h = heuristic(neighbor->x, neighbor->y, goal.first, goal.second);
            openList.push(neighbor);
        }
    }

    cout << "Greedy Best-First No path found\n";
}

int main()
{
    vector<vector<int>> grid = {
        {0, 0, 0, 0, 1},
        {1, 1, 0, 1, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0}};

    pair<int, int> start = {0, 0};
    pair<int, int> goal = {4, 4};

    a_star_search(grid, start, goal);
    greedy_best_first_search(grid, start, goal);

    return 0;
}
