#ifndef MEH_PJWSTK_MASTERMIND_GENETIC_H
#define MEH_PJWSTK_MASTERMIND_GENETIC_H

#include "../../masterMind/MasterMind.h"
class MasterMind_genetic: public MasterMind {
public:
    MasterMind_genetic() = default;
    explicit MasterMind_genetic(Config configGame) : MasterMind(std::move(configGame)) {}
    solution_t solve() override;
private:
    int generation=0;
    std::vector<solution_t> population;
    std::vector<solution_t> elites;
    std::vector<solution_t> initializePopulation(int populationSize);
    std::vector<int> fitnesses();
    static std::vector<int> selectParent(const std::vector<int>& fit);
    auto crossoverFunction();
    auto mutateFunction();
    auto terminationConditionFunction();
    std::vector<solution_t> crossoverSinglePoint(const solution_t& parent1, const solution_t& parent2);
    std::vector<solution_t> crossoverDoublePoint(const solution_t& parent1, const solution_t& parent2);
    std::vector<solution_t> mutateSwap(std::vector<solution_t>& individual);
    std::vector<solution_t> mutateRandom(std::vector<solution_t>& individual);
    bool terminationConditionGenerations();
    bool terminationConditionFitness();
    std::vector<solution_t> selectWithOutElites(int eliteSize);

    std::vector<solution_t> crossoverParents(std::vector<int> vector1, auto crossover);
};


#endif //MEH_PJWSTK_MASTERMIND_GENETIC_H
