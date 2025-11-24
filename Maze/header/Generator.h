#pragma once
#include <unordered_map>
#include <vector>

namespace Maze
{
    class Node
    {
    public:
        Node(int pos = -1);

        void SetRoot(Node* nodePtr);

        [[nodiscard]] Node* GetRoot();

        [[nodiscard]] int Pos() const;

        void SetSize(int size);

        [[nodiscard]] int GetSize() const;

    private:
        Node* root{this};
        const int pos;
        int size{-1};
    };

    struct Tree
    {
        Node* from;
        Node* to;
    };

    class Generator
    {
    public:
        Generator(unsigned int sizeX = 10, unsigned int sizeY = 10, int seed = 0);
        std::vector<Tree> Generate();

    private:
        void InitTree();

        static bool Unite(Node* id1, Node* id2);

        std::vector<Tree> trees;
        std::unordered_map<int, Node> nodes;

        const unsigned int sizeX;
        const unsigned int sizeY;
        const int seed;
    };

} // namespace Maze
