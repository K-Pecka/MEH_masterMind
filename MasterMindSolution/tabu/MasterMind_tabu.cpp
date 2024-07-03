#include "MasterMind_tabu.h"

solution_t MasterMind_tabu::solve() {
    if (config.communication) std::cout << "Solution found (Tabu):" << std::endl;
    setSolution(generateRandomSolution());

    auto neighbor = getTheBestSolution();
    addToTabu(getTheBestSolution());

    while (config.maxInteraction--) {
       auto  neighbors = neighborsInTabu(generateNeighbor(neighbor));
       if (neighbors.empty()) {
           if (!solutionHistory.empty()) {
               neighbor=solutionHistory.back();
               solutionHistory.pop_back();
               continue;
           }
           break;
       }

        neighbor = theBestNeighbor(neighbors);
        betterSolution(neighbor);

        addToTabu(neighbor);
        solutionHistory.push_back(neighbor);
    }
    return getTheBestSolution();
}
std::vector<solution_t> MasterMind_tabu::neighborsInTabu(const std::vector<solution_t>& neighbors){
    std::vector<solution_t> neighborsInTabu;
    for (const auto &neighbor: neighbors) {
        if (!isInTabu(neighbor))neighborsInTabu.push_back(neighbor);
    }
    return neighborsInTabu;
}
void MasterMind_tabu::addToTabu(const solution_t& solution) {
    tabu.insert(solution);
    if (tabu.size() > config.tabuSize)tabu.erase(tabu.begin());
}
bool MasterMind_tabu::isInTabu(const solution_t& solution) {
    return tabu.find(solution) != tabu.end();
}