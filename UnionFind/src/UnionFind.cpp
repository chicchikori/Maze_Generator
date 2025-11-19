#include "../header/UnionFind.h"
#include <algorithm>
#include <random>
#include <stack>
#include <vector>

namespace UnionFind
{
    Node::Node(int id) : id(id) {};

    void Node::SetRoot(Node* nodePtr)
    {
        root = nodePtr;
    }

    [[nodiscard]] Node* Node::GetRoot() // NOLINT(misc-no-recursion)
    {
        if (root == this)
        {
            return this;
        }
        return root = root->GetRoot();
    };

    [[nodiscard]] int Node::Id() const
    {
        return id;
    };

    std::vector<Tree> Generator::Generate(int sizeX, int sizeY, int seed)
    {
        this->sizeX = sizeX;
        this->sizeY = sizeY;
        this->seed = seed;


        InitTree();


        std::mt19937 engine(this->seed);
        std::shuffle(trees.begin(), trees.end(), engine);


        std::vector<Tree> res;
        for (auto& branch : trees)
        {
            if (Unite(branch.from, branch.to))
            {
                res.push_back(branch);
            }
        }

        return res;
    };

    std::vector<int> __declspec(dllexport) Generator::FindAnser(std::vector<Tree>& trees) const
    {
        const int goal = sizeX * sizeY - 1;
        const int start = 0;

        using Graph = std::pmr::unordered_map<int, std::vector<int>>;
        Graph graph;

        // Create graph
        for (auto& tree : trees)
        {
            int a = tree.from->Id();
            int b = tree.to->Id();
            graph[a].push_back(b);
            graph[b].push_back(a);
        }
        std::vector<int> parent(static_cast<long long>(sizeX * sizeY), -1);
        std::vector<bool> visited(static_cast<long long>(sizeX * sizeY), false);
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

    void Generator::InitTree()
    {
        // 1. Create nodes
        nodes.clear();
        for (int y = 0; y < sizeY; y++)
        {
            for (int x = 0; x < sizeX; x++)
            {
                int id = y * sizeX + x;
                nodes.emplace(id, id);
            }
        }
        // 2. Create trees
        trees.clear();
        for (int height = 0; height < sizeY; height++)
        {
            for (int width = 0; width < sizeX; width++)
            {
                int self = height * sizeX + width;
                if (width != sizeX - 1)
                {
                    trees.emplace_back(Tree{.from = &nodes[self], .to = &nodes[self + 1]});
                }
                if (height != sizeY - 1)
                {
                    trees.emplace_back(Tree{.from = &nodes[self], .to = &nodes[self + sizeX]});
                }
            }
        }
    }

    bool Generator::Unite(Node* id1, Node* id2)
    {
        auto root1 = id1->GetRoot();
        auto root2 = id2->GetRoot();
        if (root1 == root2)
        {
            return false;
        }
        if (root1->size < root2->size)
        {
            std::swap(root1, root2);
        }
        root1->size += root2->size;
        root2->SetRoot(root1);
        return true;
    }
} // namespace UnionFind
