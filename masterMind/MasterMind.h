#ifndef MEH_PJWSTK_MASTERMIND_H
#define MEH_PJWSTK_MASTERMIND_H

#include <iostream>
#include <chrono>
#include <random>
#include <utility>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <utility>
#include <functional>
#include <set>
#include <numeric>
#include <fstream>
#include <stdexcept>

using solution_t = std::vector<int>;
using solutions = std::vector<std::pair<solution_t, solution_t>>;

enum Param{
    DETERMINISTIC,SWAP, DOUBLE_POINT,FITNESS
};
struct GA{
    int generation = 20;
    int population = 200;
    int eliteSize = 15;
    double crossoverProb=0.9;
    double mutationProb=0.01;

};
struct Config {
    std::string selected_solver = "solve_tabu";
    int colorLength = 5;
    std::string pathSolutionFile = "../data/solution.txt";
    bool testMode = false;
    int codeLength = 30;
    bool communication = false;
    int maxInteraction = 1000;
    int tabuSize = 1000;
    GA GAConfig;
    std::vector<Param> params = std::vector<Param>(3);
};

std::ostream& operator<<(std::ostream&, const solution_t&);

class MasterMind{
public:
    MasterMind() = default;
    explicit MasterMind(Config configGame) : config(std::move(configGame)) {init();}
    virtual solution_t solve() = 0;

    static int randomInt(int,int);
    static double randomFloat(double,double);
    static std::mt19937 random();

    static solutions loadFile(const std::string&) ;
    solutions setLoadSolution(const std::string&);
    void init();

    void printSolve();
    void setSolution(solution_t);


    solution_t generateRandomSolution() const;

    solution_t getTheBestSolution();
    bool betterSolution(const solution_t &);

    int randomColor() const;

    int goal(const solution_t &guess);

    std::vector<solution_t> generateNeighbor(const solution_t& currentSolution) const;
    std::vector<solution_t> generateNeighbor();
    bool fullCompatibility(const solution_t&);
    solution_t theBestNeighbor(std::vector<solution_t>&);
    static solution_t randomNeighbor(std::vector<solution_t>&);
    bool isInParams(Param);
protected:
    std::vector<std::pair<solution_t,int>> lastScore;
    Config config;
    solution_t theBestSolution;
    solutions guessSolution;
};


#endif //MEH_PJWSTK_MASTERMIND_H
