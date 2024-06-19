#include "MasterMind_random.h"

color_t MasterMind_random::goal() {
    if (config.communication) std::cout << "Solution found (random): "<<std::endl;
    int counter = config.maxInteraction;
    while(counter)
    {
        betterSolution(getGuessSolution());
        counter--;
    }
    return getGuessSolution();
}