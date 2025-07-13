# Uninformed Searches Implementation 🔗

A comprehensive C++ implementation of uninformed search algorithms using adjacency list representation.

---

## 📋 Table of Contents

- Algorithms Implemented
- How Algorithms Work
- Applications
- Complexity Analysis
- Input & Output Examples
- Usage

---

## 🚀 Algorithms Implemented

- Breadth-First Search (BFS) 🌊  
- Depth-First Search (DFS) 🏔️  
- Depth-Limited Search (DLS) 📏  
- Iterative Deepening Search (IDS) 🔄  
- Bidirectional Search (BDS) ↔️  

---

## 🧠 How Algorithms Work

### 🌊 Breadth-First Search (BFS)

Explores graph level by level using a queue. Visits all neighbors at current depth before moving to next depth level.

### 🏔️ Depth-First Search (DFS)

Explores as far as possible along each branch using recursion. Backtracks when no unvisited neighbors remain.

### 📏 Depth-Limited Search (DLS)

DFS with a depth constraint. Stops exploring beyond specified depth limit to avoid infinite paths.

### 🔄 Iterative Deepening Search (IDS)

Combines DFS's space efficiency with BFS's optimality. Performs DLS with increasing depth limits until target found.

### ↔️ Bidirectional Search (BDS)

Searches simultaneously from start and goal nodes. Terminates when frontiers meet, potentially reducing search space significantly.

---

## 🎯 Applications

### 🌊 BFS Applications

- Shortest Path in unweighted graphs  
- Social Networks - finding degrees of separation  
- Web Crawling - systematic webpage exploration  
- GPS Navigation - finding nearest locations  

### 🏔️ DFS Applications

- Cycle Detection in graphs  
- Topological Sorting for dependency resolution  
- Maze Solving and pathfinding  
- Connected Components identification  

### 📏 DLS Applications

- Game AI - limiting search depth in game trees  
- Resource-Constrained environments  
- Real-time Systems with time limits  
- Memory-Limited search scenarios  

### 🔄 IDS Applications

- AI Planning systems  
- Puzzle Solving (15-puzzle, Rubik's cube)  
- Optimal Path finding with space constraints  
- Decision Tree exploration  

### ↔️ BDS Applications

- Six Degrees of Separation problems  
- Protein Folding analysis  
- Network Routing optimization  
- Social Media friend suggestions  

---

## ⚡ Complexity Analysis

| Algorithm | Time Complexity | Space Complexity | Optimal? | Complete? |
|-----------|-----------------|------------------|----------|-----------|
| BFS 🌊    | O(V + E)        | O(V)             | ✅ Yes   | ✅ Yes    |
| DFS 🏔️    | O(V + E)        | O(V)             | ❌ No    | ✅ Yes*   |
| DLS 📏    | O(b^l)          | O(bl)            | ❌ No    | ❌ No     |
| IDS 🔄    | O(b^d)          | O(bd)            | ✅ Yes   | ✅ Yes    |
| BDS ↔️    | O(b^(d/2))      | O(b^(d/2))       | ✅ Yes   | ✅ Yes    |

*Legend:*  
V = Number of vertices  
E = Number of edges  
b = Branching factor  
d = Depth of solution  
l = Depth limit  
* = Complete for finite graphs  

---

## 📸 Input & Output Examples

### 🔧 Input Graph Structure

Graph connections:  
3 ↔ 6, 9  
6 ↔ 3, 0, 4  
9 ↔ 3, 5, 7  

### 📊 Sample Outputs

```
unInfS
```

---

## 🛠️ Usage

```cpp
// Create graph instance
Graph g;

// Add edges (undirected)
g.add_edges(3, 6);
g.add_edges(6, 0);
g.add_edges(6, 4);
g.add_edges(3, 9);
g.add_edges(9, 5);
g.add_edges(9, 7);

// Run algorithms
g.bfs(3);                          // BFS from node 3
g.dfs(3);                          // DFS from node 3
g.depth_limited_dfs(3, 4, 2);      // DLS: find 4 from 3, depth limit 2
g.ids(3, 7, 3);                    // IDS: find 7 from 3, max depth 3
g.bds(3, 7);                      // BDS: find path from 3 to 7
```

---

## 🏗️ Implementation Features

- ✅ Adjacency List representation using unordered_map and unordered_set  
- ✅ Undirected Graph support  
- ✅ Visited Tracking to avoid cycles  
- ✅ Path Reconstruction for bidirectional search  
- ✅ Flexible Interface for easy testing  

---

## 📚 Requirements

- Built with C++ standard library  
- No external dependencies required! 🎉
