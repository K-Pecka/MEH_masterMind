#ifndef MEH_PJWSTK_MASTERMIND_HILLCLIMBING_H
#define MEH_PJWSTK_MASTERMIND_HILLCLIMBING_H

#include "../meh_solution/MasterMind.h"
class MasterMind_hillClimbing: public MasterMind {
public:
    MasterMind_hillClimbing() = default;
    explicit MasterMind_hillClimbing(Config configGame) : MasterMind(std::move(configGame)) {}
    color_t goal() override;
};


#endif //MEH_PJWSTK_MASTERMIND_HILLCLIMBING_H