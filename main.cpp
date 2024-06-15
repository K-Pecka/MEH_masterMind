#include <iostream>
#include <unordered_map>
#include <functional>
#include "MasterMindSolution/MasterMind_BF.h"
#include "MasterMindSolution/MasterMind_hill_climbing.h"

int main(int argc, char* argv[]) {
    std::unordered_map<std::string, std::function<std::unique_ptr<MasterMind>(const Config&)>> solvers = {
            {"solve_BF", [](const Config& cfg) { return std::make_unique<MasterMind_BF>(cfg); }},
            {"solve_hill_climbing", [](const Config& cfg) { return std::make_unique<MasterMind_hill_climbing>(cfg); }}
    };

    Config config;
    if (argc >= 2) {config.selected_solver = argv[1];}
    if (argc >= 3) {config.codeLength = std::stoi(argv[2]);}
    if (argc >= 4) {config.maxInteraction = std::stoi(argv[3]);}
    if (argc >= 6) {config.pathColorFile = argv[5];}
    if (argc >= 5) {
        std::string comm = argv[4];
        config.communication = (comm == "true" || comm == "1");
    }

    auto solver_it = solvers.find(config.selected_solver);
    if (solver_it != solvers.end()) {
        auto start_time = std::chrono::system_clock::now();
        auto solver = solver_it->second(config);
        try{
            solver->printSolve();
        }catch (const std::runtime_error& e) {
            std::cerr << e.what() << std::endl;
            exit(-1);
        }
        auto end_time = std::chrono::system_clock::now();
        auto computation_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        std::cout << computation_time.count() << " microseconds" << std::endl;
    } else {
        std::cerr << "Unknown solver: " << config.selected_solver << std::endl;
        return 1;
    }


    return 0;
}
