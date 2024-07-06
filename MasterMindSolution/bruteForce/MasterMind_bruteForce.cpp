#include "MasterMind_bruteForce.h"

solution_t MasterMind_bruteForce::solve()  {
    if (config.communication)
        std::cout << "Solution found (BF): "<<std::endl;
    solution_t currentCombination(config.codeLength, 0);
    generateCombinations(currentCombination,0);
    return getTheBestSolution();
}
void MasterMind_bruteForce::generateCombinations(solution_t& combination, int position) {
    if (position == config.codeLength) {
        betterSolution(combination);
        return;
    }
    for (int color = 0; color < config.colorLength; ++color) {
        combination[position] = color;
        generateCombinations(combination, position + 1);
    }
}