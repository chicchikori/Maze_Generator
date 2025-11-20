#pragma once
#include <vector>
#include "Generator.h"
#ifdef _WIN32
#define UNIONFIND_API __declspec(dllexport)
#else
#define UNIONFIND_API
#endif
namespace Maze
{

    class UNIONFIND_API MazeSolver
    {
    public:
        static std::vector<int> FindAnswer(const std::vector<Tree>& trees, unsigned int sizeX, unsigned int sizeY);
    };
} // namespace Maze
