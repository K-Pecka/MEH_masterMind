#include "MasterMind_annealing.h"

color_t MasterMind_annealing::goal() {
    if (config.communication) {
        std::cout << "Solution found (Simulated Annealing):" << std::endl;
    }
    setSolution(generateRandomSolution());
    color_t currentSolution = getSolution();

    int counter = config.maxInteraction;
    for (int i=0;i<counter;i++) {
        auto neighbor = generateRandomNeighbourNorm(currentSolution);
        std::cout<<neighbor;
        if (checkColor(currentSolution)<checkColor(neighbor)) {
            currentSolution = neighbor;
            betterSolution(neighbor);
        }else{
            acceptSolution(neighbor,currentSolution,i);
        }

        if (checkColor(currentSolution) == config.codeLength) {
            break;
        }
    }
    return getSolution();
}

bool MasterMind_annealing::acceptSolution(color_t& neighbor,color_t& current,int& iterator) {
    //std::cout<<exp((abs(checkColor(neighbor) - checkColor(current)) / double(1.0/(iterator+1))))<<std::endl;
    //std::cout<<double(abs(checkColor(neighbor) - checkColor(current)))<<" "<< double(1000*std::pow(0.99,(double )iterator))<<std::endl;

    return randomFloat(0.0,1.0) < exp((abs(checkColor(neighbor) - checkColor(current)) / double(1000*std::pow(0.99,(double )iterator))));
}

color_t MasterMind_annealing::generateRandomNeighbourNorm(color_t& neighbour) {
    std::random_device rd;
    std::mt19937 rdgen(rd());

    std::normal_distribution<double> distr;

    int count = distr(rdgen) + 1;
    if (count >= (neighbour.size() * 2)) count = neighbour.size();

    for (int i = 0; i < count; ++i) {
        std::uniform_int_distribution<int> selbit(0, neighbour.size() - 1);
        int sel = selbit(rdgen);

        std::uniform_int_distribution<int> colorDist(0, possibleColors.colors.size() - 1);
        if(!solution[sel].second)
            neighbour[sel] = possibleColors.colors[colorDist(rdgen)];
    }

    return neighbour;
}
