#ifndef MEH_PJWSTK_MASTERMIND_H
#define MEH_PJWSTK_MASTERMIND_H

#include <utility>

#include "../meh_solution/Meh_solution.h"


using color_t = std::vector<std::string>;

struct Guessed {
    color_t colors = {"red", "green", "blue"};
};

struct Config {
    int codeLength=3;
    std::string pathColorFile;
};

class MasterMind : public Meh_solution {
public:
    MasterMind() = default;
    explicit MasterMind(Config configGame) : config(std::move(configGame)) { init(); }
    void init();
    void loadGuessesFromFile();
    void generateRandomSolution();
    color_t getGuessSolution() { return solution; }
    bool isCorrectGuess(const color_t&);

    void bruteForceSolution();
    void generateAllCombinations(int, std::vector<color_t>&, color_t&);
private:
    Config config;
    Guessed possibleColors;
    color_t solution;


};

std::ostream& operator<<(std::ostream&, const color_t&);

#endif //MEH_PJWSTK_MASTERMIND_H
