#include "MasterMind_hillClimbing.h"

solution_t MasterMind_hillClimbing::solve() {
    bool isDeterministic = isInParams(Param::DETERMINISTIC);
    if (config.communication)
        std::cout << "Solution found (hill climbing " <<
        (isDeterministic ? "deterministic" : "random") << "): " << std::endl << std::endl;
    setSolution(generateRandomSolution());
    while (config.maxInteraction--){
        auto neighbors = generateNeighbor();
        solution_t bestNeighbor = (isDeterministic ? theBestNeighbor(neighbors) : randomNeighbor(neighbors));
        if (config.communication)
            std::cout<<"the best solution> "<< getTheBestSolution()<<" the best neighbor> "<<bestNeighbor<<std::endl;
        if(!betterSolution(bestNeighbor))break;
    }
    return getTheBestSolution();
}