#ifndef MEH_PJWSTK_MASTERMIND_GENETIC_H
#define MEH_PJWSTK_MASTERMIND_GENETIC_H

#include "../../masterMind/MasterMind.h"
class MasterMind_genetic: public MasterMind {
public:
    MasterMind_genetic() = default;
    explicit MasterMind_genetic(Config configGame) : MasterMind(std::move(configGame)) {}
    color_t goal() override;
private:
    int generation=0;
    std::vector<color_t> initializePopulation(int populationSize);
    color_t selectParent(const std::vector<color_t>& population);
    color_t crossoverSinglePoint(const color_t& parent1, const color_t& parent2);
    color_t crossoverDoublePoint(const color_t& parent1, const color_t& parent2);
    void mutateSwap(color_t& individual);
    void mutateRandom(color_t& individual);
    bool terminationConditionGenerations();
    bool terminationConditionFitness();
    std::vector<color_t> selectElites(const std::vector<color_t>& population, int eliteSize);
};


#endif //MEH_PJWSTK_MASTERMIND_GENETIC_H
