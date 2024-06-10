#include "MasterMind_BF.h"

color_t MasterMind_BF::goal()  {
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
        if (isCorrectGuess(combination)) {
            std::cout << "Solution found (BF): " << combination;
            return combination;
        }
    }
    return {};
}
