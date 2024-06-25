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

using color_t = std::vector<std::string>;
enum Param{
    RANDOM,DETERMINISTIC,SWAP, SINGLE_POINT,
    UNIFORM,MAX_GENERATIONS,
    FITNESS
};
struct Guessed {
    color_t colors = {"red", "green", "blue"};
};
struct Config {
    std::string selected_solver = "solve_hillClimbing";
    std::string pathColorFile = "../data/color.txt";
    int codeLength = 30;
    bool communication = false;
    int maxInteraction = 5000;
    std::vector<Param> params = std::vector<Param>(3);
};

std::ostream& operator<<(std::ostream&, const color_t&);
std::ostream& operator<<(std::ostream& o, const std::vector<bool>& result);
class MasterMind{
public:
    MasterMind() = default;
    explicit MasterMind(Config configGame) : config(std::move(configGame)) {init();}
    virtual color_t goal() = 0;

    static int randomInt(int,int);
    static double randomFloat(double,double);
    color_t loadFile(const std::string&) const;
    void init();

    void printSolve();
    void setSolution(color_t);


    color_t generateRandomSolution();
    color_t getGuessSolution();

    color_t getSolution();
    bool betterSolution(const color_t &guess);

    int randomColor() const;

    int checkColor(const color_t&);
    static int checkColor(std::vector<std::pair<std::string, bool>>&);

    std::vector<bool> getCorrectPosition(color_t,color_t) const;
    void showCorrectPosition(const std::vector<bool>&) const;

    //color_t generateNeighbor(const color_t& currentSolution);
    std::vector<color_t> generateNeighbor();
    color_t theBestNeighbor(std::vector<color_t>&);
    static color_t randomNeighbor(std::vector<color_t>&);
    bool isInParams(Param);
protected:
    Config config;
    std::vector<std::pair<std::string, bool>> solution;
    Guessed possibleColors;
    color_t correctSolution;
};


#endif //MEH_PJWSTK_MASTERMIND_H
