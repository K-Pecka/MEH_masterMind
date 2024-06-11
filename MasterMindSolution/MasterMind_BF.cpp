#include "MasterMind_BF.h"

color_t MasterMind_BF::goal()  {
    if(config.communication) std::cout << "Solution found (BF): ";
    return bruteForceSolution();
}
void MasterMind_BF::generateAllCombinations(int codeLength, std::vector<color_t>& combinations, color_t& currentCombination) {
    if (currentCombination.size() == codeLength) {
        combinations.push_back(currentCombination);
        return;
    }
    for (const auto& color : possibleColors.colors) {
        currentCombination.push_back(color);
        generateAllCombinations(codeLength, combinations, currentCombination);
        currentCombination.pop_back();
    }
}

color_t MasterMind_BF::bruteForceSolution() {
    std::vector<color_t> combinations;
    color_t currentCombination;
    generateAllCombinations(config.codeLength, combinations, currentCombination);

    for (const auto& combination : combinations) {
        if (combination == correctSolution) {
            return combination;
        }
    }
    return {};
}
