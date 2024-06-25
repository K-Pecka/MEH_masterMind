#include <iostream>
#include <unordered_map>
#include <functional>
#include "MasterMindSolution/MasterMind_random.h"
#include "MasterMindSolution/MasterMind_BF.h"
#include "MasterMindSolution/MasterMind_hillClimbing.h"
#include "MasterMindSolution/MasterMind_tabu.h"
#include "MasterMindSolution/MasterMind_annealing.h"
void toLowerCase(std::string &str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
}
int main(int argc, char* argv[]) {

    std::vector<std::string> args(argv,argc+argv);
    std::unordered_map<std::string,Param> params ={
            {"random",Param::RANDOM},
            {"deterministic",Param::DETERMINISTIC},
            {"swap",Param::SWAP},
            {"uniform",Param::UNIFORM},
            {"max_generation",Param::MAX_GENERATIONS}
    };
    std::unordered_map<std::string, std::function<std::unique_ptr<MasterMind>(const Config&)>> solvers = {
            {"solve_random", [](const Config& cfg) { return std::make_unique<MasterMind_random>(cfg); }},
            {"solve_BF", [](const Config& cfg) { return std::make_unique<MasterMind_BF>(cfg); }},
            {"solve_hillClimbing", [](const Config& cfg) { return std::make_unique<MasterMind_hillClimbing>(cfg); }},
            {"solve_tabu", [](const Config& cfg) { return std::make_unique<MasterMind_tabu>(cfg); }},
            {"solve_annealing", [](const Config& cfg) { return std::make_unique<MasterMind_annealing>(cfg); }}
    };

    Config config;
    for(int i=0;i<args.size();i++)
    {
        if(args[i] == "-method" || args[i] == "-m")
        {
            config.selected_solver = args[i+1];
        }
        if(args[i] == "-param")
        {
            while (i + 1 < args.size() && args[i + 1][0] != '-') {
                std::string paramStr = args[++i];
                toLowerCase(paramStr);
                std::cout<<paramStr<<std::endl;
                if (params.count(paramStr)) {
                    config.params.push_back(params[paramStr]);

                } else {
                    std::cerr << "Unknown parameter: " << paramStr << std::endl;
                }
            }
        }
        if(args[i] == "-length" || args[i] == "-l")
        {
            config.codeLength = std::stoi(args[i + 1]);
        }
        if(args[i] == "-interaction" || args[i] == "-i")
        {
            config.maxInteraction = std::stoi(args[i+1]);
        }
        if(args[i] == "-path" || args[i] == "-p")
        {
            config.pathColorFile = args[i+1];
        }
        if(args[i] == "-communication" || args[i] == "-c")
        {
            std::string comm = args[i+1];
            config.communication = (comm == "true" || comm == "1");
        }
    }
    auto solver_it = solvers.find(config.selected_solver);
    if (solver_it != solvers.end()) {
        auto solver = solver_it->second(config);
        try{
            //for(int i=0;i<10;i++)
                solver->printSolve();
        }catch (const std::runtime_error& e) {
            std::cerr << e.what() << std::endl;
            exit(-1);
        }catch (const std::invalid_argument& e) {
            std::cerr << e.what() << std::endl;
            exit(-1);
        }
    } else {
        std::cerr << "Unknown solver: " << config.selected_solver << std::endl;
        return 1;
    }


    return 0;
}
