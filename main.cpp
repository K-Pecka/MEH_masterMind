#include <iostream>
#include <unordered_map>
#include <functional>
#include "MasterMindSolution/MasterMind_BF.h"
#include "MasterMindSolution/MasterMind_hill_climbing.h"

int main(int argc, char* argv[]) {
    Config config = {4, "../data/color.txt", true};

    std::unordered_map<std::string, std::function<void(const Config&)>> solvers = {
            {"solve_BF", [&config](const Config& cfg) {
                MasterMind_BF masterMind(cfg);
                std::cout << masterMind.getGuessSolution();
                std::cout << masterMind.goal();
            }},
            {"solve_hill_climbing", [&config](const Config& cfg) {
                MasterMind_hill_climbing masterMind(cfg);
                std::cout << masterMind.getGuessSolution();
                std::cout << masterMind.goal();
            }}
    };

    std::string selected_solver = "solve_hill_climbing";
    if (argc >= 2) {
        selected_solver = argv[1];
    }

    auto solver_it = solvers.find(selected_solver);
    if (solver_it != solvers.end()) {
        solver_it->second(config);
    } else {
        std::cerr << "Unknown solver: " << selected_solver << std::endl;
        return 1;
    }

    return 0;
}
