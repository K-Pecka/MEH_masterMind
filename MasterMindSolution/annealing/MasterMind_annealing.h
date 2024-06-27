#ifndef MEH_PJWSTK_MASTERMIND_ANNEALING_H
#define MEH_PJWSTK_MASTERMIND_ANNEALING_H

#include "../../masterMind/MasterMind.h"
class MasterMind_annealing: public MasterMind{
public:
    MasterMind_annealing() = default;
    explicit MasterMind_annealing(Config configGame) : MasterMind(std::move(configGame)) {}
    color_t solve() override;
private:
    std::function < double(int) > T = [](auto i) {return double(1000 * std::pow(0.99, (double)i));};
    bool acceptSolution(color_t&,color_t&,int&);
    color_t generateRandomNeighbourNorm(color_t);
};


#endif //MEH_PJWSTK_MASTERMIND_ANNEALING_H
