#include "MasterMind_random.h"

color_t MasterMind_random::solve() {
    if (config.communication) std::cout << "Solution found (random): "<<std::endl;
    int counter = config.maxInteraction;
    while(counter)
    {
        betterSolution(generateRandomSolution());
        counter--;
    }
    return getGuessSolution();
}