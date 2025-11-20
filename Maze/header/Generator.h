#pragma once
#ifdef _WIN32
#define UNIONFIND_API __declspec(dllexport)
#else
#define UNIONFIND_API
#endif
#include <unordered_map>
#include <vector>

namespace Maze
{
    struct UNIONFIND_API Node
    {
        Node(int id = -1);

        void SetRoot(Node* nodePtr);

        [[nodiscard]] Node* GetRoot();

        [[nodiscard]] int Id() const;

        void SetSize(int size);

        [[nodiscard]] int GetSize() const;

    private:
        Node* root{this};
        const int id;
        int size{-1};
    };

    struct UNIONFIND_API Tree
    {
        Node* from;
        Node* to;
    };

    class UNIONFIND_API Geneator
    {
    public:
        Geneator(unsigned int sizeX = 10, unsigned int sizeY = 10, int seed = 0);
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

} // namespace UnionFind
