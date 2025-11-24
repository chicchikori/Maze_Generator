# Maze Generator and solver

 this project provides two main features: a **Maze Genarator** based on the Kruskal algorithm and a **Maze Solver** that reconstructs a valid path through the maze.

### **Maze Generator**

Create a **Minimum Spanning Tree (MST)** for the maze using the Kruskal algorithm framework (Union-Find).
### How it works

1. Each cell in the grid is treated as a node.
  
2. All possible walls between adjacent cells are considered as edges.

3. Instead of assigning weights and sorting edegs, the edge list is **shuffled** using a **seeded random number generator**

4. Edges are processed in the shuffles order, and edge is added to the maze only if it connects two different sets (i.e., does not create a cycle).

5. This process continues until all cells are connected, forming a perfect maze with no loops and exactly one path between any two points.

### Why a seed?

  - By using a seed value to shuffle the edge list, the maze becomes **fully reproducible**. Providing the same width, height, and seed will always generate the exact same maze.

## **Maze Solver**

A simple Depth-First Search (DFS) is used to compute a path from the start cell (ID 0) to the goal cell (the last ID).

### How it works

1. During DFS, each visited cell stores a pointer to its parent.

2. Once the goal is reached, the solver reconstructs the path by **backtracking from the goal to the start** using the recorded parent pointers.

3. The resulting path is returned as a list of cell IDs.

This ensures that the output is valid within the maze's spanning tree.

---

## Tutorial

Example: Generating a 10x10 maze with seed value 8 and solving it.

```cpp

#include "Generator.h"
#include "Solver.h"

#include <vector>
#include <iostream>


int main(){
    Maze::Geneator generator(10, 10, 8);

    auto minTree = generator.Generate();
    for(const auto& tree : minTree){
        std::cout << tree.from->Pos() << "->" << tree.to->Pos() <<"\n";
    }

    auto answer = Maze::MazeSolver::FindAnswer(minTree);
    for(const auto& route : answer){
        std::cout << route <<"\n";
    }

    return 0;
}

```

