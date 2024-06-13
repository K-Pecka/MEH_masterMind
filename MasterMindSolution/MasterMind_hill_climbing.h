#ifndef MEH_PJWSTK_MASTERMIND_HILL_CLIMBING_H
#define MEH_PJWSTK_MASTERMIND_HILL_CLIMBING_H

#include "../meh_solution/MasterMind.h"
class MasterMind_hill_climbing: public MasterMind {
public:
    MasterMind_hill_climbing() = default;
    explicit MasterMind_hill_climbing(Config configGame) : MasterMind(std::move(configGame)) {}
    color_t goal() override;
};


#endif //MEH_PJWSTK_MASTERMIND_HILL_CLIMBING_H