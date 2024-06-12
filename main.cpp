#include <iostream>
#include <unordered_map>
#include <functional>
#include "MasterMindSolution/MasterMind_BF.h"
#include "MasterMindSolution/MasterMind_hill_climbing.h"


int main(int argc, char* argv[]) {
    Config config = {150, "../data/color.txt", true,10000};

    std::unordered_map<std::string, std::function<void(const Config&)>> solvers = {
            {"solve_BF", [&config](const Config& cfg) {
                MasterMind_BF masterMind(cfg);
                std::cout << masterMind.getGuessSolution();
                std::cout << masterMind.goal();
            }},
            {"solve_hill_climbing", [&config](const Config& cfg) {
                MasterMind_hill_climbing masterMind(cfg);

                color_t solution=masterMind.getGuessSolution();
                std::cout << solution;

                color_t result=masterMind.goal();
                std::cout << result;
                if(config.communication){
                    std::vector<bool> correctPosition = masterMind.getCorrectPosition(result, solution);
                    if(config.communication) masterMind.showCorrectPosition(correctPosition);
                }

            }}
    };

    std::string selected_solver = "solve_hill_climbing";
    if (argc >= 2) {
        selected_solver = argv[1];
    }

    auto solver_it = solvers.find(selected_solver);
    if (solver_it != solvers.end()) {
        auto start_time = std::chrono::system_clock::now();
        solver_it->second(config);
        auto end_time = std::chrono::system_clock::now();
        auto computation_time =  std::chrono::nanoseconds(end_time - start_time);
        std::cout<<computation_time/1000<<std::endl;
    } else {
        std::cerr << "Unknown solver: " << selected_solver << std::endl;
        return 1;
    }

    return 0;
}
