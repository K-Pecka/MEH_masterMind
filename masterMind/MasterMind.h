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

using color_t = std::vector<std::string>;
using tinyInt = short;

typedef std::vector<std::pair<std::string, tinyInt>> vector;
enum Param{
    RANDOM,DETERMINISTIC,SWAP, DOUBLE_POINT,FITNESS
};
struct Guessed {
    color_t colors = {"red", "green", "blue"};
};
struct GA{
    int generation = 200;
    int population = 150;
    int eliteSize = 15;
    double crossoverProb=0.9;
    double mutationProb=0.01;

};
struct Config {
    std::string selected_solver = "solve_genetic";
    std::string pathColorFile = "../data/color.txt";
    std::string pathSolutionFile;//    ../data/solution.txt
    int codeLength = 30;
    bool communication = false;
    int maxInteraction = 1000;
    GA GAConfig;
    std::vector<Param> params = std::vector<Param>(3);
};

std::ostream& operator<<(std::ostream&, const color_t&);
std::ostream& operator<<(std::ostream& o, const vector& g);
std::ostream& operator<<(std::ostream& o, const std::vector<tinyInt >& result);
class MasterMind{
public:
    MasterMind() = default;
    explicit MasterMind(Config configGame) : config(std::move(configGame)) {init();}
    virtual color_t solve() = 0;

    static int randomInt(int,int);
    static double randomFloat(double,double);
    static std::mt19937 random();
    color_t loadFile(const std::string&) const;
    color_t setLoadSolution(const std::string&);
    void init();

    void printSolve();
    void setSolution(color_t);


    color_t generateRandomSolution();
    color_t getGuessSolution();

    color_t getTheBestSolution();
    bool betterSolution(const color_t &);
    int getCorrectCounter(const color_t &);
    bool betterSolutionAbsolute(const color_t &,const color_t &);
    bool fullCompatibility(color_t&);
    int randomColor() const;

    int goal(const color_t &guess);
    static int goal(vector &solution);

    std::vector<tinyInt> getCorrectPosition(color_t,color_t) const;
    void showCorrectPosition(const std::vector<tinyInt>&) const;

    std::vector<color_t> generateNeighbor(const color_t& currentSolution);
    std::vector<color_t> generateNeighbor();
    color_t theBestNeighbor(std::vector<color_t>&);
    static color_t randomNeighbor(std::vector<color_t>&);
    bool isInParams(Param);
    static std::set<std::string> isInSolution(const color_t&);
protected:
    Config config;
    vector theBestSolution;
    Guessed possibleColors;
    color_t correctSolution;
    std::set<std::string> colorInSolution;
    double weight = 2;
};


#endif //MEH_PJWSTK_MASTERMIND_H
