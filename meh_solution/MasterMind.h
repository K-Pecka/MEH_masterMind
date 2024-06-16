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

struct Guessed {
    color_t colors = {"red", "green", "blue"};
};
struct Config {
    std::string selected_solver = "solve_random";
    std::string pathColorFile = "../data/color.txt";
    int codeLength = 30;
    bool communication = false;
    int maxInteraction = 100;
};

std::ostream& operator<<(std::ostream&, const color_t&);
std::ostream& operator<<(std::ostream& o, const std::vector<bool>& result);
class MasterMind {
public:
    MasterMind() = default;
    explicit MasterMind(Config configGame) : config(std::move(configGame)) {init();}
    virtual color_t goal() = 0;

    static int randomInt(int,int);
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
    int checkColor(std::vector<std::pair<std::string, bool>>&);

    std::vector<bool> getCorrectPosition(color_t,color_t);
    void showCorrectPosition(std::vector<bool>);

    color_t generateNeighbor(const color_t& currentSolution);

protected:
    Config config;
    std::vector<std::pair<std::string, bool>> solution;
    Guessed possibleColors;
    color_t correctSolution;
};


#endif //MEH_PJWSTK_MASTERMIND_H
