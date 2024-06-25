#include "MasterMind_bruteForce.h"

color_t MasterMind_bruteForce::goal()  {
    if(config.communication) std::cout << "Solution found (BF): ";
    return bruteForceSolution();
}
void MasterMind_bruteForce::generateAllCombinations(int codeLength, std::vector<color_t>& combinations, color_t& currentCombination, int counter) {
    if(counter==0)
    {
        throw std::runtime_error("Too long time");
    }
    if (currentCombination.size() == codeLength) {
        combinations.push_back(currentCombination);
        return;
    }
    for (const auto& color : possibleColors.colors) {
        currentCombination.push_back(color);
        generateAllCombinations(codeLength, combinations, currentCombination,counter--);
        currentCombination.pop_back();
    }
}

color_t MasterMind_bruteForce::bruteForceSolution() {
    std::vector<color_t> combinations;
    color_t currentCombination;
    int counter = config.maxInteraction;
    generateAllCombinations(config.codeLength, combinations, currentCombination,counter);

    for (const auto& combination : combinations) {
        if (combination == correctSolution) {
            return combination;
        }
    }
    return {};
}