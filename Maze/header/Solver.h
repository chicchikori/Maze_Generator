#pragma once
#include <vector>
#include "Generator.h"
namespace Maze
{

    class Solver
    {
    public:
        static std::vector<int> FindAnswer(std::vector<Tree>& trees);
    };
} // namespace Maze
