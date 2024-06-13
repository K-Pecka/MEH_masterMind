#include <iostream>
#include <unordered_map>
#include <functional>
#include "MasterMindSolution/MasterMind_BF.h"
#include "MasterMindSolution/MasterMind_hill_climbing.h"


int main(int argc, char* argv[]) {
    Config config = {30, "../data/color.txt", false,100};

    std::unordered_map<std::string, std::function<std::unique_ptr<MasterMind>(const Config&)>> solvers = {
            {"solve_BF", [](const Config& cfg) { return std::make_unique<MasterMind_BF>(cfg); }},
            {"solve_hill_climbing", [](const Config& cfg) { return std::make_unique<MasterMind_hill_climbing>(cfg); }}
    };

    std::string selected_solver = "solve_hill_climbing";
    std::string param = "";
    if (argc >= 3) {
        selected_solver = argv[1];
        param = argv[2];
    }else if(argc >=2){
        selected_solver = argv[1];
    }


    auto solver_it = solvers.find(selected_solver);
    if (solver_it != solvers.end()) {
        auto start_time = std::chrono::system_clock::now();
        auto solver = solver_it->second(config);
        solver->printSolve();
        auto end_time = std::chrono::system_clock::now();
        auto computation_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        std::cout << computation_time.count() << " microseconds" << std::endl;
    } else {
        std::cerr << "Unknown solver: " << selected_solver << std::endl;
        return 1;
    }


    return 0;
}
