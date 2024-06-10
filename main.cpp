#include <iostream>
#include "MasterMindSolution/MasterMind_BF.h"

int main() {
    Config config = {
            4,
            "../data/color.txt"
    };
    MasterMind_BF masterMind(config);
    std::cout << "Randomly generated solution: " << masterMind.getGuessSolution();
    masterMind.goal();
    return 0;
}
