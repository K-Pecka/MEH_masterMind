#include "MasterMind_hill_climbing.h"

color_t MasterMind_hill_climbing::goal() {
    if (config.communication) std::cout << "Solution found (Hill climbing): "<<std::endl;
    setSolution(generateRandomSolution());
    if (config.communication){
        std::cout << "Initial random solution: "<<getSolution();
        std::cout <<"Initial random solution: "<<getCorrectPosition(getSolution(),correctSolution);
    }
    int improvement = config.maxInteraction;
    while (improvement != 0){
        color_t neighbor = generateNeighbor(getSolution());
        if (config.communication)
        {
            std::cout<<getSolution();
            std::cout<<neighbor;
            std::cout <<getCorrectPosition(neighbor,getSolution());
            std::cout<<std::endl;
        }

        if(betterSolution(neighbor))break;
        improvement--;
    }
    return getSolution();
}