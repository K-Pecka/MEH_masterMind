#ifndef MEH_PJWSTK_MASTERMIND_GENETIC_H
#define MEH_PJWSTK_MASTERMIND_GENETIC_H

#include "../../masterMind/MasterMind.h"
class MasterMind_genetic: public MasterMind {
public:
    MasterMind_genetic() = default;
    explicit MasterMind_genetic(Config configGame) : MasterMind(std::move(configGame)) {}
    color_t solve() override;
private:
    int generation=0;
    std::vector<color_t> population;
    std::vector<color_t> elites;
    std::vector<color_t> initializePopulation(int populationSize);
    std::vector<int> fitnesses();
    static std::vector<int> selectParent(const std::vector<int>& fit);
    auto crossoverFunction();
    auto mutateFunction();
    auto terminationConditionFunction();
    std::vector<color_t> crossoverSinglePoint(const color_t& parent1, const color_t& parent2);
    std::vector<color_t> crossoverDoublePoint(const color_t& parent1, const color_t& parent2);
    std::vector<color_t> mutateSwap(std::vector<color_t>& individual);
    std::vector<color_t> mutateRandom(std::vector<color_t>& individual);
    bool terminationConditionGenerations();
    bool terminationConditionFitness();
    std::vector<color_t> selectWithOutElites(int eliteSize);

    std::vector<color_t> crossoverParents(std::vector<int> vector1, auto crossover);
};


#endif //MEH_PJWSTK_MASTERMIND_GENETIC_H
