#include "../header/MazeUnionFind.h"
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

    MazeGenerator::MazeGenerator(unsigned int sizeX, unsigned int sizeY, int seed) : sizeX(sizeX), sizeY(sizeY), seed(seed)
    {
    }

    std::vector<Tree> MazeGenerator::Generate()
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
    
    bool MazeGenerator::Unite(Node* id1, Node* id2)
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
