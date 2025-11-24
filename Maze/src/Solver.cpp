#include "../header/Solver.h"
#include <algorithm>

#include <iostream>
#include <stack>
#include <vector>
namespace Maze
{

    std::vector<int> Solver::FindAnswer(std::vector<Tree>& trees)
    {
        const int num =
            trees.size() * 2; // NOLINT(cppcoreguidelines-narrowing-conversions,bugprone-narrowing-conversions)
        const int start = 0;

        int goal = start;

        std::vector<std::vector<int>> graph(num);
        // Create trees
        for (const auto& tree : trees)
        {
            const int a = tree.from->Pos();
            const int b = tree.to->Pos();

            graph[a].push_back(b);
            graph[b].push_back(a);

            goal = std::max({a, b, goal});
        }

        std::cout << goal << ":" << graph.size() << "\n";

        std::vector<int> parent(num, -1);
        std::vector<bool> visited(num, false);
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
            for (const int& nxt : graph[cur])
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
