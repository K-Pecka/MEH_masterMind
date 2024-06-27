#include "MasterMind_tabu.h"

std::ostream& operator<<(std::ostream& o, const color_set& result){
    for (const auto& set_of_colors : result) {
        o << "{ ";
        for (const auto& color : set_of_colors) {
            o << color << " ";
        }
        o << "}" <<std::endl;
    }
    return o;
}
color_t MasterMind_tabu::solve() {
    tabu.clear();
    solutionHistory.clear();
    if (config.communication) std::cout << "Solution found (Tabu):" << std::endl;
    setSolution(generateRandomSolution());
    auto neighbor = getTheBestSolution();
    addToTabu(getTheBestSolution());
    int counter = config.maxInteraction;

    while (counter--) {
        std::vector<color_t> neighbors = neighborsInTabu(generateNeighbor(neighbor));
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
        if(fullCompatibility(neighbor))break;
        addToTabu(neighbor);
        solutionHistory.push_back(neighbor);
    }
    return getTheBestSolution();
}
std::vector<color_t> MasterMind_tabu::neighborsInTabu(const std::vector<color_t>& neighbors){
    std::vector<color_t> neighborsInTabu;
    for (const auto &neighbor: neighbors) {
        if (!isInTabu(neighbor)) {
            neighborsInTabu.push_back(neighbor);
        }
    }
    return neighborsInTabu;
}
void MasterMind_tabu::addToTabu(const color_t& solution) {
    tabu.insert(solution);
    if (tabu.size() > tabu_size) {
        tabu.erase(tabu.begin());
    }
}
bool MasterMind_tabu::isInTabu(const color_t& solution) {
    return tabu.find(solution) != tabu.end();
}