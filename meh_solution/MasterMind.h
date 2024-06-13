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
    int maxInteraction = 100;
};

std::ostream& operator<<(std::ostream&, const color_t&);
std::ostream& operator<<(std::ostream& o, const std::vector<bool>& result);
class MasterMind {
public:
    MasterMind() = default;
    explicit MasterMind(Config configGame) : config(std::move(configGame)) {init();}
    virtual color_t goal() = 0;
    void printSolve();
    void setSolution(color_t);
    static int randomInt(int,int);
    void loadGuessesFromFile();
    void init();
    color_t generateRandomSolution();
    color_t getGuessSolution();
    color_t getSolution();
    int randomColor() const;
    bool betterSolution(const color_t &guess);
    int checkColor(const color_t&);
    int checkColor(std::vector<std::pair<std::string, bool>>&);
    std::vector<bool> getCorrectPosition(color_t,color_t);
    color_t generateNeighbor(const color_t& currentSolution);
    void showCorrectPosition(std::vector<bool>);
protected:
    Config config;
    std::vector<std::pair<std::string, bool>> solution;
    Guessed possibleColors;
    color_t correctSolution;
};


#endif //MEH_PJWSTK_MASTERMIND_H
