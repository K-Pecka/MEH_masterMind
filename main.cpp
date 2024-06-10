#include <iostream>
#include "MasterMind/MasterMind.h"

int main() {
    Config config = {
            4,
            "../data/color.txt"
    };
    MasterMind masterMind(config);
    std::cout << "Randomly generated solution: " << masterMind.getGuessSolution();
    masterMind.bruteForceSolution();
    return 0;
}
