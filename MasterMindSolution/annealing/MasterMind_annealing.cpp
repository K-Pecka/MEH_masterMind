#include "MasterMind_annealing.h"

solution_t MasterMind_annealing::solve() {
    if (config.communication) std::cout << "Solution found (Simulated Annealing):" << std::endl;
    setSolution(generateRandomSolution());
    solution_t currentSolution = getTheBestSolution();

    int counter = config.maxInteraction;
    for (int i=0;i<counter;i++) {
        auto neighbor = generateRandomNeighbourNorm(currentSolution);
       if (goal(neighbor) >= goal(currentSolution)) {
            currentSolution = neighbor;
            betterSolution(currentSolution);
        }else{
            if(acceptSolution(neighbor,currentSolution,i)){
                currentSolution = neighbor;
            }

        }
        if (fullCompatibility(currentSolution)) break;
    }
    betterSolution(currentSolution);
    return getTheBestSolution();
}

bool MasterMind_annealing::acceptSolution(solution_t& neighbor, solution_t& current, int& iterator) {
    auto e = exp((abs(goal(neighbor) - goal(current)) / T(iterator)));
    auto randomValue = randomFloat(0.0,1.0);
    return randomValue < e;
}

solution_t MasterMind_annealing::generateRandomNeighbourNorm(solution_t neighbor) {
    auto rdgen = random();
    std::normal_distribution<double> distr;
    int count = distr(rdgen) + 1;
    if (count >= (neighbor.size() * 2)) count = (int)neighbor.size();
    for (int i = 0; i < count; ++i) {
        int sel = randomInt(0,(int)neighbor.size() - 1);
        auto color = randomColor();
        if(color == neighbor[sel])neighbor[sel] = randomColor();
        else neighbor[sel] = color;
    }
    return neighbor;
}
