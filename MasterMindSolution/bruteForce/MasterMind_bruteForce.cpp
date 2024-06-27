#include "MasterMind_bruteForce.h"

color_t MasterMind_bruteForce::solve()  {
    if (config.communication) std::cout << "Solution found (BF): ";
    color_t currentCombination(config.codeLength,possibleColors.colors[0]);
    int counter = config.maxInteraction;

    generateCombinations(0, currentCombination, counter);

    return getTheBestSolution();
}
bool MasterMind_bruteForce::generateCombinations(int position, color_t& currentCombination, int& counter) {
    if (counter <= 0) {

        throw std::runtime_error("Too long time");
    }
    if (position == currentCombination.size()) {
        --counter;
        if (currentCombination == correctSolution) {
            setSolution(currentCombination);
            return true;
        }
        return false;
    }
    for (const auto& color : possibleColors.colors) {
        currentCombination[position] = color;
        if (generateCombinations(position + 1, currentCombination, counter)) {
            return true;
        }
    }
    return false;
}