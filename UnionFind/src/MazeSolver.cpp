#include "../header/MazeSolver.h"
#include <stack>
namespace Maze
{

    std::vector<int> MazeSolver::FindAnswer(const std::vector<Tree>& trees, unsigned int sizeX, unsigned int sizeY)
    {
        const auto num = sizeX * sizeY;
        const int goal = (int)num - 1;
        const int start = 0;

        std::vector<std::vector<int>> graph(num); // NOLINT(bugprone-implicit-widening-of-multiplication-result)

        // Create graph
        for (const auto& tree : trees)
        {
            int a = tree.from->Id();
            int b = tree.to->Id();
            graph[a].push_back(b);
            graph[b].push_back(a);
        }
        std::vector<int> parent(num, -1); // NOLINT(bugprone-implicit-widening-of-multiplication-result)
        std::vector<bool> visited(num, false); // NOLINT(bugprone-implicit-widening-of-multiplication-result)
        std::stack<int> stack;

        stack.push(start);
        visited[start] = true;


        while (!stack.empty())
        {
            int cur = stack.top();
            stack.pop();
            if (cur == goal)
            {
                break;
            }
            for (int nxt : graph[cur])
            {
                if (!visited[nxt])
                {
                    visited[nxt] = true;
                    parent[nxt] = cur;
                    stack.push(nxt);
                }
            }
        }
        std::vector<int> path;
        int cur = goal;
        while (cur != -1)
        {
            path.emplace_back(cur);

            cur = parent[cur];
        }
        return path;
    }

    void MazeGenerator::InitTree()
    {
        // 1. Create nodes
        nodes.clear();
        for (int y = 0; y < sizeY; y++)
        {
            for (int x = 0; x < sizeX; x++)
            {
                int id = y * (int)sizeX + x;
                nodes.emplace(id, id);
            }
        }
        // 2. Create trees
        trees.clear();
        for (int height = 0; height < sizeY; height++)
        {
            for (int width = 0; width < sizeX; width++)
            {
                int self = height * (int)sizeX + width;
                if (width != sizeX - 1)
                {
                    trees.emplace_back(Tree{.from = &nodes[self], .to = &nodes[self + 1]});
                }
                if (height != sizeY - 1)
                {
                    trees.emplace_back(Tree{.from = &nodes[self], .to = &nodes[self + (int)sizeX]});
                }
            }
        }
    }
} // namespace Maze
