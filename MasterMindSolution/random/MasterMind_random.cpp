#include "MasterMind_random.h"

solution_t MasterMind_random::solve() {
    if (config.communication) std::cout << "Solution found (random): "<<std::endl;
    while(config.maxInteraction--)
        betterSolution(generateRandomSolution());
    return getTheBestSolution();
}