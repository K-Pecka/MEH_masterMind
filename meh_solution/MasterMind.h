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

using color_t = std::vector<std::string>;

struct Guessed {
    color_t colors = {"red", "green", "blue"};
};
struct Config {
    int codeLength=3;
    std::string pathColorFile;
    bool comunication = true;
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
    void generateRandomSolution();
    color_t getGuessSolution() { return solution; }
    bool isCorrectGuess(const color_t&);
protected:
    Config config;
    Guessed possibleColors;
    color_t solution;
};


#endif //MEH_PJWSTK_MASTERMIND_H
