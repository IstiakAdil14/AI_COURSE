# Informed Search Algorithms Implementation 🧭

A comprehensive C++ implementation of informed search algorithms that use heuristics to guide the search process towards optimal solutions.

## 📋 Table of Contents
- [Algorithms Implemented](#-algorithms-implemented)
- [How Algorithms Work](#-how-algorithms-work)
- [Applications](#-applications)
- [Complexity Analysis](#-complexity-analysis)
- [Input & Output Examples](#-input--output-examples)
- [Usage](#-usage)

## 🚀 Algorithms Implemented

### Best First Search (Greedy) 🎯
### A* Search ⭐
### AO* Search (AND-OR)* 🔀

## 🧠 How Algorithms Work

### 🎯 Best First Search (Greedy)
Uses only heuristic function h(n) to guide search. Always expands the node that appears closest to goal according to heuristic. Fast but not guaranteed to find optimal path.

### ⭐ A* Search
Combines actual cost g(n) and heuristic h(n) using evaluation function f(n) = g(n) + h(n). Guarantees optimal solution when heuristic is admissible and consistent.

### 🔀 AO* Search (AND-OR)
Designed for AND-OR graphs where nodes can have AND or OR relationships. Handles complex problem decomposition where multiple subgoals must be achieved simultaneously (AND) or alternatively (OR).

## 🎯 Applications

### 🎯 Best First Search Applications
- Route Planning - quick approximate paths
- Game AI - fast move evaluation
- Web Search - content relevance ranking
- Resource Allocation - greedy optimization
- Real-time Systems - time-critical decisions

### ⭐ A* Search Applications
- GPS Navigation - optimal route finding
- Video Game Pathfinding - NPC movement
- Robotics - obstacle avoidance and planning
- Network Routing - optimal packet paths
- Puzzle Solving - 8-puzzle, 15-puzzle optimization

### 🔀 AO* Search Applications
- Automated Planning - goal decomposition
- Expert Systems - rule-based reasoning
- Natural Language Processing - parsing trees
- Software Engineering - modular design
- Project Management - task dependency resolution

## ⚡ Complexity Analysis

| Algorithm       | Time Complexity | Space Complexity | Optimal? | Complete? | Heuristic Required |
|-----------------|-----------------|------------------|----------|-----------|--------------------|
| Best First 🎯   | O(b^m)          | O(b^m)           | ❌ No    | ❌ No     | ✅ h(n)            |
| A* ⭐           | O(b^d)          | O(b^d)           | ✅ Yes*  | ✅ Yes*   | ✅ h(n) admissible  |
| AO* 🔀          | O(b^d)          | O(b^d)           | ✅ Yes   | ✅ Yes    | ✅ h(n) admissible  |

Legend:

- b = Branching factor
- d = Depth of optimal solution
- m = Maximum depth of search space

*When heuristic is admissible and consistent

Heuristic Properties:

- Admissible: h(n) ≤ actual cost to goal
- Consistent: h(n) ≤ cost(n,n') + h(n')

## 📸 Input & Output Examples

### 🔧 Input Graph Structure

Weighted Graph with Heuristics:

```
A ↔ B (cost: 1, h: 7,6)
A ↔ C (cost: 3, h: 7,2)  
B ↔ D (cost: 3, h: 6,1)
C ↔ D (cost: 1, h: 2,1)
B ↔ E (cost: 6, h: 6,0)
D ↔ E (cost: 1, h: 1,0)
```

### 📊 Sample Outputs

```
Graph:
A → [(B, 1), (C, 3)]
B → [(A, 1), (D, 3), (E, 6)]
C → [(A, 3), (D, 1)]
D → [(B, 3), (C, 1), (E, 1)]
E → [(B, 6), (D, 1)]

--- Best First Search ---
A → B → D → E

--- A* Search ---
A → C → D → E

--- AO* Search ---
A → B → D → E
```

## 🛠️ Usage

### Basic Setup

```cpp
// Create informed graph instance
InformedGraph g;

// Add weighted edges
g.addEdge("A", "B", 1);
g.addEdge("A", "C", 3);
g.addEdge("B", "D", 3);
g.addEdge("C", "D", 1);
g.addEdge("B", "E", 6);
g.addEdge("D", "E", 1);

// Set heuristic values
g.setHeuristic("A", 7);
g.setHeuristic("B", 6);
g.setHeuristic("C", 2);
g.setHeuristic("D", 1);
g.setHeuristic("E", 0);  // Goal node
```

### Running Algorithms

```cpp
// Best First Search (Greedy)
g.bestFirstSearch("A", "E");

// A* Search (Optimal)
g.aStarSearch("A", "E");

// AO* Search (AND-OR Graph)
g.addAndOrEdge("A", "B", true);   // AND relationship
g.addAndOrEdge("A", "C", false);  // OR relationship
g.aoStarSearch("A", "E");
```

## 🔍 Algorithm Comparison

| Feature          | Best First 🎯       | A* ⭐               | AO* 🔀                  |
|------------------|---------------------|--------------------|-------------------------|
| Search Strategy  | Greedy (h only)     | Optimal (f = g + h) | AND-OR decomposition    |
| Memory Usage     | High                | High               | High                    |
| Solution Quality | Sub-optimal         | Optimal*           | Optimal                 |
| Speed            | Fast                | Moderate           | Variable                |
| Use Case         | Quick approximation | Optimal pathfinding| Problem decomposition   |

## 🏗️ Implementation Features

### Core Components
- ✅ Weighted Graph representation with costs
- ✅ Heuristic Management for informed decisions
- ✅ Priority Queue using STL for efficient node selection
- ✅ Path Reconstruction for solution tracing
- ✅ AND-OR Graph support for complex reasoning

### Advanced Features
- 🔧 Flexible Edge Costs - supports variable weights
- 🧭 Custom Heuristics - user-defined evaluation functions
- 🔀 AND-OR Logic - handles complex problem structures
- 📊 Path Tracking - complete solution reconstruction
- ⚡ Optimized Search - efficient priority-based exploration

## 📚 Requirements

- Standard C++17 or later
- STL containers and algorithms

## 🎯 Key Advantages

### 🎯 Best First Search
- Speed: Fastest among informed searches
- Simplicity: Easy to implement and understand
- Memory Efficient: Lower space complexity in practice

### ⭐ A* Search
- Optimality: Guaranteed optimal solution*
- Efficiency: Explores minimal necessary nodes
- Versatility: Works across diverse problem domains

### 🔀 AO* Search
- Problem Decomposition: Handles complex goal structures
- Logical Reasoning: Supports AND-OR relationships
- Planning: Excellent for hierarchical problem solving

## 🚨 Important Notes

- Heuristic Quality: Better heuristics lead to more efficient search
- Admissibility: A* requires admissible heuristics for optimality
- Memory Limits: All algorithms can consume significant memory
- Problem Structure: Choose algorithm based on problem characteristics

Ready to navigate through complex search spaces with intelligent guidance! 🗺️✨
