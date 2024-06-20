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
        auto neighbors = generateNeighbor();
        color_t bestNeighbor = theBestNeighbor(neighbors);
        if (config.communication)
        {
            std::cout<<std::endl;
            std::cout<<"S>"<<getSolution();
            std::cout<<"N>"<<bestNeighbor;
            std::cout <<getCorrectPosition(bestNeighbor,correctSolution);
            std::cout<<std::endl;
        }

        if(!betterSolution(bestNeighbor))break;
        improvement--;
    }
    return getSolution();
}