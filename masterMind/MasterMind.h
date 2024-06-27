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

using color_t = std::vector<std::string>;
enum Param{
    RANDOM,DETERMINISTIC,SWAP, DOUBLE_POINT,
    UNIFORM,MAX_GENERATIONS,
    FITNESS
};
struct Guessed {
    color_t colors = {"red", "green", "blue"};
};
struct GA{
    int generation = 30;
    int population = 100;
    int eliteSize = 5;
};
struct Config {
    std::string selected_solver = "solve_annealing";
    std::string pathColorFile = "../data/color.txt";
    int codeLength = 30;
    bool communication = false;
    int maxInteraction = 1000;
    GA GAConfig = {};
    std::vector<Param> params = std::vector<Param>(3);
};

std::ostream& operator<<(std::ostream&, const color_t&);
std::ostream& operator<<(std::ostream& o, const std::vector<bool>& result);
class MasterMind{
public:
    MasterMind() = default;
    explicit MasterMind(Config configGame) : config(std::move(configGame)) {init();}
    virtual color_t solve() = 0;

    static int randomInt(int,int);
    static double randomFloat(double,double);
    static std::mt19937 random();
    color_t loadFile(const std::string&) const;
    void init();

    void printSolve();
    void setSolution(color_t);


    color_t generateRandomSolution();
    color_t getGuessSolution();

    color_t getTheBestSolution();
    bool betterSolution(const color_t &guess);
    bool fullCompatibility(color_t&);
    int randomColor() const;

    int goal(const color_t &guess);
    static int goal(std::vector<std::pair<std::string, bool>> &solution);

    std::vector<bool> getCorrectPosition(color_t,color_t) const;
    void showCorrectPosition(const std::vector<bool>&) const;

    std::vector<color_t> generateNeighbor(const color_t& currentSolution);
    std::vector<color_t> generateNeighbor();
    color_t theBestNeighbor(std::vector<color_t>&);
    static color_t randomNeighbor(std::vector<color_t>&);
    bool isInParams(Param);
protected:
    Config config;
    std::vector<std::pair<std::string, bool>> TheBestSolution;
    Guessed possibleColors;
    color_t correctSolution;
};


#endif //MEH_PJWSTK_MASTERMIND_H
