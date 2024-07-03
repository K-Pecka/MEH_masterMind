#include "MasterMind_hillClimbing.h"

solution_t MasterMind_hillClimbing::solve() {
    bool isDeterministic = isInParams(Param::DETERMINISTIC);
    if (config.communication)
        std::cout << "Solution found (Hill climbing " << (isDeterministic ? "deterministic" : "random") << "): " << std::endl << std::endl;
    setSolution(generateRandomSolution());
    while (config.maxInteraction--){
        auto neighbors = generateNeighbor();
        solution_t bestNeighbor = (isDeterministic ? theBestNeighbor(neighbors) : randomNeighbor(neighbors));
        if (config.communication)
            std::cout<<"S>"<< getTheBestSolution()<<"N>"<<bestNeighbor<<std::endl;
        if(!betterSolution(bestNeighbor))break;
    }
    return getTheBestSolution();
}