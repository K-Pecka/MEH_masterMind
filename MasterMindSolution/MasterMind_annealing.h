#ifndef MEH_PJWSTK_MASTERMIND_ANNEALING_H
#define MEH_PJWSTK_MASTERMIND_ANNEALING_H

#include "../meh_solution/MasterMind.h"

class MasterMind_annealing: public MasterMind{
public:
    MasterMind_annealing() = default;
    explicit MasterMind_annealing(Config configGame) : MasterMind(std::move(configGame)) {}
    color_t goal() override;
private:
    bool acceptSolution(color_t&,color_t&,int&);
    color_t generateRandomNeighbourNorm(color_t&);
};


#endif //MEH_PJWSTK_MASTERMIND_ANNEALING_H
