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
