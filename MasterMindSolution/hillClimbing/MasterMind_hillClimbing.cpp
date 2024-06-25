#include "MasterMind_hillClimbing.h"

color_t MasterMind_hillClimbing::goal() {

    bool isDeterministic = isInParams(Param::DETERMINISTIC);

    if (config.communication) {
        std::cout << "Solution found (Hill climbing " << (isDeterministic ? "deterministic" : "random") << "): " << std::endl;
    }

    setSolution(generateRandomSolution());
    int improvement = config.maxInteraction;
    while (improvement != 0){
        auto neighbors = generateNeighbor();
        color_t bestNeighbor = (isDeterministic?theBestNeighbor(neighbors):randomNeighbor(neighbors));
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