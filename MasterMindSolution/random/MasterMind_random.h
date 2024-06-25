#ifndef MEH_PJWSTK_MASTERMIND_RANDOM_H
#define MEH_PJWSTK_MASTERMIND_RANDOM_H

#include "../../masterMind/MasterMind.h"
class MasterMind_random : public MasterMind{
public:
    MasterMind_random() = default;
    explicit MasterMind_random(Config configGame) : MasterMind(std::move(configGame)) {}
    color_t goal() override;
};


#endif //MEH_PJWSTK_MASTERMIND_RANDOM_H
