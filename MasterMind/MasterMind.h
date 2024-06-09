//
// Created by Kacper on 05.06.2024.
//

#ifndef MEH_PJWSTK_MASTERMIND_H
#define MEH_PJWSTK_MASTERMIND_H
#include "../meh_solution/Meh_solution.h"
using color_t = std::vector<std::string>;
struct Guessed{
    std::string input;
    color_t colors={"red","green","blue"};
};

class MasterMind: public Meh_solution{
public:
    MasterMind()=default;
    explicit MasterMind(int maxLength):lengthSolution(maxLength){init();}
    void init();
    int getRandomPosition();
    bool loadGuessesFromFile(const std::string&);
    std::vector<std::string> getPossibleColors(){return possibleColors.colors;};
    void generateRandomSolution();
    color_t getGuessSolution(){return solution;}
private:
    int lengthSolution=3;
    Guessed possibleColors;
    color_t solution;
};

std::ostream& operator<<(std::ostream&, const color_t&);

#endif //MEH_PJWSTK_MASTERMIND_H
