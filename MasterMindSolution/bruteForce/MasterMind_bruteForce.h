#ifndef MEH_PJWSTK_MASTERMIND_BRUTEFORCE_H
#define MEH_PJWSTK_MASTERMIND_BRUTEFORCE_H


#include "../../masterMind/MasterMind.h"
class MasterMind_bruteForce : public MasterMind {
public:
    MasterMind_bruteForce() = default;
    explicit MasterMind_bruteForce(Config configGame) : MasterMind(std::move(configGame)) {}
    color_t goal() override;
    color_t bruteForceSolution() ;
    void generateAllCombinations(int, std::vector<color_t>&, color_t&,int);
};

#endif //MEH_PJWSTK_MASTERMIND_BRUTEFORCE_H
