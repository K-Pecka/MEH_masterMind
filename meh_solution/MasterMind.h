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
    int codeLength=3;
    std::string pathColorFile;
    bool communication = true;
};

std::ostream& operator<<(std::ostream&, const color_t&);

class MasterMind {
public:
    MasterMind() = default;
    explicit MasterMind(Config configGame) : config(std::move(configGame)) {init();}
    virtual color_t goal() = 0;
    static int randomInt(int,int);
    void loadGuessesFromFile();
    void init();
    color_t generateRandomSolution();
    color_t getGuessSolution();
    int randomColor() const;
    bool betterSolution(const color_t &guess);
    int checkColor(const color_t&);
    int checkColor(std::vector<std::pair<std::string, bool>>&);
    color_t generateNeighbor(const color_t& currentSolution);
protected:
    Config config;
    std::vector<std::pair<std::string, bool>> solution;
    Guessed possibleColors;
    color_t correctSolution;
};


#endif //MEH_PJWSTK_MASTERMIND_H
