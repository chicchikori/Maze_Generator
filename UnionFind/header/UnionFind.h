#pragma once
#include <unordered_map>
#include <vector>

namespace UnionFind
{
    extern "C" {
    struct __declspec(dllexport) Node
    {
        Node(int id = -1);

        void SetRoot(Node* nodePtr);

        [[nodiscard]] Node* GetRoot(); // NOLINT(misc-no-recursion)

        [[nodiscard]] int Id() const;

        int size{-1}; // NOLINT(cppcoreguidelines-non-private-member-variables-in-classes
                      // misc-non-private-member-variables-in-classes)

    private:
        Node* root{this};
        int id;
    };

    struct __declspec(dllexport) Tree
    {
        Node* from;
        Node* to;
        bool isAnswer{false};
    };

    class __declspec(dllexport) Generator
    {
    public:
        std::vector<Tree> Generate(int sizeX, int sizeY, int seed);
        std::vector<int> __declspec(dllexport) FindAnser(std::vector<Tree>& trees) const;

    private:
        void InitTree();

        static bool Unite(Node* id1, Node* id2);

        std::vector<Tree> trees;
        std::unordered_map<int, Node> nodes;

        std::vector<Tree> answer;

        int sizeX;
        int sizeY;
        int seed;
    };
    }
} // namespace UnionFind
