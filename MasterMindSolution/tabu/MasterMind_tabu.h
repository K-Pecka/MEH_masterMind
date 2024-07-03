#ifndef MEH_PJWSTK_MASTERMIND_TABU_H
#define MEH_PJWSTK_MASTERMIND_TABU_H

#include "../../masterMind/MasterMind.h"
#include <set>
#include <deque>

using solution_t_set = std::set<solution_t>;

class MasterMind_tabu : public MasterMind {
public:
    MasterMind_tabu() = default;
    explicit MasterMind_tabu(Config configGame) : MasterMind(std::move(configGame)) {}
    solution_t solve() override;
private:
    void addToTabu(const solution_t&);
    bool isInTabu(const solution_t&);
    std::vector<solution_t> neighborsInTabu(const std::vector<solution_t>&);
    solution_t_set tabu;
    std::deque<solution_t> solutionHistory;
};

#endif //MEH_PJWSTK_MASTERMIND_TABU_H
