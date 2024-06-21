#include "MasterMind_tabu.h"

std::ostream& operator<<(std::ostream& o, const color_set& result){
    for (const auto& set_of_colors : result) {
        o << "{ ";
        for (const auto& color : set_of_colors) {
            o << color << " ";
        }
        o << "}" << std::endl;
    }
    return o;
}
color_t MasterMind_tabu::goal() {
    int tabu_size = 1000;
    if (config.communication) {
        std::cout << "Solution found (Tabu):" << std::endl;
    }
    setSolution(generateRandomSolution());

    addToTabu(getGuessSolution());
    int counter = config.maxInteraction;
    while (counter--) {
        std::vector<color_t> neighbors;
        for (const auto &neighbor: generateNeighbor()) {
            if (!isInTabu(neighbor)) {
                neighbors.push_back(neighbor);
            }
        }
        std::cout<<tabu.size()<<std::endl;
        if (neighbors.empty())continue;

        auto neighbor = theBestNeighbor(neighbors);
        betterSolution(neighbor);
        addToTabu(neighbor);
        if (tabu.size() > tabu_size) tabu.erase(tabu.end());
    }
    return getSolution();
}
void MasterMind_tabu::addToTabu(const color_t& solution) {
    tabu.insert(solution);
}
bool MasterMind_tabu::isInTabu(const color_t& solution) {
    auto it = tabu.find(solution);
    return it != tabu.end();
}