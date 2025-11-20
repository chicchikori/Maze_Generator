#include "../header/Generator.h"
#include <algorithm>
#include <random>
#include <vector>

namespace Maze
{
    Node::Node(int id) : id(id)
    {
    }

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

    [[nodiscard]] int Node::GetSize() const
    {
        return size;
    }

    void Node::SetSize(int size)
    {
        this->size = size;
    }

    Geneator::Geneator(unsigned int sizeX, unsigned int sizeY, int seed) : sizeX(sizeX), sizeY(sizeY), seed(seed)
    {
    }

    std::vector<Tree> Geneator::Generate()
    {
        InitTree();


        std::mt19937 engine(seed);
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


    void Geneator::InitTree()
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

    bool Geneator::Unite(Node* id1, Node* id2)
    {
        auto root1 = id1->GetRoot();
        auto root2 = id2->GetRoot();
        if (root1 == root2)
        {
            return false;
        }
        if (root1->GetSize() < root2->GetSize())
        {
            std::swap(root1, root2);
        }
        root1->SetSize(root1->GetSize() + root2->GetSize());
        root2->SetRoot(root1);
        return true;
    }
} // namespace UnionFind
