#include "MasterMind_hillClimbing.h"

color_t MasterMind_hillClimbing::solve() {

    bool isDeterministic = isInParams(Param::DETERMINISTIC);

    if (config.communication) {
        std::cout << "Solution found (Hill climbing " << (isDeterministic ? "deterministic" : "random") << "): " << std::endl;
    }

    setSolution(generateRandomSolution());
    int counter = config.maxInteraction;
    while (counter != 0){
        auto neighbors = generateNeighbor();
        color_t bestNeighbor = (isDeterministic?theBestNeighbor(neighbors):randomNeighbor(neighbors));
        if (config.communication)
        {
            std::cout<<std::endl;
            std::cout << "S>" << getTheBestSolution();
            std::cout<<"N>"<<bestNeighbor;
            std::cout <<getCorrectPosition(bestNeighbor,correctSolution);
            std::cout<<std::endl;
        }

        if(!betterSolution(bestNeighbor))break;
        counter--;
    }
    return getTheBestSolution();
}