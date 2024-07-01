#include <iostream>
#include <unordered_map>
#include <functional>

#include "MasterMindSolution/random/MasterMind_random.h"
#include "MasterMindSolution/bruteForce/MasterMind_bruteForce.h"
#include "MasterMindSolution/hillClimbing/MasterMind_hillClimbing.h"
#include "MasterMindSolution/tabu/MasterMind_tabu.h"
#include "MasterMindSolution/annealing/MasterMind_annealing.h"
#include "MasterMindSolution/genetic/MasterMind_genetic.h"

void toLowerCase(std::string &str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
}
int main(int argc, char* argv[]) {

    std::vector<std::string> args(argv,argc+argv);
    std::unordered_map<std::string,Param> params ={
            {"deterministic",Param::DETERMINISTIC},

            {"swap",Param::SWAP},
            {"double_point",Param::DOUBLE_POINT},
            {"fitness",Param::FITNESS}
    };
    std::unordered_map<std::string, std::function<std::unique_ptr<MasterMind>(const Config&)>> solvers = {
            {"solve_random", [](const Config& cfg) { return std::make_unique<MasterMind_random>(cfg); }},
            {"solve_bruteForce", [](const Config& cfg) { return std::make_unique<MasterMind_bruteForce>(cfg); }},
            {"solve_hillClimbing", [](const Config& cfg) { return std::make_unique<MasterMind_hillClimbing>(cfg); }},
            {"solve_tabu", [](const Config& cfg) { return std::make_unique<MasterMind_tabu>(cfg); }},
            {"solve_annealing", [](const Config& cfg) { return std::make_unique<MasterMind_annealing>(cfg); }},
            {"solve_genetic", [](const Config& cfg) { return std::make_unique<MasterMind_genetic>(cfg); }}
    };

    Config config;
    for(int i=0;i<args.size();i++)
    {
        if(args[i] == "-method" || args[i] == "-m")
        {
            config.selected_solver = args[i+1];
        }
        if(args[i] == "-test" || args[i] == "-t")
        {
            config.testMode = true;
        }
        if(args[i] == "-param")
        {
            while (i + 1 < args.size() && args[i + 1][0] != '-') {
                std::string paramStr = args[++i];
                toLowerCase(paramStr);
                if (params.count(paramStr)) {
                    config.params.push_back(params[paramStr]);

                } else {
                    std::cerr << "Unknown parameter: " << paramStr << std::endl;
                }
            }
        }
        if (args[i] == "-GA") {
            size_t argIndex = 0;
            while (i + 1 < args.size() && args[i + 1][0] != '-') {
                std::string paramStr = args[++i];
                toLowerCase(paramStr);

                try {
                    int value = std::stoi(paramStr);
                    if (argIndex == 0) {
                        config.GAConfig.generation = value;
                    } else if (argIndex == 1) {
                        config.GAConfig.population = value;
                    } else if (argIndex == 2) {
                        config.GAConfig.eliteSize = value;
                    }else if (argIndex == 3) {
                        config.GAConfig.crossoverProb = value;
                    }else if (argIndex == 4) {
                        config.GAConfig.mutationProb = value;
                    }
                    argIndex++;
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Invalid number: " << paramStr << std::endl;
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
        if(args[i] == "-communication" || args[i] == "-c")
        {
            std::string comm = args[i+1];
            config.communication = (comm == "true" || comm == "1");
        }
        if(args[i] == "-solutionPath" || args[i] == "-sp")
        {
            config.pathSolutionFile = args[i+1];
        }
    }
    auto solver_it = solvers.find(config.selected_solver);
    if (solver_it != solvers.end()) {
        auto solver = solver_it->second(config);
        try{
            solver->printSolve();
        }catch (const std::runtime_error& e) {
            std::cout<<-1<<std::endl;
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
