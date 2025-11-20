#include "../header/Solver.h"
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

} // namespace Maze
