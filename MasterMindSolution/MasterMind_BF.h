#ifndef MEH_PJWSTK_MASTERMIND_BF_H
#define MEH_PJWSTK_MASTERMIND_BF_H

#include "../meh_solution/MasterMind.h"


class MasterMind_BF : public MasterMind {
public:
    MasterMind_BF() = default;
    explicit MasterMind_BF(Config configGame) : MasterMind(configGame) {}
    color_t goal() override;
    color_t bruteForceSolution() ;
    void generateAllCombinations(int, std::vector<color_t>&, color_t&);
};

#endif //MEH_PJWSTK_MASTERMIND_BF_H
