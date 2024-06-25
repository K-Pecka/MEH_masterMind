#ifndef MEH_PJWSTK_MASTERMIND_GENETIC_H
#define MEH_PJWSTK_MASTERMIND_GENETIC_H

#include "../meh_solution/MasterMind.h"
class MasterMind_genetic: public MasterMind {
public:
    MasterMind_genetic() = default;
    explicit MasterMind_genetic(Config configGame) : MasterMind(std::move(configGame)) {}
    color_t goal() override;
};


#endif //MEH_PJWSTK_MASTERMIND_GENETIC_H
