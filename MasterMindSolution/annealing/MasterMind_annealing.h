#ifndef MEH_PJWSTK_MASTERMIND_ANNEALING_H
#define MEH_PJWSTK_MASTERMIND_ANNEALING_H

#include "../../masterMind/MasterMind.h"
class MasterMind_annealing: public MasterMind{
public:
    MasterMind_annealing() = default;
    explicit MasterMind_annealing(Config configGame) : MasterMind(std::move(configGame)) {}
    solution_t solve() override;
private:
    std::function < double(int) > T = [](auto i) { return 1000 * std::pow(0.999, (double)i); };
    bool acceptSolution(solution_t&, solution_t&, int&);
    solution_t generateRandomNeighbourNorm(solution_t);
};

#endif //MEH_PJWSTK_MASTERMIND_ANNEALING_H
