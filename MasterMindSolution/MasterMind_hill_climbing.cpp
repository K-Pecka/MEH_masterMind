#include "MasterMind_hill_climbing.h"

color_t MasterMind_hill_climbing::goal() {
    if (config.communication) std::cout << "Solution found (Hill climbing): "<<std::endl;
    color_t currentSolution = generateRandomSolution();
    if (config.communication) std::cout << "Initial random solution: " << currentSolution;

    int currentScore = checkColor(currentSolution);

    int improvement = 0;
    const int maxAttempts = config.maxInteraction;

    while (improvement < maxAttempts) {
        color_t neighbor = generateNeighbor(currentSolution);
        int neighborScore = checkColor(neighbor);
        if (config.communication)
        {
           // std::cout << "Neighbor solution: " << neighbor;
           // std::cout << "Neighbor score: " << neighborScore << " | Current score: " << currentScore << std::endl;
        }


        if (neighborScore > currentScore) {
            currentSolution = neighbor;
            currentScore = neighborScore;
            improvement = 0;
        } else {
            improvement++;
        }
    }

    for (size_t i = 0; i < currentSolution.size(); ++i) {
        solution[i] = {currentSolution[i], true};
    }

    return currentSolution;
}

