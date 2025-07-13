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
