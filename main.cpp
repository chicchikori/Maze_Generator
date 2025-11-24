#include <iostream>
#include "Generator.h"
#include "Solver.h"


int main()
{
    const int sizeX = 100;
    const int sizeY = 100;

    Maze::Generator generator(sizeX, sizeY, 8);

    auto minTree = generator.Generate();
    for (const auto& tree : minTree)
    {
        std::cout << tree.from->Pos() << "->" << tree.to->Pos() << "\n";
    }

    auto answer = Maze::MazeSolver::FindAnswer(minTree);
    for (const auto& route : answer)
    {
        std::cout << route << "\n";
    }

    return 0;
}
