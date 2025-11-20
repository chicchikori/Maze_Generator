#include <chrono>
#include <iostream>
#include "MazeSolver.h"
#include "MazeUnionFind.h"


int main()
{
    auto uf = Maze::MazeGenerator(1000, 1000, 8);
    auto startFind = std::chrono::high_resolution_clock::now();
    auto res = uf.Generate();
    auto endFind = std::chrono::high_resolution_clock::now();
    auto milliFind = std::chrono::duration_cast<std::chrono::milliseconds>(endFind - startFind).count();
    std::cout << "find:" << milliFind << "(" << (float)milliFind / 1000.F << "s)" << "ms\n";

    auto startAnswer = std::chrono::high_resolution_clock::now();
    auto answer = Maze::MazeSolver::FindAnswer(res, 1000, 1000);
    auto endAnswer = std::chrono::high_resolution_clock::now();
    auto milliAnswer = std::chrono::duration_cast<std::chrono::milliseconds>(endAnswer - startAnswer).count();
    std::cout << "answer:" << milliAnswer << "(" << (float)milliAnswer / 1000.F << "s)" << "ms\n";
    return 0;
}
