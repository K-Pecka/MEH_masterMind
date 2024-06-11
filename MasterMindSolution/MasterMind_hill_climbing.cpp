#include "MasterMind_hill_climbing.h"

color_t MasterMind_hill_climbing::goal() {
    if(config.communication) std::cout << "Solution found (Hill climbing): ";
    color_t currentSolution = generateRandomSolution();
    std::cout<<"random first:"<<currentSolution;
    int currentScore = checkColor(currentSolution);

    int improvement = 0;
    while (improvement!=5000) {
        improvement++;

        color_t neighbor = generateNeighbor(currentSolution);
        int neighborScore = checkColor(neighbor);
        std::cout<<neighbor;
        std::cout<<neighborScore<<"<-N C->"<<currentScore<<std::endl;
        if (neighborScore > currentScore) {
            currentSolution = neighbor;
            currentScore = neighborScore;
            break;
        }
    }
    return currentSolution;
}
