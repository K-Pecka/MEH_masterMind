#include "MasterMind_hill_climbing.h"

color_t MasterMind_hill_climbing::goal() {
    if (config.communication) std::cout << "Solution found (Hill climbing): "<<std::endl;
    betterSolution(generateRandomSolution());
    if (config.communication) std::cout << "Initial random solution: "<<getSolution();
    int improvement = config.maxInteraction;
    while (improvement != 0){
        color_t neighbor = generateNeighbor(getSolution());
        if (config.communication)
        {
           std::cout << "Neighbor: " << getCorrectPosition(neighbor,getSolution());
        }

        if(betterSolution(neighbor))break;
        improvement--;
    }
    return getSolution();
}

