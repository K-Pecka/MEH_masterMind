#include "MasterMind_hill_climbing.h"

color_t MasterMind_hill_climbing::goal() {
    auto params = config.params;
    bool isDeterministic = (std::find(params.begin(), params.end(), Param::DETERMINISTIC) != params.end());

    if (config.communication) {
        std::cout << "Solution found (Hill climbing " << (isDeterministic ? "deterministic" : "random") << "): " << std::endl;
    }

    setSolution(generateRandomSolution());
    if (config.communication){
        std::cout << "Initial random solution: "<<getSolution();
        std::cout <<"Initial random solution: "<<getCorrectPosition(getSolution(),correctSolution);
    }
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