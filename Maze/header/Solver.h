#pragma once
#include <vector>
namespace Maze
{

    class Solver
    {
    public:
        static std::vector<int> FindAnswer(std::vector<std::vector<int>>& graph);
    };
} // namespace Maze
